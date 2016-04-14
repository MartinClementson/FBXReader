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
	struct layerJoints
	{
		FbxString layerName;
		unsigned int jointCount;
	};
#pragma endregion
#pragma region attributes
	int jointCount;
	int jointID;
	int animationID;
	std::vector<layer> skeletonLayers;
	std::vector<layerJoints> layerJointCount;
#pragma endregion
#pragma region functions
	void ProcessData(FbxNode * pNode, SkeletonExport &outputSkeleton);
	void ProcessPosition(FbxNode * pNode, JointHeader &skeletonJoint);
	void ProcessKeyFrames(FbxNode * pNode, SkeletonExport &outputSkeleton);
	void ProcessJoints(FbxMesh * pMesh, JointHeader &skeletonJoint);
	void ProcessAnimation(FbxNode * pNode, SkeletonExport &outputSkeleton);
	int getLayerID(FbxString input);
	int getLayerJointCount(FbxString input); //will return -1 if failed
	void addLayerJointCount(FbxString input);

#pragma endregion
};

