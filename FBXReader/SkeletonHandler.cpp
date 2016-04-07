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
		jointCount = 0;
		std::cout << "skeleton name: " << pNode->GetName() << "\n";
		ProcessData(pNode);
	}
}

void SkeletonHandler::ProcessData(FbxNode * pNode)
{
	//a joint can have several things as children here we
	//are controlling the proccesserd node to see that it
	//is in fact a joint
	if (pNode->GetSkeleton())
	{
		//joint count will keep the coun t of all the joints in a skeleton
		jointCount += 1;
		std::cout << "currentJointCount: " << jointCount << "\n";

		//we need to get the skeleton to check if it's the
		//root node
		ProcessPosition(pNode);
		FbxSkeleton *skel = pNode->GetSkeleton();

		if (skel->IsSkeletonRoot())
		{
			std::cout << "\n it's the root!!! \n";
			//assign the parent int to 0 here later
		}
		else
		{
			std::cout << "it's a child\n";

			//assign the parent system here later, we can now effectively get the parents
			FbxNode *parent = pNode->GetParent();
			std::cout << "This is the parent: " << parent->GetName() << "\n";
		}

		//Recursively checking itself
		for (int i = 0; i < pNode->GetChildCount(); i++)
			ProcessData(pNode->GetChild(i));
	}
	return;
}

void SkeletonHandler::ProcessPosition(FbxNode * pNode)
{
	FbxDouble3 translation = pNode->LclTranslation.Get();
	FbxDouble3 rotation = pNode->LclRotation.Get();
	FbxDouble3 scaling = pNode->LclScaling.Get();

	//just a temporary print, store the positions here
	std::cout << "JointName  : " << pNode->GetName() << "\n\t";
	std::cout << "Translation: (" << translation[0] << "," << translation[1] << "," << translation[2] << ")" << "\n\t";
	std::cout << "Rotation   : (" << rotation[0] << "," << rotation[1] << "," << rotation[2] << ")" << "\n\t";
	std::cout << "Scale      : (" << scaling[0] << "," << scaling[1] << "," << scaling[2] << ")\n" << "\n\t";
}
