#pragma once
#include "FbxPrinter.h"
#include "MeshHandler.h"
#include "MaterialHandler.h"
#include "CameraHandler.h"
#include "LightHandler.h"
#include "MorphHandler.h"
#include "BRFImporterStructs.h"

#include "SkeletonHandler.h"
#include "BrfExporter.h"

class FbxImport
{
private:
	FbxPrinter printer;
	MeshHandler meshHandler;
	MaterialHandler materialHandler;
	CameraHandler cameraHandler;
	MorphHandler morphHandler;
	LightHandler lightHandler;
	SkeletonHandler skeletonHandler;



	FbxManager* fbxManager = nullptr;
	FbxIOSettings* ios = nullptr;
	FbxScene* scene = nullptr;
	FbxNode* rootNode = nullptr;


public:
	FbxImport();
	~FbxImport();




	void ConvertFbxToFile(BrfExporter* outputFile);


	void LoadFbxFile(const char* fileName);

	void PrintNode(FbxNode* pNode);
	void PrintScene();


	void GetMeshData(FbxNode* pNode,		std::vector<MeshExport*>* outputMeshes);
	void GetCameraData(FbxNode* pNode,		CameraExporter* outputCameras);
	void GetSkeletonData(FbxNode* pNode,	std::vector<SkeletonExport>* outputSkeletons);
	//void GetAnimationData(FbxNode* pNode, BrfExporter* outputClass); //Maybe connected to skeleton?


	void GetMaterialData(FbxNode* pNode,	MaterialExport* outputMat);
	void GetLightData(FbxNode* pNode,		LightExport* lights);
	void GetMorphData(FbxNode* pNode/*,	std::vector<MorphAnimExport>* outputMorphs*/);
	void GetGroupData(FbxNode* pNode,		std::vector<GroupHeader>* outputGroups);


};

