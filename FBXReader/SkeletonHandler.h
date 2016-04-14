#pragma once
#include "fbxSDK.h"
#include "BRFImporterStructs.h"
#include "BrfExporter.h"
class SkeletonHandler
{
public:
	SkeletonHandler();
	~SkeletonHandler();

	void GetSkeletonData(FbxNode * pNode, std::vector<SkeletonExport*>* outputSkeletons);
private:
#pragma region structs
	struct layer
	{
		FbxString layerName;
		unsigned int ID;
	};
#pragma endregion
#pragma region attributes
	int jointCount;
	int jointID;
	int animationID;
	std::vector<layer> skeletonLayers;
#pragma endregion
#pragma region functions
	void ProcessData(FbxNode * pNode, SkeletonExport &outputSkeleton);
	void ProcessPosition(FbxNode * pNode, JointHeader &skeletonJoint);
	void ProcessKeyFrames(FbxNode * pNode, SkeletonExport &outputSkeleton);
	void ProcessJoints(FbxMesh * pMesh, JointHeader &skeletonJoint);
	int getLayerID(FbxString input);
#pragma endregion
};

