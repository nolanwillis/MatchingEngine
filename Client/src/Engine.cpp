#include "Engine.h"
#include "Camera.h"
#include "ColorGraphicsObject.h"
#include "ColorShaderObject.h"
#include "DNodeList.h"
#include "DX11Manager.h"
#include "GameObject.h"
#include "QuadMesh.h"
#include "TimeAmount.h"

#include <assert.h>
#include <cstdio>

bool Engine::LoadContent()
{
	// Create the camera.
	Vec3 upVect(0.0f, 1.0f, 0.0f);
	Vec3 tarVect(0.0f, 0.0f, -10.0f);
	Vec3 camPosA(0.0f, 0.0f, 0.0f);
	this->pCameraA = new Camera();
	this->pCameraA->SetOrientAndPosition(upVect, tarVect, camPosA);
	this->pCameraA->SetPerspective(50.0f, DX11Manager::GetAspectRatio(), 0.1f, 1000.0f);

	// Create the meshes.
	this->pQuadMesh = new QuadMesh();
	
	
	// Create the graphic objects.
	Vec4 color = { 1.0f, 0.0f, 0.0f, 0.0f };
	this->pPlayerGraphicsObject = new ColorGraphicsObject
	(
		this->pQuadMesh,
		this->pShaderObject,
		color
	);
	
	// Create the game objects.
	this->pPlayerGameObject = new GameObject(this->pPlayerGraphicsObject,
		false,
		Trans(-1.0f, 0.0f, -5.0f),
		Scale(0.5f, 0.5f, 1.0f)
	);

	testTimer.Start();

	return true;
}

void Engine::Update(float deltaTime)
{
	pCameraA->Update();
	if (testTimer.Stop() == 5 * TimeAmount(TimeAmount::Duration::ONE_SECOND))
	{
		std::printf("5 seconds reached!\n");
	}
}

void Engine::Draw()
{
	DX11Manager::SetDefaultTargetMode();

	pPlayerGameObject->Draw();
}

void Engine::UnloadContent()
{
	delete this->pQuadMesh;
	delete this->pCameraA;
}
