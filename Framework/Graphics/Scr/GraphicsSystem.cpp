#include "Precompiled.h"
#include "GraphicsSystem.h"

using namespace VisualEngine;
using namespace VisualEngine::Graphics;

namespace
{
	std::unique_ptr<GraphicsSystem> sGraphicsSystem;
	Core::WindowMessageHandler sWindowMessageHandler;
}

LRESULT CALLBACK GraphicsSystem::GraphicsSystemMessageHandler(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (sGraphicsSystem != nullptr)
	{
		switch (msg)
		{
			case WM_SIZE:
			{
				const uint32_t width = static_cast<uint32_t>(LOWORD(lParam));
				const uint32_t height = static_cast<uint32_t>(HIWORD(lParam));
				sGraphicsSystem->Resize(width, height);
				break;
			}
		}
	}
}

void GraphicsSystem::StaticInitialize(HWND window, bool fullScreen)\
{
	ASSERT(sGraphicsSystem == nullptr, "GraphicsSystem: is already initialized");
	sGraphicsSystem = std::make_unique<GraphicsSystem>();
	sGraphicsSystem->Intialize(window, fullScreen);
}
void GraphicsSystem::StaticTerminate()
{
	if (sGraphicsSystem != nullptr)
	{
		sGraphicsSystem->Terminate();
		sGraphicsSystem.reset();
	}
}
GraphicsSystem* GraphicsSystem::Get()
{
	ASSERT(sGraphicsSystem != nullptr, "Graphics: is not initialized");
	return sGraphicsSystem.get();
}
GraphicsSystem::~GraphicsSystem()
{
	ASSERT(mD3DDevice == nullptr && mImmediateContext == nullptr, "GraphicsSystem: must be terminated");
}
void GraphicsSystem::Intialize(HWND window, bool fullScreen)
{
	RECT clientRect = {};
	GetClientRect(window, &clientRect);
	UINT width = (UINT)(clientRect.right - clientRect.left);
	UINT height = (UINT)(clientRect.bottom - clientRect.top);

	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	swapChainDesc.BufferCount = 2;
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.OutputWindow = window;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = !fullScreen;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	const D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_1;

	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		&featureLevel,
		1,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&mSwapChain,
		&mD3DDevice,
		nullptr,
		&mImmediateContext);

	ASSERT(SUCCEEDED(hr), "GraphicsSystem: Failed to create device and swap chain!");
	mSwapChain->GetDesc(&mSwapChainDesc);

	Resize(GetBackBufferWidth(), GetBackBufferHeight());

	sWindowMessageHandler.Hook(window, GraphicsSystemMessageHandler);
}

void GraphicsSystem::Terminate()
{
	sWindowMessageHandler.Unhook();

	SafeRelease(mDepthStencilView);
	SafeRelease(mDepthStencilBuffer);
	SafeRelease(mRenderTargetView);
	SafeRelease(mSwapChain);
	SafeRelease(mImmediateContext);
	SafeRelease(mD3DDevice);
}

void GraphicsSystem::BeginRender()
{
	mImmediateContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);
	mImmediateContext->ClearRenderTargetView(mRenderTargetView, (FLOAT*)(&mClearcolor));
	mImmediateContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0.0f);
}
void GraphicsSystem::EndRender()
{
	mSwapChain->Present(mVSync, 0);
}
void GraphicsSystem::ToggleFullScreen()
{
	BOOL fullscren;
	mSwapChain->GetFullscreenState(&fullscren, nullptr);
	mSwapChain->SetFullscreenState(!fullscren, nullptr);
}
void GraphicsSystem::ResetRenderTarget()
{
	mImmediateContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);
}

void GraphicsSystem::ResetViewport()
{
	mImmediateContext->RSSetViewports(1, &mViewport);
}

void GraphicsSystem::SetClearColor(const Color& color)
{
	mClearcolor = color;
}

void GraphicsSystem::SetVSync(bool vsync)
{
	mVSync = vsync ? 1 : 0;
}

uint32_t GraphicsSystem::GetBackBufferWidth() const
{
	return mSwapChainDesc.BufferDesc.Width;
}

uint32_t GraphicsSystem::GetBackBufferHeight() const
{
	return mSwapChainDesc.BufferDesc.Height;
}

float GraphicsSystem::GetBackBufferAspectRatio() const
{
	return static_cast<float>(GetBackBufferWidth()) / static_cast<float>(GetBackBufferHeight());
}

ID3D11Device* GraphicsSystem::GetDevice()
{
	return mD3DDevice;
}

ID3D11DeviceContext* GraphicsSystem::GetContext()
{
	return mImmediateContext;
}
