#include "MorphHandler.h"

#pragma region Init & Destruct

MorphHandler::MorphHandler()
{
	tester = 0;
}

MorphHandler::~MorphHandler()
{

}

#pragma endregion

void MorphHandler::GetMorphData(FbxNode* pNode, std::vector<MorphAnimExport>* outputMesh)
{
	FbxGeometry* pGeo = pNode->GetGeometry();
	int morphAnimCount = pGeo->GetDeformerCount(FbxDeformer::eBlendShape);
	int morphChannelCount;
	int targetShapeCount;

	std::cout << "blendCount: " << morphAnimCount << "\n\n";
	if (morphAnimCount > 0)
	{
		MorphAnimExport temp;
		processMorphData(pNode, temp);
		/*for (unsigned int i = 0; i < morphAnimCount; i++)
		{
			FbxBlendShape* morphAnim;
			morphAnim = (FbxBlendShape*)pGeo->GetDeformer(i, FbxDeformer::eBlendShape);
			

			morphChannelCount = morphAnim->GetBlendShapeChannelCount();
			std::cout << "ChannelCount: " << morphChannelCount << "\n\n";

			for (unsigned int j = 0; j < morphChannelCount; j++)
			{
				std::cout << "channel nr: " << j << "\n";

				FbxBlendShapeChannel* morphChannel;
				morphChannel = morphAnim->GetBlendShapeChannel(j);

				std::cout << "ChannelName: " << morphChannel->GetName() << "\n\n";

				targetShapeCount = morphChannel->GetTargetShapeCount();

				std::cout << "Target Shape Count: " << targetShapeCount << "\n\n";
				for (unsigned int k = 0; k < targetShapeCount; k++)
				{
					FbxShape* shape;
					shape = morphChannel->GetTargetShape(k);

					std::cout << "Shape name: " << shape->GetName() << "\n\n";


					int vertexCount = shape->GetControlPointsCount();
					FbxVector4* vertices = shape->GetControlPoints();

					for (int l = 0; l < vertexCount; l++)
					{
						std::cout << " x: " << ((double*)shape->GetControlPointAt(l))[0] << "";
						std::cout << " y: " << ((double*)shape->GetControlPointAt(l))[1] << "";
						std::cout << " z: " << ((double*)shape->GetControlPointAt(l))[2] << "\n\n";
					}
				}
			}
		}*/
	}
}

