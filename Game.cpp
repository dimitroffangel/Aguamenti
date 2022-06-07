//
// Game.cpp
//

#include "pch.h"
#include "Game.h"
#include "FireworkScene.h"
#include "BulletScene.h"

extern void ExitGame() noexcept;

using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;

Game::Game() noexcept(false)
{
    m_DeviceResources = std::make_unique<DX::DeviceResources>();
    // TODO: Provide parameters for swapchain format, depth/stencil format, and backbuffer count.
    //   Add DX::DeviceResources::c_AllowTearing to opt-in to variable rate displays.
    //   Add DX::DeviceResources::c_EnableHDR for HDR10 display.
    m_DeviceResources->RegisterDeviceNotify(this);

    m_PhysicsScene = std::make_unique<FireworkScene>();
    m_PhysicsScene->m_Gravity.m_X = 0;
    m_PhysicsScene->m_Gravity.m_Y = -0.002f;
    m_PhysicsScene->m_Gravity.m_Z = 0;
    m_PhysicsScene->m_DragForceCoeficientK1 = 0.05f;
    m_PhysicsScene->m_DragForceCoeficientK2 = 0.01f;
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
    m_DeviceResources->SetWindow(window, width, height);

    m_DeviceResources->CreateDeviceResources();
    CreateDeviceDependentResources();

    m_DeviceResources->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();

    CreateMouseResources(window);

    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:
    /*
    m_Timer.SetFixedTimeStep(true);
    m_Timer.SetTargetElapsedSeconds(1.0 / 60);
    */
}

#pragma region Frame Update
// Executes the basic game loop.
void Game::Tick()
{
    m_Timer.Tick([&]()
    {
        Update(m_Timer);
    });

    Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
    const float elapsedTime = static_cast<float>(timer.GetElapsedSeconds());

    // TODO: Add your game logic here.
    HandleMouseEvent(elapsedTime);
    ID3D11DeviceContext1* const deviceContext = m_DeviceResources->GetD3DDeviceContext();
    assert(deviceContext != nullptr);
    m_PhysicsScene->UpdatePhysicsObjects(elapsedTime, *deviceContext);
}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_Timer.GetFrameCount() == 0)
    {
        return;
    }

    Clear();

    m_DeviceResources->PIXBeginEvent(L"Render");
    ID3D11DeviceContext1* const deviceContext = m_DeviceResources->GetD3DDeviceContext();
    assert(deviceContext != nullptr);

    // TODO: Add your rendering code here.
    m_PhysicsScene->DrawPhysicsObjects(m_View, m_Projection);

    m_DeviceResources->PIXEndEvent();
    // Show the new frame.
    m_DeviceResources->Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
    m_DeviceResources->PIXBeginEvent(L"Clear");

    // Clear the views.
    ID3D11DeviceContext1* const deviceContext = m_DeviceResources->GetD3DDeviceContext();
    assert(deviceContext != nullptr);
    ID3D11RenderTargetView* const renderTarget = m_DeviceResources->GetRenderTargetView();
    assert(renderTarget != nullptr);
    ID3D11DepthStencilView* const depthStencil = m_DeviceResources->GetDepthStencilView();
    assert(depthStencil != nullptr);

    deviceContext->ClearRenderTargetView(renderTarget, Colors::CornflowerBlue);
    deviceContext->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    deviceContext->OMSetRenderTargets(1, &renderTarget, depthStencil);

    // Set the viewport.
    const auto viewport = m_DeviceResources->GetScreenViewport();
    deviceContext->RSSetViewports(1, &viewport);

    m_DeviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
    m_Timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowMoved()
{
    const auto deviceResourcesOutputSize = m_DeviceResources->GetOutputSize();
    m_DeviceResources->WindowSizeChanged(deviceResourcesOutputSize.right, deviceResourcesOutputSize.bottom);
}

void Game::OnDisplayChange()
{
    m_DeviceResources->UpdateColorSpace();
}

void Game::OnWindowSizeChanged(int width, int height)
{
    if (!m_DeviceResources->WindowSizeChanged(width, height))
        return;

    CreateWindowSizeDependentResources();

    // TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const noexcept
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width = 800;
    height = 600;
}
void Game::CreateMouseResources(HWND window)
{
    m_Mouse = std::make_unique<Mouse>();
    m_Mouse->SetWindow(window);
}
void Game::HandleMouseEvent(const float deltaTime)
{
    const DirectX::Mouse::State mouseState = m_Mouse->GetState();
    ID3D11DeviceContext1* const deviceContext = m_DeviceResources->GetD3DDeviceContext();
    assert(deviceContext != nullptr);
    m_PhysicsScene->HandleMouseEvent(deltaTime, mouseState, *deviceContext);
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::CreateDeviceDependentResources()
{
    ID3D11Device1* const device = m_DeviceResources->GetD3DDevice();
    assert(device != nullptr);

    // TODO: Initialize device dependent objects here (independent of window size).
    ID3D11DeviceContext1* const deviceContext = m_DeviceResources->GetD3DDeviceContext();
    assert(deviceContext != nullptr);
    
    m_World = Matrix::Identity;
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
    // TODO: Initialize windows-size dependent objects here.
    const auto deviceResourcesOutputSize = m_DeviceResources->GetOutputSize();
    m_View = Matrix::CreateLookAt(Vector3(0.f, 0.f, 3.f), Vector3::Zero, Vector3::UnitY);
    m_Projection = Matrix::CreatePerspectiveFieldOfView(XM_PI / 4.f, static_cast<float>(deviceResourcesOutputSize.right) / static_cast<float>(deviceResourcesOutputSize.bottom), 0.1f, 10.f);
}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.
    m_Mouse.reset();
}

void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}
#pragma endregion
