#include "SkeletonHandler.h"



SkeletonHandler::SkeletonHandler()
{
}


SkeletonHandler::~SkeletonHandler()
{
}

void SkeletonHandler::GetSkeletonData(FbxNode * pNode, std::vector<SkeletonExport>* outputSkeletons)
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
		//joint count will keep the count of all the joints in a skeleton
		jointCount += 1;
		std::cout << "currentJointCount: " << jointCount << "\n";

		FbxSkeleton *skel = pNode->GetSkeleton();

		ProcessKeyFrames(pNode);

		/*ProcessPosition(pNode);
		FbxTimeSpan animTime;
		pNode->GetAnimationInterval(animTime);
		FbxAnimEvaluator *anim = pNode->GetAnimationEvaluator();
		FbxVector4 test = anim->GetNodeLocalTranslation(pNode, animTime.GetStart(), pNode->eSourcePivot, false, false);*/
		/*FbxScene* scene = pNode->GetScene();
		FbxAnimStack* lAnimstack = scene->GetSrcObject<FbxAnimStack>(0);
		for (int i = 0; i < lAnimstack->GetSrcObjectCount<FbxAnimLayer>(); i++)
		{
			FbxAnimLayer* pAnimLayer = lAnimstack->GetMember<FbxAnimLayer>(i);
			FbxAnimCurve *curve = pNode->LclTranslation.GetCurve(pAnimLayer, FBXSDK_CURVENODE_COMPONENT_X);
			ProcessCurve(curve);
		}*/

		//we need to get the skeleton to check if it's the
		//root node
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
			std::cout << "This is the parent: " << parent->GetName() << "\n\n";
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

void SkeletonHandler::ProcessKeyFrames(FbxNode * pNode)
{
	FbxScene * scene = pNode->GetScene();

	//Getting the number of animation stacks for this mesh
	//seeing as you can have different ones such as (running, walking...)
	int numAnimations = scene->GetSrcObjectCount<FbxAnimStack>();
	for (int animIndex = 0; animIndex < numAnimations; animIndex++)
	{
		//getting the current stack and evaluator
		FbxAnimStack *animStack = (FbxAnimStack*)scene->GetSrcObject<FbxAnimStack>(animIndex);
		FbxAnimEvaluator *animEval = scene->GetAnimationEvaluator();
		std::cout << animStack->GetName();
		//so far so good

		int numLayers = animStack->GetMemberCount();
		for (int layerIndex = 0; layerIndex < numLayers; layerIndex++)
		{
			FbxAnimLayer *animLayer = (FbxAnimLayer*)animStack->GetMember(layerIndex);
			std::cout << animLayer->GetName();

			FbxAnimCurve * translationCurve = pNode->LclTranslation.GetCurve(animLayer);
			FbxAnimCurve * rotationCurve = pNode->LclRotation.GetCurve(animLayer);
			FbxAnimCurve * scalingCurve = pNode->LclScaling.GetCurve(animLayer);

			if (scalingCurve != NULL)
			{
				//getting the number of set key for this attrubute
				//for this joint
				int numKeys = scalingCurve->KeyGetCount();
				for (int keyIndex = 0; keyIndex < numKeys; keyIndex++)
				{
					FbxTime frameTime = scalingCurve->KeyGetTime(keyIndex);
					FbxDouble3 scalingVector = pNode->EvaluateLocalScaling(frameTime);
					float x = (float)scalingVector[0];
					float y = (float)scalingVector[1];
					float z = (float)scalingVector[2];

					float frameSeconds = (float)frameTime.GetSecondDouble();
				}
			}
			else
			{
				//if the animation layer doesnt have a scaling curve, make a default one
				FbxDouble3 scalingVector = pNode->LclScaling.Get();
				float x = (float)scalingVector[0];
				float y = (float)scalingVector[1];
				float z = (float)scalingVector[2];
			}
			if (rotationCurve != NULL)
			{
				//getting the number of set key for this attrubute
				//for this joint
				int numKeys = rotationCurve->KeyGetCount();
				for (int keyIndex = 0; keyIndex < numKeys; keyIndex++)
				{
					FbxTime frameTime = rotationCurve->KeyGetTime(keyIndex);
					FbxDouble3 rotationVector = pNode->EvaluateLocalRotation(frameTime);
					float x = (float)rotationVector[0];
					float y = (float)rotationVector[1];
					float z = (float)rotationVector[2];

					float frameSeconds = (float)frameTime.GetSecondDouble();
				}
			}
			else
			{
				//if the animation layer doesnt have a scaling curve, make a default one
				FbxDouble3 rotationVector = pNode->LclRotation.Get();
				float x = (float)rotationVector[0];
				float y = (float)rotationVector[1];
				float z = (float)rotationVector[2];
			}
			if (translationCurve != NULL)
			{
				//getting the number of set key for this attrubute
				//for this joint
				int numKeys = translationCurve->KeyGetCount();
				for (int keyIndex = 0; keyIndex < numKeys; keyIndex++)
				{
					FbxTime frameTime = translationCurve->KeyGetTime(keyIndex);
					FbxDouble3 translationVector = pNode->EvaluateLocalTranslation(frameTime);
					float x = (float)translationVector[0];
					float y = (float)translationVector[1];
					float z = (float)translationVector[2];

					float frameSeconds = (float)frameTime.GetSecondDouble();
				}
			}
			else
			{
				//if the animation layer doesnt have a scaling curve, make a default one
				FbxDouble3 translationVector = pNode->LclTranslation.Get();
				float x = (float)translationVector[0];
				float y = (float)translationVector[1];
				float z = (float)translationVector[2];
			}
		}
	}
}

void SkeletonHandler::ProcessJoints(FbxMesh * pMesh)
{
}