void MorphHandler::processMorphData(FbxNode * pNode, MorphAnimExport & output)
{
	FbxGeometry* pGeo = pNode->GetGeometry();
	int morphAnimCount = pGeo->GetDeformerCount(FbxDeformer::eBlendShape);
	int morphChannelCount;
	int targetShapeCount;

	//processKeyFrames(pNode, output);

	for (unsigned int i = 0; i < morphAnimCount; i++)
	{
		FbxBlendShape* morphAnim;
		morphAnim = (FbxBlendShape*)pGeo->GetDeformer(i, FbxDeformer::eBlendShape);

		morphChannelCount = morphAnim->GetBlendShapeChannelCount();
		std::cout << "ChannelCount: " << morphChannelCount << "\n\n";

		for (unsigned int j = 0; j < morphChannelCount; j++)
		{
			std::cout << "channel nr: " << j << "\n";

			FbxBlendShapeChannel* morphChannel;
			morphChannel = morphAnim->GetBlendShapeChannel(j);
			morphChannel->GetBlendShapeDeformer();
			std::cout << "ChannelName: " << morphChannel->GetName() << "\n\n";

			targetShapeCount = morphChannel->GetTargetShapeCount();

			std::cout << "Target Shape Count: " << targetShapeCount << "\n\n";
			for (unsigned int k = 0; k < targetShapeCount; k++)
			{
				FbxShape* shape;
				shape = morphChannel->GetTargetShape(k);
				
				
				//processKeyFrames(pNode, output, morphChannel);

				
				FbxScene * scene = pNode->GetScene();

				//Getting the number of animation stacks for this mesh
				//seeing as you can have different ones such as (running, walking...)
				int numAnimations = scene->GetSrcObjectCount<FbxAnimStack>();
				//outputSkeleton.animation
				for (int animIndex = 0; animIndex < numAnimations; animIndex++)
				{
					//getting the current stack and evaluator
					FbxAnimStack *animStack = (FbxAnimStack*)scene->GetSrcObject<FbxAnimStack>(animIndex);
					FbxAnimEvaluator *animEval = scene->GetAnimationEvaluator();
					std::cout << animStack->GetName();
					//so far so good

					//put control here to se if its the same animation layer
					//int layerTest = getLayerID((FbxString)animStack->GetName());
					int numLayers = animStack->GetMemberCount();
					for (int layerIndex = 0; layerIndex < numLayers; layerIndex++)
					{
						FbxAnimLayer *animLayer = (FbxAnimLayer*)animStack->GetMember(layerIndex);

						FbxAnimCurve * deformCurve = morphChannel->DeformPercent.GetCurve(animLayer);
						if (deformCurve != nullptr)
						{
							animatedShapes temp;
							temp.animatedChannels = morphChannel;
							animShapes.push_back(temp);
							//animatedChannels.push_back(morphChannel);
							//animatedTargets.push_back(shape);
						}
					}
				}
				//morphChannel->DeformPercent.GetCurve(0);

				 
				std::cout << "Shape name: " << shape->GetName() << "\n\n";


				int vertexCount = shape->GetControlPointsCount();
				FbxVector4* vertices = shape->GetControlPoints();
				for (int l = 0; l < vertexCount; l++)
				{
					std::cout << " x: " << ((double*)shape->GetControlPointAt(l))[0] << "";
					std::cout << " y: " << ((double*)shape->GetControlPointAt(l))[1] << "";
					std::cout << " z: " << ((double*)shape->GetControlPointAt(l))[2] << "\n\n";
				}
			}
		}
		//tester++;
	}
}

void MorphHandler::processKeyFrames(FbxNode * pNode, animatedShapes &animShape)
{
	FbxScene * scene = pNode->GetScene();

	//Getting the number of animation stacks for this mesh
	//seeing as you can have different ones such as (running, walking...)
	int numAnimations = scene->GetSrcObjectCount<FbxAnimStack>();
	//outputSkeleton.animation
	for (int animIndex = 0; animIndex < numAnimations; animIndex++)
	{
		//getting the current stack and evaluator
		FbxAnimStack *animStack = (FbxAnimStack*)scene->GetSrcObject<FbxAnimStack>(animIndex);
		FbxAnimEvaluator *animEval = scene->GetAnimationEvaluator();
		std::cout << animStack->GetName();
		//so far so good

		//put control here to se if its the same animation layer
		//int layerTest = getLayerID((FbxString)animStack->GetName());
		int numLayers = animStack->GetMemberCount();
		for (int layerIndex = 0; layerIndex < numLayers; layerIndex++)
		{
			FbxAnimLayer *animLayer = (FbxAnimLayer*)animStack->GetMember(layerIndex);
			std::cout << animLayer->GetName();

			FbxAnimCurve * translationCurve = pNode->LclTranslation.GetCurve(animLayer);
			FbxAnimCurve * rotationCurve = pNode->LclRotation.GetCurve(animLayer);
			FbxAnimCurve * scalingCurve = pNode->LclScaling.GetCurve(animLayer);
			
			FbxAnimCurve * deformCurve = animShape.animatedChannels->DeformPercent.GetCurve(animLayer);

			if (deformCurve != nullptr)
			{
				int numKeys = deformCurve->KeyGetCount();
				for (int keyIndex = 0; keyIndex < numKeys; keyIndex++)
				{
					FbxTime frameTime = deformCurve->KeyGetTime(keyIndex);
					animShape.animatedTimes.push_back(frameTime);
					//double deform = animShape.animatedChannels->DeformPercent.EvaluateValue(frameTime);
					//std::cout << "\n" << deform << "\n";
				}
			}
		}
	}
}

void MorphHandler::evaluateAnimation(FbxNode * pNode, MorphAnimExport & output, animatedShapes & animShape)
{
}
