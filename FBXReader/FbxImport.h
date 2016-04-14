#pragma once
#include "FbxPrinter.h"
#include "MeshHandler.h"
#include "MaterialHandler.h"
#include "CameraHandler.h"
#include "GroupHandler.h"
#include "LightHandler.h"
#include "AttributeHandler.h"
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
	GroupHandler groupHandler;
	LightHandler lightHandler;
	AttributeHandler attributeHandler;
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
	void GetAttributeData(FbxNode* pNode,   AttributesExport* outPutAttributes);

	void GetMaterialData(FbxNode* pNode,	MaterialExport* outputMat);
	void GetLightData(FbxNode* pNode,		LightExport* lights);
	void GetMorphAnimData(FbxNode* pNode,	std::vector<MorphAnimExport>* outputMorphs);
	void GetGroupData(FbxNode* pNode,		std::vector<GroupExport*>* outputGroups);


};

