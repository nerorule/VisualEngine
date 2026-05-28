#pragma once

#include <VisualEngine/Inc/VisualEngine.h>

class ShapeStates : public VisualEngine::AppState
{
public:
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render() override;

protected:
	virtual void CreateShape();

	using Vertices = std::vector<VisualEngine::Graphics::VertexPC>;
	Vertices mVertices;

	VisualEngine::Graphics::MeshBuffer mMeshBuffer;
	VisualEngine::Graphics::VertexShader mVertexShader;
	VisualEngine::Graphics::PixelShader mPixelShader;
};

class QuadState : public ShapeStates
{
public:
	void Update(float deltaTime) override;

protected:
	void CreateShape() override;
};

class DiamondState : public ShapeStates
{
public:
	void Update(float deltaTime) override;

protected:
	void CreateShape() override;
};

class HeartState : public ShapeStates
{
public:
	void Update(float deltaTime) override;

protected:
	void CreateShape() override;
};

