#include "CameraHandler.h"

CameraHandler::CameraHandler()
{

}

CameraHandler::~CameraHandler()
{

}

void CameraHandler::GetCamPos(FbxCamera* pCamera, FbxNode* pTargetNode)
{
	
	fbxsdk::FbxDouble3 test;
	test = pCamera->Position.Get();

	

	
}