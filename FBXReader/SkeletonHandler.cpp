#include "SkeletonHandler.h"



SkeletonHandler::SkeletonHandler()
{
}


SkeletonHandler::~SkeletonHandler()
{
}

void SkeletonHandler::GetSkeletonData(FbxNode * pNode)
{
	if (pNode->GetSkeleton())
	{
		std::cout << "skeleton name: " << pNode->GetName() << "\n";
		ProcessData(pNode->GetSkeleton());
	}
}

void SkeletonHandler::ProcessData(FbxSkeleton * pSkeleton)
{
	//pSkeleton->IsSkeletonRoot
	//std::cout << (char*)pSkeleton->GetSkeletonType();
	if (pSkeleton->IsSkeletonRoot())
		std::cout << "\n it's the root!!!";
}
