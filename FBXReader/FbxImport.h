#pragma once
#include "FbxPrinter.h"
#include "MeshHandler.h"
class FbxImport
{
private:
	FbxPrinter printer;
	MeshHandler meshHandler;


	FbxManager* fbxManager;
	FbxIOSettings* ios;
	FbxScene* scene;
	FbxNode* rootNode;

public:
	FbxImport();
	~FbxImport();




	void ConvertFbxToFile(dummyStructClass* outputFile);

	void LoadFbxFile(const char* fileName);

	void PrintNode(FbxNode* pNode);
	void PrintScene();

	dummyStructVert GetMeshData(FbxNode* pNode);

			//+ ourFileMeshStruct             GetMeshData(FbxNode* pNode)
			//+ ourFileCamStruct               GetCameraData(FbxNode* pNode)
			//+ ourFileSkeletontStruct        GetSkeletonData(FbxNode* pNode)
			//+ ourFileSkeletonAnimStruct GetAnimationData(FbxNode* pNode)
			//+ ourFileMaterialStruct          GetMaterialData(FbxNode* pNode)
			//+ ourFileLightStruct               GetLightData(FbxNode* pNode)
			//+ ourFileMorphAnimStruct     GetMorphAnimData(FbxNode* pNode)
			//+ ourFileGroupStruct             GetGroupData(FbxNode* pNode)
			//+ ourFileAttributesStruct        GetAttributesData(FbxNode* pNode)
};

