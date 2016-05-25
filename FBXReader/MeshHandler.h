#pragma once
#include "MeshExport.h"
#include "BRFImporterStructs.h"
#include "fbxSDK.h"

class MeshHandler
{
public:
	MeshHandler();
	~MeshHandler();

	void GetMeshData(FbxNode* pNode, std::vector<MeshExport*>* outputMeshes, SceneMap* sceneMap);

private:
	bool isATargetMesh(const char* name);
	bool HasMorphAnim(FbxNode* pNode);
	void ProcessData(FbxMesh* pMesh, MeshExport* mesh, bool hasSkeleton);
	void GetVertPositions(FbxMesh* pMesh, int index, double* targetPos);
	void GetVertNormals(fbxsdk::FbxGeometryElementNormal* pNElement, int index, double* targetNormal);
	void GetVertBiNormals(fbxsdk::FbxGeometryElementBinormal* pBNElement, int index, double* targetBiNormal);
	void GetVertTangents(fbxsdk::FbxGeometryElementTangent* pTElement, int index, double* targetTangent);
	void GetVertTextureUV(fbxsdk::FbxGeometryElementUV* uvElement, int index, double* targetUV);
	void GetSkeletonWeights(fbxsdk::FbxMesh * pMesh, int index, MeshExport* outputMesh);
	bool GetBoundingBox(FbxNode*pNode, OOBBHeader* boundingBox);
	bool IsBoundingBox(FbxNode* pNode);
	bool HasSkeleton(FbxNode* pNode);
	bool IsGroup(FbxNode* pNode);
	void GetPolygonNormals(double* targetNormal, FbxVector4* sourceNormals);
	unsigned int objectID;
	unsigned int weightIndex;

	VertexHeader* tempVertex;

};

