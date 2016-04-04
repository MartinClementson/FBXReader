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
	
	pTargetPos[0] = (float)tmp[0];
	pTargetPos[1] = (float)tmp[1];
	pTargetPos[2] = (float)tmp[2];
}

void CameraHandler::GetCameraData(FbxNode* pNode)
{
	if (pNode->GetCamera())
	{
		std::cout << pNode->GetName() << std::endl;
		ProcessCameraData(pNode->GetCamera());
	}
}

void CameraHandler::ProcessCameraData(FbxCamera* pCamera)
{
	CameraStruct cameras;

	GetCamPos(pCamera, cameras.position);
	GetCamRoll(pCamera, cameras.roll);


}

void CameraHandler::GetCamRoll(FbxCamera* pCamera, float* pTargetRoll)
{
	FbxDouble3 tmp = pCamera->Roll.Get;

	pTargetRoll[0] = (float)tmp[0];
	pTargetRoll[1] = (float)tmp[1];
	pTargetRoll[2] = (float)tmp[2];
}

void CameraHandler::GetCamIntrest(FbxCamera* pCamera, float* pTargetIntrest)
{
	FbxDouble3 tmp = pCamera->InterestPosition.Get();

	pTargetIntrest[0] = (float)tmp[0];
	pTargetIntrest[1] = (float)tmp[1];
	pTargetIntrest[2] = (float)tmp[2];
}