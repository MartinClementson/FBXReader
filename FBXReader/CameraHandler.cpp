#include "CameraHandler.h"

CameraHandler::CameraHandler()
{

}

CameraHandler::~CameraHandler()
{

}

void CameraHandler::GetCamPos(FbxCamera* pCamera, float* pTargetPos)
{
	
	FbxDouble3 tmp = pCamera->Position.Get();
	std::cout << "Camera Position" << std::endl;

	pTargetPos[0] = (float)tmp[0];
	std::cout << "x: " << pTargetPos[0] << " ";

	pTargetPos[1] = (float)tmp[1];
	std::cout << "y: " << pTargetPos[1] << " ";

	pTargetPos[2] = (float)tmp[2];
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
	CameraStruct cameras;

	GetCamPos(pCamera, cameras.position);
	GetCamIntrest(pCamera, cameras.intrest);
	GetCamFOV(pCamera, &cameras.FOV);


}

void CameraHandler::GetCamIntrest(FbxCamera* pCamera, float* pTargetIntrest)
{
	FbxDouble3 tmp = pCamera->InterestPosition.Get();

	std::cout << "Camera Intrest Position: " << std::endl;

	pTargetIntrest[0] = (float)tmp[0];
	std::cout << "x: " << pTargetIntrest[0] << " ";

	pTargetIntrest[1] = (float)tmp[1];
	std::cout << "y: " << pTargetIntrest[1] << " ";

	pTargetIntrest[2] = (float)tmp[2];
	std::cout << "z: " << pTargetIntrest[2] << " " << std::endl;
}

void CameraHandler::GetCamFOV(FbxCamera* pCamera, float* pTargetFOV)
{

	
	pTargetFOV[0] = (float)pCamera->FieldOfView.Get();
	std::cout << "FOV: " << pTargetFOV[0] << " " << std::endl;
}