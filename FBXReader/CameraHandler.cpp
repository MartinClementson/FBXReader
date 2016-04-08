#include "CameraHandler.h"


CameraHandler::CameraHandler()
{

}

CameraHandler::~CameraHandler()
{

}



void CameraHandler::GetCameraData(FbxNode* pNode, CameraExporter* outCamera)
{
	for (int j = 0; j < pNode->GetChildCount(); j++)
		GetCameraData(pNode->GetChild(j), outCamera);
	
	if (pNode->GetCamera())
	{
		//std::cout << "CAMERA!!!!" << std::endl;
		std::cout << pNode->GetName() << std::endl;
		ProcessCameraData(pNode->GetCamera(), outCamera);
	}
}

void CameraHandler::ProcessCameraData(FbxCamera* pCamera, CameraExporter* outCamera)
{
	
	BRFImporter::CameraHeader cameras;

	memcpy(cameras.camName, pCamera->GetName(), sizeof(char) * 256);
	
	GetCamPos(pCamera, cameras.position);
	GetCamIntrest(pCamera, cameras.intrest);
	GetCamRoll(pCamera, &cameras.roll);

	outCamera->cameras->push_back(cameras);


}

void CameraHandler::GetCamPos(FbxCamera* pCamera, double* pTargetPos)
{

	FbxDouble3 tmp = pCamera->Position.Get();

	pTargetPos[0] = (double)tmp[0];
	pTargetPos[1] = (double)tmp[1];
	pTargetPos[2] = (double)tmp[2];
}

void CameraHandler::GetCamIntrest(FbxCamera* pCamera, double* pTargetIntrest)
{
	FbxDouble3 tmp = pCamera->InterestPosition.Get();

	pTargetIntrest[0] = (double)tmp[0];
	pTargetIntrest[1] = (double)tmp[1];
	pTargetIntrest[2] = (double)tmp[2];

}

void CameraHandler::GetCamRoll(FbxCamera* pCamera, double* pTargetRoll)
{
	pTargetRoll[0] = pCamera->Roll.Get();
}