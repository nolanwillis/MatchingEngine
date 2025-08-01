#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Mat4.h"
#include "Quat.h"
#include "Scale.h"
#include "Trans.h"

class GraphicsObject;
class RigidBody;

class GameObject
{
public:
	Scale S;
	Quat Q;
	Trans T;
	
	bool simulatePhysics;

	GameObject() = delete;
	GameObject
	(
		GraphicsObject* pGraphicsObject,
		bool simulatePhysics = false,
		Trans T = {0.0f, 0.0f, 0.0f},
		Scale S = {1.0f, 1.0f, 1.0f}, 
		Quat Q = {0.0f, 0.0f, 0.0f, 1.0f}
	);
	GameObject(const GameObject&) = delete;
	GameObject& operator = (const GameObject&) = delete;
	virtual ~GameObject() = default;

	virtual void Update(float deltaTime);
	virtual void Draw();
	
private:
	GraphicsObject* pGraphicsObject;
	RigidBody* poRigidBody;

};

#endif


