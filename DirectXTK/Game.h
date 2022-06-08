//
// Game.h
//

#pragma once

#include "./DirectXTK/Common/DeviceResources.h"
#include "./DirectXTK/Common/StepTimer.h"

#include "./PhysicScenes/PhysicsScene.h"


// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game final : public DX::IDeviceNotify
{
public:

    Game() noexcept(false);
    ~Game() = default;

    Game(Game&&) = default;
    Game& operator= (Game&&) = default;

    Game(Game const&) = delete;
    Game& operator= (Game const&) = delete;

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // IDeviceNotify
    void OnDeviceLost() override;
    void OnDeviceRestored() override;

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowMoved();
    void OnDisplayChange();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const noexcept;
private:
    void CreateMouseResources(HWND window);
    void HandleMouseEvent(const float deltaTime);

private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();

    // Device resources.
    std::unique_ptr<DX::DeviceResources> m_DeviceResources;

    // Rendering loop timer.
    DX::StepTimer  m_Timer;

    // Scene specific
    DirectX::SimpleMath::Matrix m_World;
    DirectX::SimpleMath::Matrix m_View;
    DirectX::SimpleMath::Matrix m_Projection;
    std::unique_ptr<DirectX::Mouse> m_Mouse;
    
    // Physics Specific
    std::unique_ptr<PhysicsScene> m_PhysicsScene;
};
