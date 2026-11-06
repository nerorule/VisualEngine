#include "Precompiled.h"
#include "PostProccesingEffect.h"

#include "RenderObject.h"
#include "Texture.h"
#include "VertexTypes.h"
#include "GraphicsSystem.h"

using namespace VisualEngine;
using namespace VisualEngine::Graphics;

namespace
{
	const char* gModeNames[] = {
		"None",
		"MonoChrome",
		"Invert",
		"Mirror",
		"Blur",
		"Combine2",
		"MotionBlur",
		"ChromaticAberration",
		"Wave"
	};
}

void PostProccesingEffect::Initialize(const std::filesystem::path& filePath)
{
	mVertexShader.Initialize<VertexPX>(filePath);
	mPixelShader.Initialize(filePath);
	mSampler.Initialize(Sampler::Filter::Point, Sampler::AdressMode::Wrap);
	mPostProcessingBuffer.Initialize();
}
void PostProccesingEffect::Terminate()
{
	mPostProcessingBuffer.Terminate();
	mSampler.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
}

void PostProccesingEffect::Begin()

{
	mVertexShader.Bind();
	mPixelShader.Bind();
	mSampler.BindPS(0);
	for (uint32_t i = 0; i < mTextures.size(); ++i)
	{
		if (mTextures[i] != nullptr)
		{
			mTextures[i]->BindPS(i);
		}
	}
	PostProcessingData data;
	data.mode = static_cast<int>(mMode);
	switch (mMode)
	{
	case Mode::None:
	case Mode::MonoChrome:
	case Mode::Invert:
		break;
	case Mode::Mirror:
	{
		data.param0 = mMirrorScaleX;
		data.param1 = mMirrorScaleY;
	}
	break;
	case Mode::Blur:
	case Mode::MotionBlur:
	{
		GraphicsSystem* gs = GraphicsSystem::Get();
		const float screenWidth = gs->GetBackBufferWidth();
		const float screenHeight = gs->GetBackBufferHeight();
		data.param0 = mBlurStrenght / screenWidth;
		data.param1 = mBlurStrenght / screenHeight;
	}
	break;
	case Mode::Combine2:
	{
		data.param0 = mCombine2Alpha;
	}
	break;
	case Mode::ChromaticAberration:
	{
		data.param0 = mAberrationValue;
		data.param1 = mAberrationValue;
	}
	break;
	case Mode::Wave:
	{
		data.param0 = mWaveLenght;
		data.param1 = mNumWaves;
	}
	break;
	default:
		break;
	}

	mPostProcessingBuffer.Update(data);
	mPostProcessingBuffer.BindPS(0);
}
void PostProccesingEffect::End()
{
	for (uint32_t i = 0; i < mTextures.size(); ++i)
	{
		Texture::UnBindPS(i);
	}
}

void PostProccesingEffect::Render(const RenderObject& renderObject)
{
	renderObject.meshBuffer.Render();
}

void PostProccesingEffect::SetTexture(const Texture* texture, uint32_t slot)
{
	ASSERT(slot < mTextures.size(), "PostProccesingEffect: Invalid slot index.");
	mTextures[slot] = texture;
}
void PostProccesingEffect::SetMode(Mode mode)
{
	mMode = mode;
}

void PostProccesingEffect::DebugUI()
{
	if (ImGui::CollapsingHeader("Post Processing Effect", ImGuiTreeNodeFlags_DefaultOpen))
	{
		int currentMode = static_cast<int>(mMode);
		if (ImGui::Combo("Mode", &currentMode, gModeNames, static_cast<int>(std::size(gModeNames))))
		{
			mMode = static_cast<Mode>(currentMode);
		}
		if (mMode == Mode::Mirror)
		{
			ImGui::DragFloat("Mirror Scale X", &mMirrorScaleX, 0.01f, -1.0f, 1.0f);
			ImGui::DragFloat("Mirror Scale Y", &mMirrorScaleY, 0.01f, -1.0f, 1.0f);
		}
		else if (mMode == Mode::Blur)
		{
			ImGui::DragFloat("BlurStrenght", &mBlurStrenght, 0.01f, 0.0f, 1.0f);
		}
		else if (mMode == Mode::Combine2)
		{
			ImGui::DragFloat("Combine2Alpha", &mCombine2Alpha, 0.01f, 0.0f, 1.0f);
		}
		else if (mMode == Mode::ChromaticAberration)
		{
			ImGui::DragFloat("AberrationValue", &mAberrationValue, 0.001f, 0.0f, 1.0f);
		}
		else if (mMode == Mode::Wave)
		{
			ImGui::DragFloat("WaveLength", &mWaveLenght, 0.001f, 0.0f, 1.0f);
			ImGui::DragFloat("NumWaves", &mNumWaves, 1.0f, 0.0f, 1000.0f);
		}
	}
}