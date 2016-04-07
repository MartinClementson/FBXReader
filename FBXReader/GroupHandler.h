#pragma once
#include "fbxSDK.h"
#include "BRFImporterStructs.h"

class GroupHandler
{

public:
	GroupHandler();
	~GroupHandler();

	void GetGroupData(FbxNode* pNode);

private:

	
	void ProcessGroupData(FbxNode* pGroup,FbxLight*pLight,FbxMesh*pMesh,FbxCamera*pCamera);

	void GetTranslation(FbxNode* pNode,double translation);
	void GetScaling(FbxNode* pNode, double scaling);
	void GetRotation(FbxNode * pNode, double rotation);
	void GetName(FbxNode*pNode, char name);
	void GetId(FbxNode*pNode, unsigned int id);
	void GetParentId(FbxNode*pNode, unsigned int id);

};