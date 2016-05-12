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
							processKeyFrames(pNode, temp);
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
				/*for (int l = 0; l < vertexCount; l++)
				{
					std::cout << " x: " << ((double*)shape->GetControlPointAt(l))[0] << "";
					std::cout << " y: " << ((double*)shape->GetControlPointAt(l))[1] << "";
					std::cout << " z: " << ((double*)shape->GetControlPointAt(l))[2] << "\n\n";
				}*/
			}
		}
		//tester++;
	}
	animShapes.shrink_to_fit();
	evaluateAnimation(pNode, output);
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

void MorphHandler::evaluateAnimation(FbxNode * pNode, MorphAnimExport & output)
{
	if (animShapes.size() != 0)
	{
		animatedShapes finalShape;
		
		std::vector<sameChannelAnimation> tempMorphChannels;
		if (animShapes.size() > 1)
		{
			for (int i = 0; i < animShapes.size(); i++)
			{
				for (int j = i + 1; j < animShapes.size(); j++)
				{
					for (int k = 0; k < animShapes.at(i).animatedTimes.size(); k++)
					{
						for (int l = 0; l < animShapes.at(j).animatedTimes.size(); l++)
						{
							sameChannelAnimation temp;
							temp.morphChannels.push_back(animShapes.at(i).animatedChannels);
							if (animShapes.at(i).animatedTimes.at(k) == animShapes.at(j).animatedTimes.at(l))
							{
								temp.morphChannels.push_back(animShapes.at(j).animatedChannels);
								//temp.time = animShapes.at(i).animatedTimes.at(k);
							}
							//if (temp.morphChannels.size() == 1)
							temp.time = animShapes.at(i).animatedTimes.at(k);

							tempMorphChannels.push_back(temp);
						}
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < animShapes.at(0).animatedTimes.size(); i++)
			{
				sameChannelAnimation temp;
				temp.morphChannels.push_back(animShapes.at(0).animatedChannels);
				temp.time = animShapes.at(0).animatedTimes.at(i);
				tempMorphChannels.push_back(temp);
			}
		}
		transferAnimation(pNode, output, tempMorphChannels);
	}
}

void MorphHandler::transferAnimation(FbxNode * pNode, MorphAnimExport & output, std::vector<sameChannelAnimation>& animations)
{
	for (int i = 0; i < animations.size(); i++)
	{

		//if there's only one keyed blend shape at this key
		if (animations.at(i).morphChannels.size() == 1)
		{
			FbxShape * shape = animations.at(i).morphChannels.at(0)->GetTargetShape(0);
			if (animations.at(i).time != 1924423250) //this number is the value for the keyframe 0, which we don't want
			{
				FbxScene * scene = pNode->GetScene();
				int numAnimations = scene->GetSrcObjectCount<FbxAnimStack>();
				for (int animIndex = 0; animIndex < numAnimations; animIndex++)
				{
					//getting the current stack and evaluator
					FbxAnimStack *animStack = (FbxAnimStack*)scene->GetSrcObject<FbxAnimStack>(animIndex);
					FbxAnimEvaluator *animEval = scene->GetAnimationEvaluator();

					int numLayers = animStack->GetMemberCount();
					for (int layerIndex = 0; layerIndex < numLayers; layerIndex++)
					{
						FbxAnimLayer *animLayer = (FbxAnimLayer*)animStack->GetMember(layerIndex);
						FbxAnimCurve * deformCurve = animations.at(i).morphChannels.at(0)->DeformPercent.GetCurve(animLayer);

						//getting the deform procent value
						double deform = animations.at(i).morphChannels.at(0)->DeformPercent.EvaluateValue(animations.at(i).time);
						
						if (deform == 0.0)
						{
							//deform is the same as the base shape, no need to interpolate
							//släng in vertiserna från pNode här
						}
						else if (deform == 100.0)
						{
							//deform value is the same as the "shape" variable, no need to interpolate
							//FbxGeometry* hej = (FbxGeometry*)shape->GetDstObject();
							FbxMesh* pMesh = pNode->GetMesh();
							int polyCount = pMesh->GetPolygonCount();
							std::vector<int> polyVertices;
							std::vector<FbxVector4> polyNormals;

							//getting the custom index for the vertices and normals
							for (int k = 0; k < polyCount; k++)
							{
								for (int l = 0; l < pMesh->GetPolygonSize(k); l++)
								{
									FbxVector4 tempNormal;
									polyVertices.push_back(pMesh->GetPolygonVertex(k, l));
									pMesh->GetPolygonVertexNormal(k, l, tempNormal);
									polyNormals.push_back(tempNormal);
								}
							}

							for (int k = 0; k < polyVertices.size(); k++)
							{
								BRFImporter::MorphVertexHeader tempvertex;
								
								tempvertex.pos[0] = (double)shape->GetControlPointAt(polyVertices.at(k))[0];
								tempvertex.pos[1] = (double)shape->GetControlPointAt(polyVertices.at(k))[1];
								tempvertex.pos[2] = (double)shape->GetControlPointAt(polyVertices.at(k))[2];

								GetPolygonNormals(tempvertex.normal, &polyNormals.at(k));//kolla in denna

								fbxsdk::FbxGeometryElementBinormal * test2 = shape->GetElementBinormal(k);
								//shape->GetBinormals(test2,0);
								std::cout << "bajs";
								//GetVertBiNormals(shape->GetElementBinormal(k), polyVertices.at(k), tempvertex.biTangent);
								//GetVertTangents(shape->GetElementTangent(), polyVertices.at(k), tempvertex.tangent);
								//fyll i med den här
								
							}
						}
						else
						{
							//need to interpolate
						}
					}
				}
			}
		}

		//if there's more shapes keyed
		else
		{
			//hitta värde för fler här
		}
	}
}

void MorphHandler::GetPolygonNormals(double * targetNormal, FbxVector4 * sourceNormals)
{
	targetNormal[0] = sourceNormals->mData[0];
	targetNormal[1] = sourceNormals->mData[1];
	targetNormal[2] = sourceNormals->mData[2];
}

void MorphHandler::GetVertBiNormals(fbxsdk::FbxGeometryElementBinormal * pBNElement, int index, double * targetBiNormal)
{
	FbxVector4 biNormal = pBNElement->GetDirectArray().GetAt(index);
	targetBiNormal[0] = biNormal[0];
	targetBiNormal[1] = biNormal[1];
}

void MorphHandler::GetVertTangents(fbxsdk::FbxGeometryElementTangent * pTElement, int index, double * targetTangent)
{
	FbxVector4 tangent = pTElement->GetDirectArray().GetAt(index);
	targetTangent[0] = tangent[0];
	targetTangent[1] = tangent[1];
}