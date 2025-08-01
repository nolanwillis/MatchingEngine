#include "GameObject.h"
#include "Mat4.h"
#include "GraphicsObject.h"

#include <assert.h>

GameObject::GameObject(GraphicsObject* pGraphicsObject, bool simulatePhysics, Trans T, Scale S, 
	Quat Q)
	:
	pGraphicsObject(pGraphicsObject),
	S(S),
	Q(Q),
	T(T),
	simulatePhysics(false)
{
	assert(pGraphicsObject);
	this->pGraphicsObject->worldMatrix = S * Q * T;
}

void GameObject::Update(float deltaTime)
{
	//this->poRigidBody->Update(deltaTime);
	this->pGraphicsObject->worldMatrix = S * Q * T;
}
void GameObject::Draw()
{
	this->pGraphicsObject->Draw();
}
