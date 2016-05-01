#pragma once
#ifndef __GAMEOBJECT_H_
#define __GAMEOBJECT_H_

#include "RE\ReEng.h"

#include "BoundingObjectManager.h"

class GameObject
{
public:
	//variables
	bool gravityAffected;

	vector3 position;
	vector3 prevPosition;
	vector3 velocity;
	vector3 force;

	float friction;
	float mass;
	float maxVelocity;

	String meshName;
	BoundingObjectManager* colliderMngr;
	MeshManagerSingleton* meshMngr;

	//Name. Pos, Vel, Force, and Mass assumed 0.
	GameObject(String name);
	//Name, pos, mass. Force and Vel of 0
	GameObject(String name, vector3 pos, float objMass);
	//Name, Pos, Vel, Force, Mass
	GameObject(String name, vector3 pos, vector3 vel, vector3 f, float objMass);

	GameObject(GameObject const& other);
	GameObject& operator=(GameObject const& other);
	~GameObject();

	void Init();
	void Update(float deltaTime);
	void Display();

	void ApplyForce(vector3 v3_force);
	void ApplyGravity(float deltaTime);

private:
	void Release();
};

#endif
