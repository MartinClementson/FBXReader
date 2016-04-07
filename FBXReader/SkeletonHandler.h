#pragma once
#include "fbxSDK.h"
class SkeletonHandler
{
public:
	SkeletonHandler();
	~SkeletonHandler();

	void GetSkeletonData(FbxNode * pNode);
private:
#pragma region attributes
	int jointCount;
#pragma endregion
#pragma region functions
	void ProcessData(FbxNode * pNode);
	void ProcessPosition(FbxNode * pNode);
	void ProcessKeyFrames(FbxNode * pNode);
#pragma endregion
};

