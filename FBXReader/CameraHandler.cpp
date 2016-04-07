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
	FbxDouble tmp = pCamera->Roll.Get();

	pTargetRoll[0] = (float)tmp;
}

void GetCamIntrest(FbxCamera* pCamera, float* pTargetIntrest)
{

}