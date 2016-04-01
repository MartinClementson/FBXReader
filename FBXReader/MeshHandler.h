#pragma once
#include "fbxSDK.h"
class MeshHandler
{
public:
	MeshHandler();
	~MeshHandler();

	void GetMeshData(FbxNode* pNode);

private:
	void ProcessData(FbxMesh* pMesh);
	void GetVertPositions(FbxMesh* pMesh, int index, float* targetPos);

};

