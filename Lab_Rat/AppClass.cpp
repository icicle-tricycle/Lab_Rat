#include "AppClass.h"

void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Lab Rat"); // Window Name

	// Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
	//if this line is in Init Application it will depend on the .cfg file, if it
	//is on the InitVariables it will always force it regardless of the .cfg
	m_v4ClearColor = vector4(.65f, .65f, .65f, 0.0f);
}

void AppClass::InitVariables(void)
{
	fDuration = 10.0f;
	numTraps = 3.0f;

	//cube = new GameObject("cube", vector3(0.0f), vector3(0.0f), vector3(0.0f),1.0f);

	//BOManager = BoundingObjectManager::GetInstance();
	//GOManager = GameObjectManager::GetInstance();

	//m_pMeshMngr->LoadModel("Minecraft\\Steve.obj", "Steve");
	m_pMeshMngr->LoadModel("RobotKyle\\Scientist.fbx", "Player");
	//m_pMeshMngr->LoadModel("Minecraft\\Creeper.obj", "Creeper");
	m_pMeshMngr->LoadModel("RobotKyle\\RobotKyle.fbx", "Robot");

	/*m_pMeshMngr->LoadModel("Sorted\\Plane.obj", "Plane");
	m_pMeshMngr->LoadModel("BackedUp\\Cube.obj", "Cube");*/
	m_pMeshMngr->InstanceCuboid(vector3(30, 1, 20), REBLACK, "Floor");
	m_pMeshMngr->InstanceCuboid(vector3(30, 10, 1), REWHITE, "WallBack");
	m_pMeshMngr->InstanceCuboid(vector3(30, 10, 1), REWHITE, "WallFront");
	m_pMeshMngr->InstanceCuboid(vector3(1, 10, 20), REWHITE, "WallLeft");
	m_pMeshMngr->InstanceCuboid(vector3(1, 10, 20), REWHITE, "WallRight");
	m_pMeshMngr->InstanceCuboid(vector3(30, 5, 0.25f), vector3(0.3f, 0.45f, 0.6f), "WallCenter");
	

	//create game objects from loaded models
	player = new Player("Player");
	//rat = new GameObject("Creeper");
	rat = new GameObject("Robot");

	floor = new GameObject("Floor");
	wallBack = new GameObject("WallBack");
	wallFront = new GameObject("WallFront");
	wallLeft = new GameObject("WallLeft");
	wallRight = new GameObject("WallRight");
	wallCenter = new GameObject("WallCenter");
	
	Trap* trap = nullptr;
	for (uint i = 0; i < numTraps; i++)
	{
		m_pMeshMngr->InstanceCuboid(vector3(1, 1, 1), vector3(0.8f, 0.20f, 0.4f), "Trap"+ std::to_string(i));
		trap = new Trap("Trap" + std::to_string(i));
		traps.push_back(trap);
		traps[i]->SetModelMatrix(glm::translate(vector3(-7.5f + i*7.5f, .5, -5)));
	}
	std::vector<GameObject*> walls;
	walls.push_back(floor);
	walls.push_back(wallBack);
	walls.push_back(wallFront);
	walls.push_back(wallLeft);
	walls.push_back(wallRight);
	walls.push_back(wallCenter);

	player->SetWalls(walls);


	//set object properties
	matrix4 temp;
	temp = glm::translate(vector3(0, 5, 5));
	temp = glm::scale(temp,vector3(1.2f, 1.2f, 1.2f));
	//player->SetModelMatrix(glm::translate(vector3(0, 5, 5)));
	player->SetModelMatrix(temp);
	player->SetVelocity(vector3(0, -.1, 0));

	//matrix4 temp;
	temp = glm::translate(vector3(-12, 0.5f, -5));
	temp = glm::scale(temp, vector3(.02f, .02f, .02f));
	temp = glm::rotate(temp, 90.0f, 0.0f, 1.0f, 0.0f);
	rat->SetModelMatrix(temp);

	floor->SetModelMatrix(glm::translate(vector3(0, 0, 0)));
	wallBack->SetModelMatrix(glm::translate(vector3(0, 0, -10)));
	wallFront->SetModelMatrix(glm::translate(vector3(0, 0, 10)));
	wallLeft->SetModelMatrix(glm::translate(vector3(-15, 0, 0)));
	wallRight->SetModelMatrix(glm::translate(vector3(15, 0, 0)));
	wallCenter->SetModelMatrix(glm::translate(vector3(0, 0, 0)));

	/*for (uint i = 0; i < numTraps; i++)
	{
		traps[i]->SetModelMatrix(glm::translate(vector3(-10.0f + i*2.0f, .5, -5)));
	}*/

	//Reset the selection to -1, -1
	m_selection = std::pair<int, int>(-1, -1);
	//Set the camera position
	m_pCameraMngr->SetPositionTargetAndView(
		vector3(0.0f, 22.0f, 17.0f),//Camera position
		vector3(0.0f, 3.0f, 0.0f),//What Im looking at
		REAXISY);//What is up
	//Load a model onto the Mesh BOManager
	//m_pMeshMngr->LoadModel("Lego\\Unikitty.bto", "Unikitty");
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh BOManager's time without updating for collision detection
	m_pMeshMngr->Update();

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	//Call the arcball method
	ArcBall();
	
	//Set the model matrix for the first model to be the arcball
	//m_pMeshMngr->SetModelMatrix(ToMatrix4(m_qArcBall), 0);

	player->Update();
	/*if (player->IsColliding(floor))
	{
		vector3 v3Velocity = player->GetVelocity();
		v3Velocity.y = 0;
		player->SetVelocity(v3Velocity);
	}*/

	//RAT LERPING
	//Lets us know how much time has passed since the last call
	double fTimeSpan = m_pSystem->LapClock();

	//cumulative time
	static double fRunTime = 0.0f;
	fRunTime += fTimeSpan;

	if (fRunTime < fDuration)
	{
		float fPercent = MapValue(static_cast<float>(fRunTime), 0.0f, fDuration, 0.0f, 1.0f);
		vector3 v3Position = glm::lerp(vector3(-12, 0.5f, -5), vector3(12, 0.5f, -5), fPercent);
		matrix4 temp;
		temp = glm::translate(v3Position);
		temp = glm::scale(temp, vector3(.02f, .02f, .02f));
		temp = glm::rotate(temp, 90.0f, 0.0f, 1.0f, 0.0f);
		rat->SetModelMatrix(temp);

	}

	//add game objects to render list
	player->AddToRenderList(true);
	rat->AddToRenderList(true);
	floor->AddToRenderList(true);
	wallBack->AddToRenderList(true);
	wallFront->AddToRenderList(true);
	wallLeft->AddToRenderList(true);
	wallRight->AddToRenderList(true);
	wallCenter->AddToRenderList(true);
	for (uint i = 0; i < numTraps; i++)
	{
		traps[i]->AddToRenderList(true);
	}
	
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//print info into the console
	//printf("FPS: %d            \r", nFPS);//print the Frames per Second
	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);

	m_pMeshMngr->Print("Selection: ");
	m_pMeshMngr->PrintLine(m_pMeshMngr->GetInstanceGroupName(m_selection.first, m_selection.second), REYELLOW);
	
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();

	//Render the grid based on the camera's mode:
	//switch (m_pCameraMngr->GetCameraMode())
	//{
	//default: //Perspective
	//	m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::XZ, RERED * 0.75f);
	//	//m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XZ); //renders the XY grid with a 100% scale
	//	break;
	//case CAMERAMODE::CAMROTHOX:
	//	m_pMeshMngr->AddGridToRenderList/*AddGridToQueue*/(1.0f, REAXIS::YZ, RERED * 0.75f); //renders the YZ grid with a 100% scale
	//	break;
	//case CAMERAMODE::CAMROTHOY:
	//	m_pMeshMngr->AddGridToRenderList/*AddGridToQueue*/(1.0f, REAXIS::XZ, REGREEN * 0.75f); //renders the XZ grid with a 100% scale
	//	break;
	//case CAMERAMODE::CAMROTHOZ:
	//	m_pMeshMngr->AddGridToRenderList/*AddGridToQueue*/(1.0f, REAXIS::XY, REBLUE * 0.75f); //renders the XY grid with a 100% scale
	//	break;
	//}
	
	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ResetRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	SafeDelete(player);
	SafeDelete(rat);
	SafeDelete(floor);
	SafeDelete(wallBack);
	SafeDelete(wallFront);
	SafeDelete(wallLeft);
	SafeDelete(wallRight);
	SafeDelete(wallCenter);

	for (uint i = 0; i < numTraps; i++)
	{
		SafeDelete(traps[i]);
	}

	SafeDelete(cube);
	super::Release(); //release the memory of the inherited fields
}