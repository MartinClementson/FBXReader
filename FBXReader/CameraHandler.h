#ifndef CAMERAHANDLER_H
#define CAMERAHANDLER_H

#include "fbxSDK.h"


class CameraHandler
{
public:
	CameraHandler();
	~CameraHandler();

	void GetCameraData(FbxNode* pNode);
private:
	void GetCamPos(FbxCamera* pCamera, FbxNode* pTargetNode);
};

#endif // !CAMERAHANDLER_H

