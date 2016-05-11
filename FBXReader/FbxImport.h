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

using namespace std;
class FbxImport
{
private:

	SceneMap sceneMap;
	
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
	void GetSkeletonData(FbxNode* pNode,	std::vector<SkeletonExport*>* outputSkeletons);
	//void GetCameraData(FbxNode * pNode, CameraExporter * outputCameras);
	//void GetSkeletonData(FbxNode* pNode,	std::vector<SkeletonExport>* outputSkeletons);
	//void GetAnimationData(FbxNode* pNode, BrfExporter* outputClass); //Maybe connected to skeleton?


	void GetMaterialData(FbxNode* pNode,	MaterialExport* outputMat);
	void GetLightData(FbxNode* pNode,		LightExport* lights);
	void GetMorphData(FbxNode* pNode/*,	std::vector<MorphAnimExport>* outputMorphs*/);
	void GetGroupData(FbxNode* pNode,		std::vector<GroupHeader>* outputGroups);



	void MapMeshes(FbxNode* pNode);
	void MapCameras(FbxNode* pNode);
	void MapSkeletons(FbxNode* pNode);
	//void GetAnimationData(FbxNode* pNode, BrfExporter* outputClass); //Maybe connected to skeleton?


	void MapMaterials(FbxNode* pNode);
	void MapLights(FbxNode* pNode);
	void MapMorphAnim(FbxNode* pNode);
	void MapGroups(FbxNode* pNode);









};

