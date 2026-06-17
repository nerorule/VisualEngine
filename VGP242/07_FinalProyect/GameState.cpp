#include "GameState.h"

using namespace VisualEngine;
using namespace VisualEngine::Graphics;
using namespace VisualEngine::Input;

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 1.0f, -7.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

	// Create Shape
	MeshPX space = MeshBuilder::CreateSkySpherePX(60, 60, 20.0f);
	mSpaceMeshBuffer.Initialize(space);

	Graphics::MeshPX sun = MeshBuilder::CreateSpherePX(30, 30, 1.0f);
	mSunMeshBuffer.Initialize(sun);

	Graphics::MeshPX mercury = MeshBuilder::CreateSpherePX(30, 30, 0.2f);
	mMercuryMeshBuffer.Initialize(mercury);

	Graphics::MeshPX venus = MeshBuilder::CreateSpherePX(30, 30, 0.3f);
	mVenusMeshBuffer.Initialize(venus);

	Graphics::MeshPX earth = MeshBuilder::CreateSpherePX(30, 30, 0.5f);
	mEarthMeshBuffer.Initialize(earth);

	Graphics::MeshPX mars = MeshBuilder::CreateSpherePX(30, 30, 0.20f);
	mMarsMeshBuffer.Initialize(mars);

	Graphics::MeshPX jupiter = MeshBuilder::CreateSpherePX(30, 30, 0.9f);
	mJupiterMeshBuffer.Initialize(jupiter);

	Graphics::MeshPX saturn = MeshBuilder::CreateSpherePX(30, 30, 0.7f);
	mSaturnMeshBuffer.Initialize(saturn);

	Graphics::MeshPX uranus = MeshBuilder::CreateSpherePX(30, 30, 0.45f);
	mUranusMeshBuffer.Initialize(uranus);

	Graphics::MeshPX neptune = MeshBuilder::CreateSpherePX(30, 30, 0.43f);
	mNeptuneMeshBuffer.Initialize(neptune);

	Graphics::MeshPX pluto = MeshBuilder::CreateSpherePX(30, 30, 0.08f);
	mPlutoMeshBuffer.Initialize(pluto);

	Graphics::MeshPX moon = MeshBuilder::CreateSpherePX(30, 30, 0.05f);
	mMoonMeshBuffer.Initialize(moon);

	std::filesystem::path shaderPath = L"../../Assets/Shaders/DoTexture.fx";
	mVertexShader.Initialize<VertexPX>(shaderPath);
	mPixelShader.Initialize(shaderPath);
	mConstantBuffer.Initialize(sizeof(Math::Matrix4));

	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AdressMode::Wrap);

	mSpaceTextureId = TextureManager::Get()->LoadTexture(L"space.jpg");
	mEarthTextureId = TextureManager::Get()->LoadTexture("earth.jpg");
	mMercuryTextureId = TextureManager::Get()->LoadTexture("planets/mercury.jpg");
	mVenusTextureId = TextureManager::Get()->LoadTexture("planets/venus.jpg");
	mMarsTextureId = TextureManager::Get()->LoadTexture("planets/mars.jpg");
	mJupiterTextureId = TextureManager::Get()->LoadTexture("planets/jupiter.jpg");
	mSaturnTextureId = TextureManager::Get()->LoadTexture("planets/saturn.jpg");
	mUranusTextureId = TextureManager::Get()->LoadTexture("planets/uranus.jpg");
	mNeptuneTextureId = TextureManager::Get()->LoadTexture("planets/neptune.jpg");
	mPlutoTextureId = TextureManager::Get()->LoadTexture("planets/pluto.jpg");
	mMoonTextureId = TextureManager::Get()->LoadTexture("planets/pluto.jpg");
	mSunTextureId = TextureManager::Get()->LoadTexture("planets/sun.jpg");

	// initialize angles and speeds 
	for (int i = 0; i < Planet_Count; ++i)
	{
		mRotationAngles[i] = 0.0f;
		mOrbitAngles[i] = 0.0f;
		mRotationSpeeds[i] = 0.5f; // default rotation 
		mOrbitSpeeds[i] = 0.1f;    // default orbit speed 
	}
	// defaults
	mRotationSpeeds[Planet_Mercury] = 1.6f;
	mOrbitSpeeds[Planet_Mercury] = 4.0f;

	mRotationSpeeds[Planet_Venus] = 1.2f;
	mOrbitSpeeds[Planet_Venus] = 1.6f;

	mRotationSpeeds[Planet_Earth] = 1.0f;
	mOrbitSpeeds[Planet_Earth] = 1.0f;

	mRotationSpeeds[Planet_Mars] = 0.9f;
	mOrbitSpeeds[Planet_Mars] = 0.8f;

	mRotationSpeeds[Planet_Jupiter] = 0.6f;
	mOrbitSpeeds[Planet_Jupiter] = 0.2f;

	mRotationSpeeds[Planet_Saturn] = 0.55f;
	mOrbitSpeeds[Planet_Saturn] = 0.14f;

	mRotationSpeeds[Planet_Uranus] = 0.45f;
	mOrbitSpeeds[Planet_Uranus] = 0.08f;

	mRotationSpeeds[Planet_Neptune] = 0.42f;
	mOrbitSpeeds[Planet_Neptune] = 0.06f;

	mRotationSpeeds[Planet_Pluto] = 0.25f;
	mOrbitSpeeds[Planet_Pluto] = 0.04f;

	// moon defaults 
	mMoonOrbitDistance = 0.6f;   
	mMoonOrbitSpeed = 0.1f;
	mMoonRotationSpeed = 0.1f;
	mMoonOrbitAngle = 0.0f;
	mMoonRotationAngle = 0.0f;
}

