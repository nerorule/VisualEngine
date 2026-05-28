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

	VisualEngine::Graphics::TextureId mTextureId;
	VisualEngine::Graphics::MeshPX mMesh;

	VisualEngine::Graphics::MeshBuffer mMeshBuffer;
	VisualEngine::Graphics::VertexShader mVertexShader;
	VisualEngine::Graphics::PixelShader mPixelShader;
	VisualEngine::Graphics::Sampler mSampler;

	VisualEngine::Graphics::Camera mCamera;
	VisualEngine::Graphics::ConstantBuffer mConstantBuffer;
};
