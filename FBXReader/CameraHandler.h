#ifndef CAMERAHANDLER_H
#define CAMERAHANDLER_H

#include "fbxSDK.h"
#include "CameraStuct.h"


class CameraHandler
{
public:
	CameraHandler();
	~CameraHandler();

	void GetCameraData(FbxNode* pNode);
private:
	void ProcessCameraData(FbxCamera* pCamera);
	void GetCamPos(FbxCamera* pCamera, float* pTargetPos);
	void GetCamRoll(FbxCamera* pCamera, float* pTargetRoll);
	void GetCamIntrest(FbxCamera* pCamera, float* pTargetIntrest);
};

#endif // !CAMERAHANDLER_H

