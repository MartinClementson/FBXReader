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
	void GetCameraData(FbxNode * pNode, std::vector<CameraExporter*>* outCamera);

	void ProcessCameraData(FbxCamera * pCamera, CameraExporter * outCamera);

private:
	void GetCamPos(FbxCamera* pCamera, double* pTargetPos);
	void GetCamRotation(FbxNode* pCamNode, double* pTargetRot);
};

#endif // !CAMERAHANDLER_H