void GameState::Terminate()
{
	TextureManager::Get()->ReleaseTexture(mSpaceTextureId);
	TextureManager::Get()->ReleaseTexture(mEarthTextureId);
	TextureManager::Get()->ReleaseTexture(mMercuryTextureId);
	TextureManager::Get()->ReleaseTexture(mVenusTextureId);
	TextureManager::Get()->ReleaseTexture(mMarsTextureId);
	TextureManager::Get()->ReleaseTexture(mJupiterTextureId);
	TextureManager::Get()->ReleaseTexture(mSaturnTextureId);
	TextureManager::Get()->ReleaseTexture(mUranusTextureId);
	TextureManager::Get()->ReleaseTexture(mNeptuneTextureId);
	TextureManager::Get()->ReleaseTexture(mPlutoTextureId);
	TextureManager::Get()->ReleaseTexture(mMoonTextureId);
	TextureManager::Get()->ReleaseTexture(mSunTextureId);
	mSampler.Terminate();
	mConstantBuffer.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mSpaceMeshBuffer.Terminate();
	mEarthMeshBuffer.Terminate();
	mMercuryMeshBuffer.Terminate();
	mVenusMeshBuffer.Terminate();
	mMarsMeshBuffer.Terminate();
	mJupiterMeshBuffer.Terminate();
	mSaturnMeshBuffer.Terminate();
	mUranusMeshBuffer.Terminate();
	mNeptuneMeshBuffer.Terminate();
	mPlutoMeshBuffer.Terminate();
	mMoonMeshBuffer.Terminate();
	mSunMeshBuffer.Terminate();
}

