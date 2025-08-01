#ifndef ENGINE_H
#define ENGINE_H

#include "StopWatch.h"

class Camera;
class GameObject;
class GraphicsObject;
class Mesh;
class ShaderObject;
class Texture;

class Engine
{
public:
	Engine() = default;

	// Loads all the content to be used in the game.
	bool LoadContent();
	// Called once per frame, updates the data of objects.
	void Update(float deltaTime);
	// Called once per frame, draws all the objects.
	void Draw();
	// Unloads all the content that was loaded.
	void UnloadContent();

private:
	Camera* pCameraA;
	Mesh* pQuadMesh;
	Texture* pTestTexture;
	ShaderObject* pShaderObject;
	GraphicsObject* pPlayerGraphicsObject;
	GameObject* pPlayerGameObject;
	StopWatch testTimer;
};

#endif
