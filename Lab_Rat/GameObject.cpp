#include "GameObject.h"

void GameObject::Init()
{
	gravityAffected = true;

	position = ZERO_V3;
	prevPosition = ZERO_V3;
	velocity = ZERO_V3;
	force = ZERO_V3;

	friction = 0.0f;
	mass = 1.0f;
	maxVelocity = 1.0f;

	meshName = "";

	colliderMngr = BoundingObjectManager::GetInstance();
	meshMngr = MeshManagerSingleton::GetInstance();
}

GameObject::GameObject(String name)
{
	Init();
	meshName = name;
	std::vector<vector3> list = meshMngr->GetVertexList(meshName);
	colliderMngr->addBox(list, meshName);
}

GameObject::GameObject(String name, vector3 pos, float objMass)
{
	Init();
	position = pos;
	meshName = name;
	mass = objMass;
	std::vector<vector3> list = meshMngr->GetVertexList(meshName);
	colliderMngr->addBox(list, meshName);
}

GameObject::GameObject(String name, vector3 pos, vector3 vel, vector3 f, float objMass)
{
	Init();
	position = pos;
	velocity = vel;
	force = f;
	meshName = name;
	mass = objMass;
	std::vector<vector3> list = meshMngr->GetVertexList(meshName);
	colliderMngr->addBox(list, meshName);
}
GameObject::GameObject(GameObject const & other) { }
GameObject & GameObject::operator=(GameObject const & other) { return *this; }
GameObject::~GameObject() { }

void GameObject::Update(float deltaTime)
{
	prevPosition = position;

	float fFriction = MapValue(friction, 0.0f, 1.0f, 1.0f, 0.0f);
	force = force * fFriction;

	ApplyGravity(deltaTime);

	vector3 vel = force * deltaTime;
	vel = glm::clamp(velocity, -maxVelocity, maxVelocity);
	position += vel;
	
	matrix4 m4ToWorld = glm::translate(position);

	meshMngr->SetModelMatrix(m4ToWorld, meshName);
	colliderMngr->SetModelMatrix(m4ToWorld, meshName); // Needs to be implemented in the manager
}

void GameObject::Display()
{
	meshMngr->AddInstanceToRenderList(meshName);
}

void GameObject::ApplyForce(vector3 v3_force)
{
	force += v3_force / mass;
}

void GameObject::ApplyGravity(float deltaTime)
{
	if (gravityAffected)
		force += vector3(0.0f, -9.81f, 0.0f) * deltaTime;
}

void GameObject::Release()
{
	
}

