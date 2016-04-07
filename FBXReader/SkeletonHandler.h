#pragma once
#include "fbxSDK.h"
class SkeletonHandler
{
public:
	SkeletonHandler();
	~SkeletonHandler();

	void GetSkeletonData(FbxNode * pNode);
private:
	void ProcessData(FbxSkeleton * pSkeleton);
};

