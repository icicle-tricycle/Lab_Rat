#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Sandbox"); // Window Name

	// Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
	//if this line is in Init Application it will depend on the .cfg file, if it
	//is on the InitVariables it will always force it regardless of the .cfg
	m_v4ClearColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);
}

void AppClass::InitVariables(void)
{
	cube = new GameObject(IDENTITY_M4, vector3(0), vector3(0));
	matrix4 cubeMatrix = IDENTITY_M4;
	
	m_floor = new PrimitiveClass();
	m_floor->GeneratePlane(80.0f, vector3(1.0f));
	floorMatrix = glm::rotate(IDENTITY_M4, 90.0f, REAXISX);
	m_wallX1 = new PrimitiveClass();
	m_wallX1->GeneratePlane(80.0f, vector3(1.0f));
	wallX_Matrix1 = glm::rotate(IDENTITY_M4, 90.0f, REAXISY);
	wallX_Matrix1 *= glm::translate(vector3(0.0f, 0.0f, -40.0f));
	m_wallX2 = new PrimitiveClass();
	m_wallX2->GeneratePlane(80.0f, vector3(1.0f));
	wallX_Matrix2 = glm::rotate(IDENTITY_M4, 90.0f, REAXISY);
	wallX_Matrix2 *= glm::translate(vector3(0.0f, 0.0f, 40.0f));
	m_wallZ1 = new PrimitiveClass();
	m_wallZ1->GeneratePlane(80.0f, vector3(1.0f));
	wallZ_Matrix1 = IDENTITY_M4;
	wallZ_Matrix1 *= glm::translate(vector3(0.0f, 0.0f, 40.0f));
	m_wallZ2 = new PrimitiveClass();
	m_wallZ2->GeneratePlane(80.0f, vector3(1.0f));
	wallZ_Matrix2 = IDENTITY_M4;
	wallZ_Matrix2 *= glm::translate(vector3(0.0f, 0.0f, -40.0f));
	
	//Reset the selection to -1, -1
	m_selection = std::pair<int, int>(-1, -1);
	//Set the camera position
	m_pCameraMngr->SetPositionTargetAndView(
		vector3(0.0f, 15.0f, 15.0f),//Camera position
		vector3(0.0f, 3.0f, 0.0f),//What Im looking at
		REAXISY);//What is up
	//Load a model onto the Mesh manager
	//m_pMeshMngr->LoadModel("Lego\\Unikitty.bto", "Unikitty");
	//m_pMeshMngr->AddPlaneToQueue(matrix4(vector4(0.0f)), RERED);
	m_pMeshMngr->AddCubeToQueue(cubeMatrix, RERED, SOLID);
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	//Call the arcball method
	ArcBall();
	
	//Set the model matrix for the first model to be the arcball
	//m_pMeshMngr->SetModelMatrix(ToMatrix4(m_qArcBall), 0);
	
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
	switch (m_pCameraMngr->GetCameraMode())
	{
	default: //Perspective
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XZ); //renders the XY grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOX:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::YZ, RERED * 0.75f); //renders the YZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOY:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XZ, REGREEN * 0.75f); //renders the XZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOZ:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY, REBLUE * 0.75f); //renders the XY grid with a 100% scale
		break;
	}

	m_pMeshMngr->AddCubeToQueue(cube->position, RERED, SOLID);
	
	m_pMeshMngr->Render(); //renders the render list
	m_floor->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), floorMatrix);

	m_wallX1->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), wallX_Matrix1);
	m_wallX2->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), wallX_Matrix2);
	m_wallZ1->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), wallZ_Matrix1);
	m_wallZ2->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), wallZ_Matrix2);

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	SafeDelete(cube);
	super::Release(); //release the memory of the inherited fields
}