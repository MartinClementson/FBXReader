#ifndef CAMERAHANDLER_H
#define CAMERAHANDLER_H

#include "fbxSDK.h"
#include "BRFImporterStructs.h"
#include "CameraExport.h"


class CameraHandler
{
public:
	CameraHandler();
	~CameraHandler();

	void GetCameraData(FbxNode* pNode, CameraExporter* outCamera);
private:
	void ProcessCameraData(FbxCamera* pCamera, CameraExporter* outCamera);
	void GetCamPos(FbxCamera* pCamera, double* pTargetPos);
	void GetCamIntrest(FbxCamera* pCamera, double* pTargetIntrest);
	void GetCamRoll(FbxCamera* pCamera, double* pTargetRoll);
};

#endif // !CAMERAHANDLER_H

