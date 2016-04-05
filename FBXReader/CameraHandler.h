#ifndef CAMERAHANDLER_H
#define CAMERAHANDLER_H

#include "fbxSDK.h"
#include "CameraStructs.h"


class CameraHandler
{
public:
	CameraHandler();
	~CameraHandler();

	void GetCameraData(FbxNode* pNode);
private:
	void ProcessCameraData(FbxCamera* pCamera);
	void GetCamPos(FbxCamera* pCamera, float* pTargetPos);
	void GetCamIntrest(FbxCamera* pCamera, float* pTargetIntrest);
	void GetCamFOV(FbxCamera* pCamera, float* pTargetFOV);
};

#endif // !CAMERAHANDLER_H