void GameState::Update(float deltaTime)
{
	UpdateCamera(deltaTime);

	// rotate speed
	// advance each planet using its own speeds
	for (int i = 0; i < Planet_Count; ++i)
	{
		const float rotDelta = mRotationSpeeds[i] * deltaTime;
		const float orbitDelta = mOrbitSpeeds[i] * deltaTime;

		mRotationAngles[i] += rotDelta;
		mOrbitAngles[i] += orbitDelta;

		// keep angles bounded
		const float twoPi = Math::Constants::TwoPi;
		mRotationAngles[i] = fmodf(mRotationAngles[i], twoPi);
		mOrbitAngles[i] = fmodf(mOrbitAngles[i], twoPi);
	}


	// advance moon angles
	mMoonOrbitAngle += mMoonOrbitSpeed * deltaTime;
	mMoonRotationAngle += mMoonRotationSpeed * deltaTime;

	// keep moon angles bounded
	const float twoPi = Math::Constants::TwoPi;
	mMoonOrbitAngle = fmodf(mMoonOrbitAngle, twoPi);
	mMoonRotationAngle = fmodf(mMoonRotationAngle, twoPi);

	
	const float dEarth = 4.0f;
	Math::Matrix4 earthLocalRot = Math::Matrix4::RotationY(mRotationAngles[Planet_Earth]);
	Math::Matrix4 earthTrans = Math::Matrix4::Translation(dEarth, 0.0f, 0.0f);
	Math::Matrix4 earthOrbitRot = Math::Matrix4::RotationY(mOrbitAngles[Planet_Earth]);
	Math::Matrix4 earthWorld = earthOrbitRot * earthTrans * earthLocalRot;
	Math::Vector3 earthPos = Math::GetTranslation(earthWorld);

	// compute moon position
	const float r = mMoonOrbitDistance;
	const float a = mMoonOrbitAngle;
	Math::Vector3 moonPos;
	moonPos.x = earthPos.x + sinf(a) * r;
	moonPos.y = earthPos.y; 
	moonPos.z = earthPos.z + cosf(a) * r;

	// store world matrix for the moon
	mMoonWorld = Math::Matrix4::Translation(moonPos) * Math::Matrix4::RotationY(mMoonRotationAngle);
}

