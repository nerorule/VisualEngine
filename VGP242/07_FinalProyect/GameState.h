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

	Math::Vector3 RenderPlanet(const VisualEngine::Graphics::MeshBuffer& mesh,
		VisualEngine::Graphics::TextureId textureId,
		float rotation,
		float orbitRotation,
		float orbitDistance);

	Math::Vector3 ComputePlanetPosition(float rotation, float orbitRotation, float orbitDistance);


	float mPlanetOrbitDistance = 4.0f;

	// planet selection & camera follow
	enum Planet
	{
		Planet_Sun = 0,
		Planet_Mercury,
		Planet_Venus,
		Planet_Earth,
		Planet_Mars,
		Planet_Jupiter,
		Planet_Saturn,
		Planet_Uranus,
		Planet_Neptune,
		Planet_Pluto,
		Planet_Count
	};
	int mSelectedPlanet = Planet_Earth;
	bool mFollowPlanet = false;
	Math::Vector3 mFollowOffset = Math::Vector3{ 3.0f, 2.0f, 0.0f };

	// toggle orbit guides
	bool mShowOrbits = true;

	// per-planet angles and speeds
	std::array<float, Planet_Count> mRotationAngles{};
	std::array<float, Planet_Count> mOrbitAngles{};
	std::array<float, Planet_Count> mRotationSpeeds{};
	std::array<float, Planet_Count> mOrbitSpeeds{};

	// Planets Textures
	VisualEngine::Graphics::TextureId mSpaceTextureId;
	VisualEngine::Graphics::MeshBuffer mSpaceMeshBuffer;

	VisualEngine::Graphics::TextureId mSunTextureId;
	VisualEngine::Graphics::MeshBuffer mSunMeshBuffer;

	VisualEngine::Graphics::TextureId mMercuryTextureId;
	VisualEngine::Graphics::MeshBuffer mMercuryMeshBuffer;

	VisualEngine::Graphics::TextureId mVenusTextureId;
	VisualEngine::Graphics::MeshBuffer mVenusMeshBuffer;

	VisualEngine::Graphics::TextureId mEarthTextureId;
	VisualEngine::Graphics::MeshBuffer mEarthMeshBuffer;

	VisualEngine::Graphics::TextureId mMarsTextureId;
	VisualEngine::Graphics::MeshBuffer mMarsMeshBuffer;

	VisualEngine::Graphics::TextureId mJupiterTextureId;
	VisualEngine::Graphics::MeshBuffer mJupiterMeshBuffer;

	VisualEngine::Graphics::TextureId mSaturnTextureId;
	VisualEngine::Graphics::MeshBuffer mSaturnMeshBuffer;

	VisualEngine::Graphics::TextureId mUranusTextureId;
	VisualEngine::Graphics::MeshBuffer mUranusMeshBuffer;

	VisualEngine::Graphics::TextureId mNeptuneTextureId;
	VisualEngine::Graphics::MeshBuffer mNeptuneMeshBuffer;

	VisualEngine::Graphics::TextureId mPlutoTextureId;
	VisualEngine::Graphics::MeshBuffer mPlutoMeshBuffer;

	// moon its own roation
	VisualEngine::Graphics::TextureId mMoonTextureId;
	VisualEngine::Graphics::MeshBuffer mMoonMeshBuffer;
	float mMoonOrbitDistance = 0.6f;
	float mMoonOrbitSpeed = 0.2f;
	float mMoonRotationSpeed = 0.1f;
	float mMoonOrbitAngle = 0.0f;
	float mMoonRotationAngle = 0.0f;

	// store moon world matrix computed in Update and used in Render
	Math::Matrix4 mMoonWorld = Math::Matrix4::Identity;
	

	// ========================================================

	VisualEngine::Graphics::VertexShader mVertexShader;
	VisualEngine::Graphics::PixelShader mPixelShader;
	VisualEngine::Graphics::Sampler mSampler;

	VisualEngine::Graphics::Camera mCamera;
	VisualEngine::Graphics::ConstantBuffer mConstantBuffer;
};