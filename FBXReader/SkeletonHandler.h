#pragma once
#include "fbxSDK.h"
#include "BRFImporterStructs.h"
#include "BrfExporter.h"
class SkeletonHandler
{
public:
	SkeletonHandler();
	~SkeletonHandler();

	void GetSkeletonData(FbxNode * pNode, std::vector<SkeletonExport>* outputSkeletons);
private:
#pragma region attributes
	int jointCount;
	int jointID;
#pragma endregion
#pragma region functions
	void ProcessData(FbxNode * pNode, SkeletonExport &outputSkeleton);
	void ProcessPosition(FbxNode * pNode, JointHeader &skeletonJoint);
	void ProcessKeyFrames(FbxNode * pNode, SkeletonExport &outputSkeleton);
	void ProcessJoints(FbxMesh * pMesh, int index);
#pragma endregion
};