void GameState::Render()
{
	// ===================================================================
	// prepare the gpu
	mVertexShader.Bind();
	mPixelShader.Bind();

	// sync buffer information
	mConstantBuffer.BindVS(0);
	mSampler.BindPS(0);

	// update buffer data
	Math::Matrix4 matView = mCamera.GetViewMatrix();
	Math::Matrix4 matProj = mCamera.GetProjectionMatrix();
	// ===================================================================

	// render space ========================================================
	Math::Matrix4 matWorld = Math::Matrix4::Identity;
	Math::Matrix4 wvp = matWorld * matView * matProj;
	wvp = Math::Transpose(wvp);
	mConstantBuffer.Update(&wvp);
	// assign textures
	TextureManager::Get()->BindPS(mSpaceTextureId, 0);
	// render object
	mSpaceMeshBuffer.Render();
	// ==================================================================

	// render sun ========================================================
	matWorld = Math::Matrix4::Identity;
	wvp = matWorld * matView * matProj;
	wvp = Math::Transpose(wvp);
	mConstantBuffer.Update(&wvp);
	// assign textures
	TextureManager::Get()->BindPS(mSunTextureId, 0);
	// render object
	mSunMeshBuffer.Render();
	// ==================================================================

	// orbit distances (unit space)
	const float dMercury = 2.0f;
	const float dVenus = 3.0f;
	const float dEarth = 4.0f; 
	const float dMars = 5.0f;
	const float dJupiter = 8.0f;
	const float dSaturn = 11.0f;
	const float dUranus = 14.0f;
	const float dNeptune = 17.0f;
	const float dPluto = 20.0f;

	// render planets and collect positions
	Math::Vector3 planetPositions[Planet_Count];

	planetPositions[Planet_Mercury] = RenderPlanet(mMercuryMeshBuffer, mMercuryTextureId,
		mRotationAngles[Planet_Mercury], mOrbitAngles[Planet_Mercury], dMercury);

	planetPositions[Planet_Venus] = RenderPlanet(mVenusMeshBuffer, mVenusTextureId,
		mRotationAngles[Planet_Venus], mOrbitAngles[Planet_Venus], dVenus);

	planetPositions[Planet_Earth] = RenderPlanet(mEarthMeshBuffer, mEarthTextureId,
		mRotationAngles[Planet_Earth], mOrbitAngles[Planet_Earth], dEarth);

	planetPositions[Planet_Mars] = RenderPlanet(mMarsMeshBuffer, mMarsTextureId,
		mRotationAngles[Planet_Mars], mOrbitAngles[Planet_Mars], dMars);

	planetPositions[Planet_Jupiter] = RenderPlanet(mJupiterMeshBuffer, mJupiterTextureId,
		mRotationAngles[Planet_Jupiter], mOrbitAngles[Planet_Jupiter], dJupiter);

	planetPositions[Planet_Saturn] = RenderPlanet(mSaturnMeshBuffer, mSaturnTextureId,
		mRotationAngles[Planet_Saturn], mOrbitAngles[Planet_Saturn], dSaturn);

	planetPositions[Planet_Uranus] = RenderPlanet(mUranusMeshBuffer, mUranusTextureId,
		mRotationAngles[Planet_Uranus], mOrbitAngles[Planet_Uranus], dUranus);

	planetPositions[Planet_Neptune] = RenderPlanet(mNeptuneMeshBuffer, mNeptuneTextureId,
		mRotationAngles[Planet_Neptune], mOrbitAngles[Planet_Neptune], dNeptune);

	planetPositions[Planet_Pluto] = RenderPlanet(mPlutoMeshBuffer, mPlutoTextureId,
		mRotationAngles[Planet_Pluto], mOrbitAngles[Planet_Pluto], dPluto);

	Math::Matrix4 moonWvp = mMoonWorld * matView * matProj;
	moonWvp = Math::Transpose(moonWvp);
	mConstantBuffer.Update(&moonWvp);
	TextureManager::Get()->BindPS(mMoonTextureId, 0);
	mMoonMeshBuffer.Render();

	// compute positions for debug guides
	Math::Vector3 moonPos = Math::GetTranslation(mMoonWorld);

	// follow the selected planet
	if (mFollowPlanet && mSelectedPlanet >= 0 && mSelectedPlanet < GameState::Planet_Count)
	{
		Math::Vector3 pos = planetPositions[mSelectedPlanet];
		mCamera.SetPosition(pos + mFollowOffset);
		mCamera.SetLookAt(pos);
	}
	// =================================================================

	// draw orbit guides
	if (mShowOrbits)
	{
		SimpleDraw::AddGroundCircle(20, dMercury, Math::Vector3::Zero, Colors::White);
		SimpleDraw::AddGroundCircle(20, dVenus, Math::Vector3::Zero, Colors::White);
		SimpleDraw::AddGroundCircle(20, dEarth, Math::Vector3::Zero, Colors::White);
		SimpleDraw::AddGroundCircle(20, dMars, Math::Vector3::Zero, Colors::White);
		SimpleDraw::AddGroundCircle(20, dJupiter, Math::Vector3::Zero, Colors::White);
		SimpleDraw::AddGroundCircle(20, dSaturn, Math::Vector3::Zero, Colors::White);
		SimpleDraw::AddGroundCircle(20, dUranus, Math::Vector3::Zero, Colors::White);
		SimpleDraw::AddGroundCircle(20, dNeptune, Math::Vector3::Zero, Colors::White);
		SimpleDraw::AddGroundCircle(20, dPluto, Math::Vector3::Zero, Colors::White);
	}

	SimpleDraw::Render(mCamera);
}
//float myVariable = 0.0f;
void GameState::DebugUI()
{
	ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	// Planet selection
	const char* items[GameState::Planet_Count] =
	{
		"Sun", "Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune", "Pluto"
	};
	ImGui::Combo("Follow Planet", &mSelectedPlanet, items, IM_ARRAYSIZE(items));

	// Follow toggle and offset
	ImGui::Checkbox("Follow Enabled", &mFollowPlanet);
	ImGui::DragFloat3("Follow Offset", &mFollowOffset.x, 0.1f, -100.0f, 100.0f);

	// Show orbit guides toggle
	ImGui::Checkbox("Show Orbits", &mShowOrbits);


	ImGui::Separator();
	ImGui::Text("Moon");
	ImGui::DragFloat("Moon Orbit Speed", &mMoonOrbitSpeed, 0.001f, 0.0f, 2.0f, "%.4f");
	ImGui::DragFloat("Moon Rotation Speed", &mMoonRotationSpeed, 0.01f, -10.0f, 10.0f, "%.3f");
	ImGui::DragFloat("Moon Orbit Distance", &mMoonOrbitDistance, 0.01f, 0.05f, 10.0f, "%.2f");

	// Rotation/orbit speed controls for selected planet
	if (mSelectedPlanet >= 0 && mSelectedPlanet < Planet_Count)
	{
		ImGui::Separator();
		ImGui::Text("Selected: %s", items[mSelectedPlanet]);
		ImGui::DragFloat("Rotation Speed", &mRotationSpeeds[mSelectedPlanet], 0.01f, -10.0f, 10.0f, "%.3f");
		ImGui::DragFloat("Orbit Speed", &mOrbitSpeeds[mSelectedPlanet], 0.01f, -10.0f, 10.0f, "%.3f");
	}

	ImGui::End();
}

