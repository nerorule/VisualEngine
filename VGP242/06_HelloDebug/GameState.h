#pragma once

#include <VisualEngine/Inc/VisualEngine.h>

class GameState : public VisualEngine::AppState
{
public:
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render() override;
	void DebugUI() override;
private:
	void UpdateCamera(float deltaTime);

	VisualEngine::Graphics::Camera mCamera;
};