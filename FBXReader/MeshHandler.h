#pragma once
#include "MeshExport.h"
#include "BRFImporterStructs.h"
#include "fbxSDK.h"
class MeshHandler
{
public:
	MeshHandler();
	~MeshHandler();

	void GetMeshData(FbxNode* pNode, std::vector<MeshExport*>* outputMeshes);

private:
	void ProcessData(FbxMesh* pMesh, MeshExport* mesh);
	void GetVertPositions(FbxMesh* pMesh, int index, double* targetPos);
	void GetVertNormals(fbxsdk::FbxGeometryElementNormal* pNElement, int index, double* targetNormal);
	void GetVertBiNormals(fbxsdk::FbxGeometryElementBinormal* pBNElement, int index, double* targetBiNormal);
	void GetVertTangents(fbxsdk::FbxGeometryElementTangent* pTElement, int index, double* targetTangent);
	void GetVertTextureUV(fbxsdk::FbxGeometryElementUV* uvElement, int index, double* targetUV);
};

