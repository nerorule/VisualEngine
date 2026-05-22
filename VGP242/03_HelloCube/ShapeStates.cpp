#include "ShapeStates.h"

using namespace VisualEngine;
using namespace VisualEngine::Graphics;
using namespace VisualEngine::Input;

void ShapeState::Initialize()
{
	// create shape
	CreateShape();
	//mMeshBuffer.Initialize(mVertices.data(), sizeof(VertexPC), mVertices.size());
	mMeshBuffer.Initialize(mMesh);
	std::filesystem::path shaderPath = L"../../Assets/Shaders/DoColor.fx";
	mVertexShader.Initialize<VertexPC>(shaderPath);
	mPixelShader.Initialize(shaderPath);
}

void ShapeState::Terminate()
{
	mVertices.clear();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mMeshBuffer.Terminate();
}

void ShapeState::Update(float deltaTime)
{
	if (InputSystem::Get()->IsKeyPressed(KeyCode::UP))
	{
		MainApp().ChangeState("HouseState");
	}
}

void ShapeState::Render()
{
	mVertexShader.Bind();
	mPixelShader.Bind();
	mMeshBuffer.Render();
}

void ShapeState::CreateShape()
{
	mVertices.push_back({ {-0.5f, -0.5f, 0.0f}, {VisualEngine::Graphics::Colors::Red  } });
	mVertices.push_back({ { 0.0f,  0.5f, 0.0f}, {VisualEngine::Graphics::Colors::Green} });
	mVertices.push_back({ { 0.5f, -0.5f, 0.0f}, {VisualEngine::Graphics::Colors::Blue } });
}

