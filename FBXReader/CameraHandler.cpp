#include "CameraHandler.h"


CameraHandler::CameraHandler()
{

}

CameraHandler::~CameraHandler()
{

}

void CameraHandler::GetCamPos(FbxCamera* pCamera, double* pTargetPos)
{
	
	FbxDouble3 tmp = pCamera->Position.Get();
	std::cout << "Camera Position" << std::endl;

	pTargetPos[0] = (double)tmp[0];
	std::cout << "x: " << pTargetPos[0] << " ";

	pTargetPos[1] = (double)tmp[1];
	std::cout << "y: " << pTargetPos[1] << " ";

	pTargetPos[2] = (double)tmp[2];
	std::cout << "z: " << pTargetPos[2] << " " << std::endl;
}

void CameraHandler::GetCameraData(FbxNode* pNode)
{
	
	if (pNode->GetCamera())
	{
		std::cout << "CAMERA!!!!" << std::endl;
		std::cout << pNode->GetName() << std::endl;
		ProcessCameraData(pNode->GetCamera());
	}
}

void CameraHandler::ProcessCameraData(FbxCamera* pCamera)
{
	
	BRFImporter::CameraHeader cameras;
	
	GetCamPos(pCamera, cameras.position);
	GetCamIntrest(pCamera, cameras.intrest);
	GetCamRoll(pCamera, &cameras.roll);


}

void CameraHandler::GetCamIntrest(FbxCamera* pCamera, double* pTargetIntrest)
{
	FbxDouble3 tmp = pCamera->InterestPosition.Get();

	std::cout << "Camera Intrest Position: " << std::endl;

	pTargetIntrest[0] = (double)tmp[0];
	std::cout << "x: " << pTargetIntrest[0] << " ";

	pTargetIntrest[1] = (double)tmp[1];
	std::cout << "y: " << pTargetIntrest[1] << " ";

	pTargetIntrest[2] = (double)tmp[2];
	std::cout << "z: " << pTargetIntrest[2] << " " << std::endl;
}

void CameraHandler::GetCamRoll(FbxCamera* pCamera, double* pTargetRoll)
{
	pTargetRoll[0] = pCamera->Roll.Get();
	std::cout << "Roll: " << pTargetRoll[0] << " " << std::endl;
}