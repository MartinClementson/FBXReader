#pragma once
#ifndef GROUPHANDLER_H
#define GROUPHANDLER_H



#include "fbxSDK.h"
#include "BRFImporterStructs.h"
#include "CameraHandler.h"
#include "MeshHandler.h"
//#include "LightHandler.h"

class GroupHandler
{

public:
	GroupHandler();
	~GroupHandler();

	void GetGroupData(FbxNode* pNode);

private:

	
	void ProcessGroupData(FbxNode* pGroup);

	/*void GetTranslation(FbxNode* pNode,double translation);
	void GetScaling(FbxNode* pNode, double scaling);
	void GetRotation(FbxNode * pNode, double rotation);
	void GetName(FbxNode*pNode, char name);
	void GetId(FbxNode*pNode, unsigned int id);
	void GetParentId(FbxNode*pNode, unsigned int id);*/

};
#endif // !GROUPHANDLER