void GameState::UpdateCamera(float deltaTime)
{
	InputSystem* input = InputSystem::Get();
	const float moveSpeed = input->IsKeyDown(KeyCode::LSHIFT) ? 10.0f : 1.0f;
	const float turnSpeed = 0.1f;

	if (input->IsKeyDown(KeyCode::W))
	{
		mCamera.Walk(moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::S))
	{
		mCamera.Walk(-moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::D))
	{
		mCamera.Strafe(moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::A))
	{
		mCamera.Strafe(-moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::E))
	{
		mCamera.Rise(moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::Q))
	{
		mCamera.Rise(-moveSpeed * deltaTime);
	}

	if (input->IsMouseDown(MouseButton::RBUTTON))
	{
		mCamera.Yaw(input->GetMouseMoveX() * turnSpeed * deltaTime);
		mCamera.Pitch(input->GetMouseMoveY() * turnSpeed * deltaTime);
	}
}

Math::Vector3 GameState::RenderPlanet(const Graphics::MeshBuffer& mesh,
	Graphics::TextureId textureId,
	float rotation,
	float orbitRotation,
	float orbitDistance)
{
	// build transforms (local spin, translate out, orbit)
	Math::Matrix4 localRot = Math::Matrix4::RotationY(rotation);
	Math::Matrix4 trans = Math::Matrix4::Translation(orbitDistance, 0.0f, 0.0f);
	Math::Matrix4 orbitRot = Math::Matrix4::RotationY(orbitRotation);
	

	// compose: orbitRot * trans * localRot 
	Math::Matrix4 world = orbitRot * trans * localRot;

	// compute and upload WVP
	Math::Matrix4 wvp = world * mCamera.GetViewMatrix() * mCamera.GetProjectionMatrix();
	wvp = Math::Transpose(wvp);
	mConstantBuffer.Update(&wvp);

	// bind texture and draw
	TextureManager::Get()->BindPS(textureId, 0);
	mesh.Render();

	// return wolrd translation
	return Math::GetTranslation(world);
}

Math::Vector3 GameState::ComputePlanetPosition(float rotation, float orbitRotation, float orbitDistance)
{
	// same math as RenderPlanet but without updating the GPU or rendering
	Math::Matrix4 localRot = Math::Matrix4::RotationY(rotation);
	Math::Matrix4 trans = Math::Matrix4::Translation(orbitDistance, 0.0f, 0.0f);
	Math::Matrix4 orbitRot = Math::Matrix4::RotationY(orbitRotation);

	Math::Matrix4 world = orbitRot * trans * localRot;
	return Math::GetTranslation(world);
}

// render earth =====================================================
//Math::Matrix4 earthMatRot = Math::Matrix4::RotationY(mPlanetRotation);          // self spin
//Math::Matrix4 earthMatTrans = Math::Matrix4::Translation(mPlanetOrbitDistance, 0.0f, 0.0f);     // orbit radius
//Math::Matrix4 earthMatOrbitRot = Math::Matrix4::RotationY(mPlanetOrbitRotation); // orbit around sun
//Math::Matrix4 earthMatWorld = earthMatOrbitRot * earthMatTrans * earthMatRot;
//wvp = earthMatWorld * matView * matProj;
//wvp = Math::Transpose(wvp);
//mConstantBuffer.Update(&wvp);
//Math::Vector3 position = Math::GetTranslation(earthMatWorld);
//const Math::Vector3 offset = { 3.0f, 2.0f, 0.0f };
//mCamera.SetPosition(position + offset);
//mCamera.SetLookAt(position);
//// assign textures
//TextureManager::Get()->BindPS(mEarthTextureId, 0);
//// render object
//mEarthMeshBuffer.Render();