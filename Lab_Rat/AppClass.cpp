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
	//cube = new GameObject("cube", vector3(0.0f), vector3(0.0f), vector3(0.0f),1.0f);

	//BOManager = BoundingObjectManager::GetInstance();
	//GOManager = GameObjectManager::GetInstance();

	m_pMeshMngr->LoadModel("Minecraft\\Steve.obj", "Steve");
	/*m_pMeshMngr->LoadModel("Minecraft\\Creeper.obj", "Creeper");
	m_pMeshMngr->LoadModel("Sorted\\Plane.obj", "Plane");
	m_pMeshMngr->LoadModel("BackedUp\\Cube.obj", "Cube");*/
	m_pMeshMngr->InstanceCuboid(vector3(30, 1, 20), REBLACK, "Floor");
	m_pMeshMngr->InstanceCuboid(vector3(30, 10, 1), REWHITE, "WallBack");
	m_pMeshMngr->InstanceCuboid(vector3(30, 10, 1), REWHITE, "WallFront");
	m_pMeshMngr->InstanceCuboid(vector3(1, 10, 20), REWHITE, "WallLeft");
	m_pMeshMngr->InstanceCuboid(vector3(1, 10, 20), REWHITE, "WallRight");
	/*BOManager->addBox(m_pMeshMngr->GetVertexList("Steve"));
	BOManager->addBox(m_pMeshMngr->GetVertexList("Creeper"), "Creeper");
	BOManager->addBox(m_pMeshMngr->GetVertexList("Plane"), "Plane");
	BOManager->addBox(m_pMeshMngr->GetVertexList("Cube"), "Cube");*/

	//create game objects from loaded models
	player = new GameObject("Steve");
	floor = new GameObject("Floor");
	wallBack = new GameObject("WallBack");
	wallFront = new GameObject("WallFront");
	wallLeft = new GameObject("WallLeft");
	wallRight = new GameObject("WallRight");


	//set object properties
	player->SetModelMatrix(glm::translate(vector3(0, 5, 0)));
	player->SetVelocity(vector3(0, -.1, 0));

	floor->SetModelMatrix(glm::translate(vector3(0, 0, 0)));
	wallBack->SetModelMatrix(glm::translate(vector3(0, 0, -10)));
	wallFront->SetModelMatrix(glm::translate(vector3(0, 0, 10)));
	wallLeft->SetModelMatrix(glm::translate(vector3(-15, 0, 0)));
	wallRight->SetModelMatrix(glm::translate(vector3(15, 0, 0)));



	//What is this?
	/*m_pMeshMngr->SetModelMatrix(glm::translate(vector3(-5.0f, 2.0f, 0.0f)), "Creeper");
	m_pMeshMngr->SetModelMatrix(glm::translate(vector3(2.0f, 2.0f, 0.0f)), "Plane");

	m_pMeshMngr->SetModelMatrix(
		glm::translate(
			glm::scale(vector3(3.0f, 0.0f, 3.0f)),
			vector3(0.0f, 0.0f, 0.0f)),
		"Cube"
		);

	/*BOManager->addBox(m_pMeshMngr->GetVertexList("Steve"), "Steve");
	BOManager->addBox(m_pMeshMngr->GetVertexList("Creeper"), "Creeper");*/
	//Reset the selection to -1, -1
	m_selection = std::pair<int, int>(-1, -1);
	//Set the camera position
	m_pCameraMngr->SetPositionTargetAndView(
		vector3(0.0f, 15.0f, 15.0f),//Camera position
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
	if (player->IsColliding(floor))
	{
		vector3 v3Velocity = player->GetVelocity();
		v3Velocity.y = 0;
		player->SetVelocity(v3Velocity);
	}

	//add game objects to render list
	player->AddToRenderList(true);
	floor->AddToRenderList(true);
	
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//BOManager->reAlign();


	//BOManager->checkCollisions();

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
	switch (m_pCameraMngr->GetCameraMode())
	{
	default: //Perspective
		m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::XZ, RERED * 0.75f);
		//m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XZ); //renders the XY grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOX:
		m_pMeshMngr->AddGridToRenderList/*AddGridToQueue*/(1.0f, REAXIS::YZ, RERED * 0.75f); //renders the YZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOY:
		m_pMeshMngr->AddGridToRenderList/*AddGridToQueue*/(1.0f, REAXIS::XZ, REGREEN * 0.75f); //renders the XZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOZ:
		m_pMeshMngr->AddGridToRenderList/*AddGridToQueue*/(1.0f, REAXIS::XY, REBLUE * 0.75f); //renders the XY grid with a 100% scale
		break;
	}
	
	//m_pMeshMngr->AddCubeToQueue(cube->position, RERED, SOLID);
	//m_pMeshMngr->AddCubeToRenderList(cube->position, RERED, SOLID);

	//BOManager->checkCollisions();

	//for each BO
	/*for (uint i = 0; i < BOManager->boundingObjects.size(); i++)
	{
		if (BOManager->boundingObjects[i]->IsVisible())
		{
			MeshClass* temp = new MeshClass();

			//handle mesh here? Should it be a mesh?...

			vector3 tMax = BOManager->boundingObjects[i]->GetMax();
			vector3 tMin = BOManager->boundingObjects[i]->GetMin();
			vector3 tMid = BOManager->boundingObjects[i]->GetCentroid();

			temp->AddVertexPosition(vector3(tMin.x, tMin.y, tMin.z));
			temp->AddVertexPosition(vector3(tMin.x, tMin.y, tMax.z));
			temp->AddVertexPosition(vector3(tMin.x, tMax.y, tMin.z));
			temp->AddVertexPosition(vector3(tMin.x, tMax.y, tMax.z));
			temp->AddVertexPosition(vector3(tMax.x, tMin.y, tMin.z));
			temp->AddVertexPosition(vector3(tMax.x, tMin.y, tMax.z));
			temp->AddVertexPosition(vector3(tMax.x, tMax.y, tMin.z));
			temp->AddVertexPosition(vector3(tMax.x, tMax.y, tMax.z));

			matrix4 tempWorldMatrix = IDENTITY_M4;
			tempWorldMatrix = glm::translate(tMid);

			m_pMeshMngr->AddMeshToRenderList(temp, tempWorldMatrix);
		}
	}*/
	
	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ResetRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	SafeDelete(player);
	SafeDelete(floor);
	SafeDelete(wallBack);
	SafeDelete(wallFront);
	SafeDelete(wallLeft);
	SafeDelete(wallRight);

	SafeDelete(cube);
	super::Release(); //release the memory of the inherited fields
}