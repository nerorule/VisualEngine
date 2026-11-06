#pragma once

#include "ConstantBuffer.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "Sampler.h"

namespace VisualEngine::Graphics
{
	class RenderObject;
	class Texture;

	class PostProccesingEffect
	{
	public:
		enum class Mode
		{
			None,
			MonoChrome,
			Invert,
			Mirror,
			Blur,
			Combine2,
			MotionBlur,
			ChromaticAberration,
			Wave
		};

		void Initialize(const std::filesystem::path& filePath);
		void Terminate();

		void Begin();
		void End();

		void Render(const RenderObject& renderObject);

		void SetTexture(const Texture* texture, uint32_t slot = 0);
		void SetMode(Mode mode);

		void DebugUI();
	private:
		struct PostProcessingData
		{
			int mode = 0;
			float param0 = 0.0f;
			float param1 = 0.0f;
			float param2 = 0.0f;
		};
		using PostProccesinBuffer = TypedConstantBuffer<PostProcessingData>;
		PostProccesinBuffer mPostProcessingBuffer;

		VertexShader mVertexShader;
		PixelShader mPixelShader;
		Sampler mSampler;
		std::array<const Texture*, 4> mTextures;

		Mode mMode = Mode::None;
		// debug ui settings
		float mMirrorScaleX = -1.0f;
		float mMirrorScaleY = 1.0f;
		float mBlurStrenght = 5.0f;
		float mCombine2Alpha = 0.0f;
		float mAberrationValue = 0.005f;
		float mWaveLenght = 0.05f;
		float mNumWaves = 20.0f;
	};
}