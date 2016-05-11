#include "MorphHandler.h"

#pragma region Init & Destruct

MorphHandler::MorphHandler()
{

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

	processKeyFrames(pNode, output);

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
	}
}

void MorphHandler::processKeyFrames(FbxNode * pNode, MorphAnimExport & output)
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

			//if (translationCurve != NULL ||
			//	rotationCurve != NULL ||
			//	scalingCurve != NULL)
			//	//jointCount += 1;
			//	addLayerJointCount((FbxString)animStack->GetName());


			//FbxTimeSpan animTime;
			//pNode->GetAnimationInterval(animTime, animStack);
			//FbxTime tid = animTime.GetStop();


			int max = 0;

			//can have three different matrices and in the end multiply them into the real one!
			//std::vector<DirectX::XMMATRIX> scaleMatrix;
			std::vector<FbxAMatrix> rotationMatrix;
			std::vector<FbxAMatrix> translationMatrix;

			//temp
			//std::vector<FbxAMatrix> frameMatrix;

			//if (scalingCurve != NULL)
			//{
			//	//getting the number of set key for this attrubute
			//	//for this joint, store this later for frameCount!
			//	int numKeys = scalingCurve->KeyGetCount();
			//	//double testKeys = scalingCurve->;
			//	FbxTimeSpan terra;
			//	scalingCurve->GetTimeInterval(terra);
			//	FbxTime test = terra.GetDuration();
			//	int bajs = (test.GetFrameCount(FbxTime::eFrames24)+1);
			//	FbxTime kiss;
			//	/*kiss.SetTime(0, 0, 0, 10, 0, FbxTime::eFrames24);
			//	kiss.SetTime(0, 0, 0, 35, 0, FbxTime::eFrames24);
			//	kiss.SetTime(0, 0, 0, 1, 0, FbxTime::eFrames24);
			//	kiss.SetTime(0, 0, 0, 19, 0, FbxTime::eFrames24);*/
			//	
			//	//double kiss = test.GetFrameRate(FbxTime::eFrames24);
			//	//FbxDouble3 test = pNode->EvaluateLocalScaling(frameTime);
			//	//scalingCurve->GetTimeInterval(animTime);
			//	//std::cout << "\nstart: " << "to end: " ;
			//	for (int keyIndex = 0; keyIndex <= bajs; keyIndex += 5)
			//	{
			//		//FbxTime frameTime = scalingCurve->KeyGetTime(keyIndex);
			//		kiss.SetTime(0, 0, 0, keyIndex, 0, FbxTime::eFrames24);
			//		FbxDouble3 scalingVector = pNode->EvaluateLocalScaling(kiss);
			//		float x = (float)scalingVector[0];
			//		float y = (float)scalingVector[1];
			//		float z = (float)scalingVector[2];
			//		//for the worldMatrix of the frame
			//		scaleMatrix.push_back(DirectX::XMMatrixScaling(x, y, z));
			//		//float frameSeconds = (float)frameTime.GetSecondDouble();
			//	}
			//}
			if (rotationCurve != NULL)
			{
				//getting the number of set key for this attrubute
				//for this joint
				FbxTimeSpan span;
				scalingCurve->GetTimeInterval(span);
				FbxTime duration = span.GetDuration();
				int numKeys = (duration.GetFrameCount(FbxTime::eFrames24) + 1);
				FbxTime frameTime;
				//int numKeys = rotationCurve->KeyGetCount();
				for (int keyIndex = 1; keyIndex <= numKeys; keyIndex += 5)
				{
					//FbxTime frameTime = rotationCurve->KeyGetTime(keyIndex);
					if (keyIndex == 6)
						keyIndex = 5;
					frameTime.SetTime(0, 0, 0, keyIndex, 0, FbxTime::eFrames24);
					FbxDouble3 rotationVector = pNode->EvaluateLocalRotation(frameTime);
					float x = (float)rotationVector[0];
					float y = (float)rotationVector[1];
					float z = (float)rotationVector[2];

					//for the worldmatrix of the frame
					DirectX::XMMATRIX tempRotation;
					DirectX::XMMATRIX rotationx = DirectX::XMMatrixRotationX(x);
					DirectX::XMMATRIX rotationy = DirectX::XMMatrixRotationY(y);
					DirectX::XMMATRIX rotationz = DirectX::XMMatrixRotationZ(z);

					tempRotation = rotationx*rotationy; tempRotation = tempRotation*rotationz;
					FbxAMatrix rot;
					//FbxVector4 rotV(x, y, z, 1);
					rot.SetR(FbxVector4(x, y, z, 1));
					rotationMatrix.push_back(rot);


					//float frameSeconds = (float)frameTime.GetSecondDouble();
				}
			}
			if (translationCurve != NULL)
			{
				//getting the number of set key for this attrubute
				//for this joint
				FbxTimeSpan span;
				scalingCurve->GetTimeInterval(span);
				FbxTime duration = span.GetDuration();
				int numKeys = (duration.GetFrameCount(FbxTime::eFrames24) + 1);
				FbxTime frameTime;
				//int numKeys = translationCurve->KeyGetCount();
				for (int keyIndex = 1; keyIndex <= numKeys; keyIndex += 5)
				{
					if (keyIndex == 6)
						keyIndex = 5;
					//FbxTime frameTime = translationCurve->KeyGetTime(keyIndex);
					frameTime.SetTime(0, 0, 0, keyIndex, 0, FbxTime::eFrames24);
					FbxDouble3 translationVector = pNode->EvaluateLocalTranslation(numKeys);
					float x = (float)translationVector[0];
					float y = (float)translationVector[1];
					float z = (float)translationVector[2];
					FbxAMatrix trans;
					trans.SetT(FbxVector4(x, y, z, 1));
					//translationMatrix.push_back(DirectX::XMMatrixTranslation(x, y, z));
					translationMatrix.push_back(trans);
					//double frameSeconds = frameTime.GetSecondDouble();
				}
			}

			//getting the maximum value of keyframes
			//from the number of keyframes

			//add matrix here
			//use int i for frame ID
		}
	}
}
