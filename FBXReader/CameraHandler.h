#ifndef CAMERAHANDLER_H
#define CAMERAHANDLER_H

#include "fbxSDK.h"
#include "BRFImporterStructs.h"


class CameraHandler
{
public:
	CameraHandler();
	~CameraHandler();

	void GetCameraData(FbxNode* pNode);
private:
	void ProcessCameraData(FbxCamera* pCamera);
	void GetCamPos(FbxCamera* pCamera, double* pTargetPos);
	void GetCamIntrest(FbxCamera* pCamera, double* pTargetIntrest);
	void GetCamRoll(FbxCamera* pCamera, double* pTargetRoll);
};

#endif // !CAMERAHANDLER_H

