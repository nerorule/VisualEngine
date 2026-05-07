#include "ShapeStates.h"

using namespace VisualEngine;
using namespace VisualEngine::Graphics;

void ShapeState::Initialize()
{
}

void ShapeState::Terminate()
{
	mVertices.clear();
	SafeRelease(mPixelShader);
	SafeRelease(mInputLayout);
	SafeRelease(mVertexShader);
	SafeRelease(mVertexBuffer);
}

void ShapeState::Update(float deltaTime)
{
}

void ShapeState::Render()
{
	auto context = GraphicsSystem::Get()->GetContext();

	// BindBuffer
	context->VSSetShader(mVertexShader, nullptr, 0);
	context->IASetInputLayout(mInputLayout);
	context->PSSetShader(mPixelShader, nullptr, 0);

	// Define the obj data (hor to read vertices)
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Draw
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
	context->Draw(static_cast<UINT>(mVertices.size()), 0);
}

void ShapeState::CreateShape()
{
	mVertices.push_back({ {-0.5f, -0.5f, 0.0f}, {VisualEngine::Graphics::Colors::Red} });
	mVertices.push_back({ {0.0f, 0.5f, 0.0f}, {VisualEngine::Graphics::Colors::Green} });
	mVertices.push_back({ {0.5f, -0.5f, 0.0f}, {VisualEngine::Graphics::Colors::Blue} });
}
