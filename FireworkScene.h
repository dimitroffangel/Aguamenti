#ifndef AGUAMENTI_FIREWORKSCENE_H
#define AGUAMENTI_FIREWORKSCENE_H

#include "Firework.h"
#include "Precision.h"

class FireworkScene
{
	static constexpr size_t MAXIMUM_NUMBER_OF_FIREWORKS = 800;

public:
	void UpdateFireworks(const Aguamenti::Real deltaTime, ID3D11DeviceContext1& deviceContext);
	void DrawFireworks(const DirectX::SimpleMath::Matrix& matrixView, const DirectX::SimpleMath::Matrix& matrixProjection);
	void HandleMouseEvent(const float deltaTime, const DirectX::Mouse::State mouseState, ID3D11DeviceContext1& deviceContext);

private:
	void CreateFirework(const Firework& firework, ID3D11DeviceContext1& deviceContext);

private:
	Aguamenti::Real m_TimerBeforeAnotherFireworkSet = 0.0f;
	bool m_HasSpawnedFireworks = false;
	std::vector<Firework> m_Fireworks;
	std::vector< std::unique_ptr<DirectX::GeometricPrimitive>> m_FireworkMeshes;
};

#endif