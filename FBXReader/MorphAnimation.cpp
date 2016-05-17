#include "MorphAnimation.h"





bool MorphAnimation::isATargetMesh(const char * name)
{


	char compare[12];
	char target[12];
	target[0] = 'A';
	target[1] = 'N';
	target[2] = 'I';
	target[3] = 'M';
	target[4] = '_';
	target[5] = 'T';
	target[6] = 'A';
	target[7] = 'R';
	target[8] = 'G';
	target[9] = 'E';
	target[10] = 'T';
	target[11] = '\0';

	for (int i = 0; i < 11; i++)
	{
		compare[i] = name[i];
	}
	compare[11] = '\0';
	if (strcmp(compare, target) == 0)
	{
		std::cout << "TARGET MESH FOUND" << std::endl;
		return true;
	}
	else
		return false;


	return true;
}

void MorphAnimation::ExtractSourceMesh(FbxNode * pNode)
{
	/* Here we process all the data for the mesh,

	position
	normals
	UV
	tangent
	bitangent
	*/


	MeshExport* targetMesh =  new MeshExport(false);





	FbxMesh* pMesh = pNode->GetMesh();
	unsigned int vertCount = pMesh->GetControlPointsCount();
	

	//trying to find the material
	//FbxNode * pNode = (FbxNode*)pMesh->GetDstObject();


	unsigned int polyCount = pMesh->GetPolygonCount();


	std::vector<int> polyVertices;
	std::vector<FbxVector4> polyNormals;
	for (int i = 0; i < polyCount; i++)
	{
		for (int j = 0; j < pMesh->GetPolygonSize(i); j++)
		{
			FbxVector4 tempNormal;
			polyVertices.push_back(pMesh->GetPolygonVertex(i, j));
			pMesh->GetPolygonVertexNormal(i, j, tempNormal);
			polyNormals.push_back(tempNormal);
		}
	}
	
	

	std::vector<int> uvIndex;
	for (int i = 0; i < polyCount; ++i)
	{
		std::vector<FbxVector2> tempValues;
		FbxLayerElementArrayTemplate<FbxVector2>* uvVertices = 0;
		pMesh->GetTextureUV(&uvVertices, FbxLayerElement::eTextureDiffuse);

		for (int j = 0; j < pMesh->GetPolygonSize(i); ++j)
		{
			int UVIndex = pMesh->GetTextureUVIndex(i, j);
			uvIndex.push_back(UVIndex);
	
		}
	
	}
	


	
		//outPutMesh->verticesNoSkeleton->resize(34);
		//unsigned int index = 0;
		for (int i = 0; i < polyVertices.size(); ++i)
		{
			
			//VertexHeaderNoSkeleton tempVertex;
			VertexHeaderNoSkeleton tempVertex;

			FbxLayerElementArrayTemplate<FbxVector2>* uvVertices = 0;
			pMesh->GetTextureUV(&uvVertices, FbxLayerElement::eTextureDiffuse);

			GetVertPositions(pMesh, polyVertices.at(i), tempVertex.pos);
			//GetVertNormals(pMesh->GetElementNormal(), polyVertices.at(i), tempVertex.normal);
			GetPolygonNormals(tempVertex.normal, &polyNormals.at(i));
			GetVertBiNormals(pMesh->GetElementBinormal(), polyVertices.at(i), tempVertex.biTangent);
			GetVertTangents(pMesh->GetElementTangent(), polyVertices.at(i), tempVertex.tangent);
			GetVertTextureUV(pMesh->GetElementUV(), uvIndex.at(i), tempVertex.uv);
			
			targetMesh->verticesNoSkeleton->push_back(tempVertex);
		}
	
	

	std::cout << "Source mesh :" << pMesh->GetName() << std::endl;
	std::cout << "Total amount of vertices on mesh : " << targetMesh->verticesNoSkeleton->size() << std::endl;
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t t = 0; t < 3; t++)
		{
			std::cout << targetMesh->verticesNoSkeleton->at(i).pos[t] << " , ";

		}
		std::cout << "\n";
	}
	std::cout << "\n";


	sourceMesh = targetMesh;


}

BlendMesh* MorphAnimation::ExtractTargetMesh(FbxNode * pNode)
{

	/* Here we process all the data for the mesh,

	position
	normals
	UV
	tangent
	bitangent
	*/


	BlendMesh* targetMesh = new BlendMesh();





	FbxMesh* pMesh = pNode->GetMesh();
	unsigned int vertCount = pMesh->GetControlPointsCount();


	//trying to find the material
	//FbxNode * pNode = (FbxNode*)pMesh->GetDstObject();


	unsigned int polyCount = pMesh->GetPolygonCount();


	std::vector<int> polyVertices;
	std::vector<FbxVector4> polyNormals;
	for (int i = 0; i < polyCount; i++)
	{
		for (int j = 0; j < pMesh->GetPolygonSize(i); j++)
		{
			FbxVector4 tempNormal;
			polyVertices.push_back(pMesh->GetPolygonVertex(i, j));
			pMesh->GetPolygonVertexNormal(i, j, tempNormal);
			polyNormals.push_back(tempNormal);
		}
	}



	std::vector<int> uvIndex;
	for (int i = 0; i < polyCount; ++i)
	{
		std::vector<FbxVector2> tempValues;
		FbxLayerElementArrayTemplate<FbxVector2>* uvVertices = 0;
		pMesh->GetTextureUV(&uvVertices, FbxLayerElement::eTextureDiffuse);

		for (int j = 0; j < pMesh->GetPolygonSize(i); ++j)
		{
			int UVIndex = pMesh->GetTextureUVIndex(i, j);
			uvIndex.push_back(UVIndex);

		}

	}




	//outPutMesh->verticesNoSkeleton->resize(34);
	//unsigned int index = 0;
	for (int i = 0; i < polyVertices.size(); ++i)
	{

		//VertexHeaderNoSkeleton tempVertex;
		BlendVertexHeader tempVertex;

		FbxLayerElementArrayTemplate<FbxVector2>* uvVertices = 0;
		pMesh->GetTextureUV(&uvVertices, FbxLayerElement::eTextureDiffuse);

		GetVertPositions(pMesh, polyVertices.at(i), tempVertex.pos);
		//GetVertNormals(pMesh->GetElementNormal(), polyVertices.at(i), tempVertex.normal);
		GetPolygonNormals(tempVertex.normal, &polyNormals.at(i));
		GetVertBiNormals(pMesh->GetElementBinormal(), polyVertices.at(i), tempVertex.biTangent);
		GetVertTangents(pMesh->GetElementTangent(), polyVertices.at(i), tempVertex.tangent);
	

		targetMesh->vertices.push_back(tempVertex);
	}



	std::cout << "Source mesh :" << pMesh->GetName() << std::endl;
	std::cout << "Total amount of vertices on mesh : " << targetMesh->vertices.size() << std::endl;
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t t = 0; t < 3; t++)
		{
			std::cout << targetMesh->vertices.at(i).pos[t] << " , ";

		}
		std::cout << "\n";
	}
	std::cout << "\n";

	std::cout << "Total amount of vertices on mesh : " << targetMesh->vertices.size() << std::endl;
	blendMeshes.push_back(targetMesh);
	return targetMesh;
}

void MorphAnimation::ExtractAllMeshesInAnimation(FbxNode * pNode)
{
	for (int i = 0; i < pNode->GetChildCount(); i++)
	{
			ExtractAllMeshesInAnimation(pNode->GetChild(i)); //recursively go down the hierarchy and search for blendshape animations
	}
	if (isATargetMesh(pNode->GetName()))
	{
		std::cout << pNode->GetName() << std::endl;
		
		const char* name = pNode->GetName();
		int i = name[12] - '0';
		blendShapeMap[i] = ExtractTargetMesh(pNode); //get the number in the name and map it.
	}




#pragma region
		
		if (pNode->GetGeometry())			 //if we find source mesh
		{
			FbxGeometry* pGeo = pNode->GetGeometry();
			if (pGeo->GetDeformerCount(FbxDeformer::eBlendShape) > 0)	 //if there is any blendshapes
			{
				ExtractSourceMesh(pNode);
				int morphAnimCount = pGeo->GetDeformerCount(FbxDeformer::eBlendShape);	 //get amount of targets
				int morphChannelCount;
				int targetShapeCount;
				for (unsigned int i = 0; i < morphAnimCount; i++) //for each blendshape
				{

					FbxBlendShape* morphAnim;
					morphAnim = (FbxBlendShape*)pGeo->GetDeformer(i, FbxDeformer::eBlendShape); //Get the blend shape #i

					morphChannelCount = morphAnim->GetBlendShapeChannelCount(); //Get how many channels the blend shape #i has
					std::cout << "ChannelCount: " << morphChannelCount << "\n\n";

						BlendAnimation* tempAnimation = new BlendAnimation();
					for (unsigned int j = 0; j < morphChannelCount; j++) //for every channel
					{
						std::cout << "channel nr: " << j << "\n";

						FbxBlendShapeChannel* morphChannel;
						morphChannel = morphAnim->GetBlendShapeChannel(j);
						//morphChannel->GetBlendShapeDeformer();

						std::cout << "ChannelName: " << morphChannel->GetNameWithoutNameSpacePrefix() << "\n\n";   //usually blendshapeName.meshName

						targetShapeCount = morphChannel->GetTargetShapeCount();
						std::cout << "Target Shape Count: " << targetShapeCount << "\n\n";
						for (unsigned int k = 0; k < targetShapeCount; k++) //for every shape in this channel
						{
							FbxShape* shape;
							shape = morphChannel->GetTargetShape(k);
							std::cout << shape->GetName() << std::endl;

							
							
							//processKeyFrames(pNode, output, morphChannel);
							//shape->GetElementPolygonGroupCount()

							FbxScene * scene = pNode->GetScene();

							//Getting the number of animation stacks for this mesh
							//seeing as you can have different ones such as (running, walking...)
							int numAnimations = scene->GetSrcObjectCount<FbxAnimStack>();

							for (int animIndex = 0; animIndex < numAnimations; animIndex++)
							{

								//getting the current stack and evaluator
								FbxAnimStack *animStack = (FbxAnimStack*)scene->GetSrcObject<FbxAnimStack>(animIndex);
								FbxAnimEvaluator *animEval = scene->GetAnimationEvaluator();
								std::cout << animStack->GetName() << "\n";
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
										int numKeys = deformCurve->KeyGetCount();
										for (int keyIndex = 0; keyIndex < numKeys; keyIndex++)
										{
											fbxsdk::FbxAnimCurveKey key = deformCurve->KeyGet(keyIndex);
											const char* name = shape->GetName();											 //Mapping the number in the name to the frame. this is to keep track of what mesh is used in this frame
											int in = name[12] - '0';														 //Mapping the number in the name to the frame. this is to keep track of what mesh is used in this frame

											if (std::find(tempAnimation->meshIDs.begin(), tempAnimation->meshIDs.end(), in) == tempAnimation->meshIDs.end()) //we need to keep track of the meshes used in the animation, Here we check if the id exists already. otherwise add it to the list of meshes used
												tempAnimation->meshIDs.push_back((unsigned int)in);

											FbxTime frameTime = deformCurve->KeyGetTime(keyIndex);

											//framerate är 41 med mode eFrames1000 :S:S:S:S:S
											unsigned int frame = frameTime.GetFieldCount(FbxTime::EMode::eFrames1000) / 41 / 2;
											std::cout <<"frame :" << frame << "\n"; //ful lösning, för att hitta rätt keyframe. inte helt exakt. men nära!
		
											double deform	   = morphChannel->DeformPercent.EvaluateValue(frameTime);
											std::cout << "\n influece: " << deform << "\n";
											if (frame > tempAnimation->animationTime)
												tempAnimation->animationTime = frame;
											
											bool	frameExists = false;
											int		frameIndex = 0;
											for (size_t i = 0; i < tempAnimation->frames.size(); i++)
											{
												if (tempAnimation->frames.at(i).frameTime == frame)
												{
													frameExists = true;
													frameIndex  = (int)i;
													break;
												}
											}
											if (frameExists)
											{
												tempAnimation->frames.at(frameIndex).meshIDs.push_back(in);
												tempAnimation->frames.at(frameIndex).influence.push_back(float(deform));
											}
											else
											{
										    tempAnimation->frames.push_back(BlendFrame());										 //Mapping the number in the name to the frame. this is to keep track of what mesh is used in this frame
											tempAnimation->frames.at(tempAnimation->frames.size() - 1).frameTime = frame;		 //STORING THE FRAME NUMBER
											tempAnimation->frames.at(tempAnimation->frames.size() - 1).meshIDs.push_back(in);	 //Mapping the number in the name to the frame. this is to keep track of what mesh is used in this frame
											tempAnimation->frames.at(tempAnimation->frames.size() - 1).influence.push_back(float(deform));																   // STORING THE INFLUENCE AT THIS FRAME
											}
										}
									}
								}
							}
						}
					}
								animations.push_back(tempAnimation);

				this->GetMissingKeyFrame(morphAnim,pNode,animations.size() - 1);
				}
				

			}
		}
#pragma endregion

}

void MorphAnimation::GetMorphAnimation(FbxNode * pNode)
{
	
		ExtractAllMeshesInAnimation(pNode);

	


	//FbxGeometry* pGeo = pNode->GetGeometry();								 // get Source
	//int morphAnimCount = pGeo->GetDeformerCount(FbxDeformer::eBlendShape);	 //get amount of targets
	//int morphChannelCount;
	//int targetShapeCount;
	//for (unsigned int i = 0; i < morphAnimCount; i++) //for each target
	//{
	//	FbxBlendShape* morphAnim;
	//	morphAnim = (FbxBlendShape*)pGeo->GetDeformer(i, FbxDeformer::eBlendShape); //Get the blend shape #i

	//	morphChannelCount = morphAnim->GetBlendShapeChannelCount(); //Get how many channels the blend shape #i has
	//	std::cout << "ChannelCount: " << morphChannelCount << "\n\n";
	//
	//	for (unsigned int j = 0; j < morphChannelCount; j++) //for every channel
	//	{
	//		std::cout << "channel nr: " << j << "\n";

	//		FbxBlendShapeChannel* morphChannel;
	//		morphChannel = morphAnim->GetBlendShapeChannel(j);
	//		morphChannel->GetBlendShapeDeformer();
	//		std::cout << "ChannelName: " << morphChannel->GetName() << "\n\n";   //usually blendshapeName.meshName

	//		targetShapeCount = morphChannel->GetTargetShapeCount();
	//		std::cout << "Target Shape Count: " << targetShapeCount << "\n\n";
	//		for (unsigned int k = 0; k < targetShapeCount; k++) //for every shape in this channel
	//		{
	//			FbxShape* shape;svb
	//		
	//			shape = morphChannel->GetTargetShape(k);
	//		}
	//	
	//	}



	//}

}


MorphAnimation::MorphAnimation()
{
}


MorphAnimation::~MorphAnimation()
{
	if (sourceMesh)
		delete sourceMesh;

	for (size_t i = 0; i < animations.size(); i++)
	{
		delete animations.at(i);
	}
	for (size_t i = 0; i < blendMeshes.size(); i++)
	{
		delete blendMeshes.at(i);

	}
}



void MorphAnimation::GetVertPositions(FbxMesh * pMesh, int index, double * targetPos)
{
	FbxVector4 position = pMesh->GetControlPointAt(index);

	targetPos[0] = (double)position[0];
	targetPos[1] = (double)position[1];
	targetPos[2] = (double)position[2];
}

void MorphAnimation::GetVertNormals(fbxsdk::FbxGeometryElementNormal * pNElement, int index, double * targetNormal)
{
	FbxVector4 normal = pNElement->GetDirectArray().GetAt(index);

	targetNormal[0] = normal[0];
	targetNormal[1] = normal[1];
	targetNormal[2] = normal[2];
}

void MorphAnimation::GetVertBiNormals(fbxsdk::FbxGeometryElementBinormal * pBNElement, int index, double * targetBiNormal)
{
	FbxVector4 biNormal = pBNElement->GetDirectArray().GetAt(index);
	targetBiNormal[0] = biNormal[0];
	targetBiNormal[1] = biNormal[1];
}

void MorphAnimation::GetVertTangents(fbxsdk::FbxGeometryElementTangent * pTElement, int index, double * targetTangent)
{
	FbxVector4 tangent = pTElement->GetDirectArray().GetAt(index);
	targetTangent[0] = tangent[0];
	targetTangent[1] = tangent[1];
}

void MorphAnimation::GetVertTextureUV(fbxsdk::FbxGeometryElementUV* uvElement, int index, double * targetUV)
{
	FbxVector2 uvs = uvElement->GetDirectArray().GetAt(index);
	targetUV[0] = uvs[0];
	targetUV[1] = 1 - uvs[1];
}

void MorphAnimation::GetPolygonNormals(double * targetNormal, FbxVector4 * sourceNormals)
{
	targetNormal[0] = sourceNormals->mData[0];
	targetNormal[1] = sourceNormals->mData[1];
	targetNormal[2] = sourceNormals->mData[2];
}

void MorphAnimation::GetMissingKeyFrame(FbxBlendShape* morphAnim, FbxNode * pNode, int animationIndex)
{
	/*
			We have extracted the frames of the animation now.
			But if we extract a keyframe that has influence of only one mesh (for example). another mesh might still have influence
			but not a specific keyframe set at that time. This is because the keyframe we extracted might be between two keyframes of the other mesh.
			we still need to extract that mesh to make sure we don't miss information on that frame
	*/

	
		for (size_t i = 0; i < animations.at(animationIndex)->frames.size(); i++) //get mesh amount of the animation
		{
			if (animations.at(animationIndex)->frames.at(i).meshIDs.size() > animations.at(animationIndex)->meshesUsed) //loop through the animation and get all the meshes used
				animations.at(animationIndex)->meshesUsed = animations.at(animationIndex)->frames.at(i).meshIDs.size();

		}



		for (size_t k = 0; k < animations.at(animationIndex)->frames.size(); k++)
		{
			if (animations.at(animationIndex)->frames.at(k).meshIDs.size() == animations.at(animationIndex)->meshesUsed) //If all the meshes are accounted for in this frame. Continue to the next frame
				continue;
			else
			{
				for (size_t i = 0; i < animations.at(animationIndex)->meshIDs.size(); i++) //Loop through the mesh ids and find what mesh is missing
				{
					if (
						std::find(												//find			    Search the frame mesh id's and compare it to the whole animations stored mesh ids
							animations.at(animationIndex)->frames.at(k).meshIDs.begin(),    //array begin			  
							animations.at(animationIndex)->frames.at(k).meshIDs.end(),	   //array end
							animations.at(animationIndex)->meshIDs.at(i))				   //value we are looking for
						== animations.at(animationIndex)->frames.at(k).meshIDs.end()   // if the value is not found
						)
					{ //Go through the animation extraction process and find the missing info 
						int morphChannelCount;
						morphChannelCount = morphAnim->GetBlendShapeChannelCount(); //Get how many channels the blend shape has

						for (unsigned int j = 0; j < morphChannelCount; j++) //for every channel
						{
							FbxBlendShapeChannel* morphChannel;
							morphChannel = morphAnim->GetBlendShapeChannel(j);
							unsigned int targetShapeCount = morphChannel->GetTargetShapeCount();
							for (unsigned int tarShape = 0; tarShape < targetShapeCount; tarShape++) //for every shape in this channel
							{
								FbxShape* shape;
								shape = morphChannel->GetTargetShape(tarShape);
								std::cout << shape->GetName() << std::endl;

								const char* name = shape->GetName();											 //Get the name of the shape to get the ID. we compare the id  to make sure we are processing the right mesh
								unsigned int in = name[12] - '0';
								
								if (in != animations.at(animationIndex)->meshIDs.at(i)) //Make sure we process the right mesh (the one that is missing the frame) else continue 
									continue;

								FbxScene * scene = pNode->GetScene();


								//Getting the number of animation stacks for this mesh
								//seeing as you can have different ones such as (running, walking...)
								int numAnimations = scene->GetSrcObjectCount<FbxAnimStack>();
								for (int animIndex = 0; animIndex < numAnimations; animIndex++) //for every animation
								{

									//getting the current stack and evaluator
									FbxAnimStack *animStack = (FbxAnimStack*)scene->GetSrcObject<FbxAnimStack>(animIndex);
									FbxAnimEvaluator *animEval = scene->GetAnimationEvaluator();
									std::cout << animStack->GetName() << "\n";
									//so far so good

									int numLayers = animStack->GetMemberCount();

									for (int layerIndex = 0; layerIndex < numLayers; layerIndex++)
									{
										FbxAnimLayer *animLayer = (FbxAnimLayer*)animStack->GetMember(layerIndex);

										FbxAnimCurve * deformCurve = morphChannel->DeformPercent.GetCurve(animLayer);
										if (deformCurve != nullptr)
										{
											int numKeys = deformCurve->KeyGetCount();
											if (numKeys < animations.at(animationIndex)->frames.size()) //if the amount of keys are less than what is in the animation, we have found the animation that has the missing keyframe
											{
												//since we know the time of the missing keyframe. We just extract it.
												FbxTime frameTime;
												frameTime.SetTime(0, 0, 0, animations.at(animationIndex)->frames.at(k).frameTime, 0, FbxTime::eFrames24);

												/*	unsigned int anim = animationIndex;
													unsigned int frame = k;
													unsigned int frameTimeA = animations.at(animationIndex)->frames.at(k).frameTime;
												/*/
												double deform = morphChannel->DeformPercent.EvaluateValue(frameTime, true);

												animations.at(animationIndex)->frames.at(k).meshIDs.push_back(in);	
												animations.at(animationIndex)->frames.at(k).influence.push_back(float(deform));
											
											}
											else
												continue; //if this animation has all the keyframes, continue
										}


									}	// end for(every layer)
								}		// end for(every animation)
							}			// end for (every shape)
						}				// end for(every Channel)

					}
					else
						std::cout << "No missing frame found on this mesh" << std::endl;
				}// end for(every mesh id)         (Loop through the mesh ids and find what mesh is missing)
			} // end else (if the animation is missing a frame)
		}
	
}

void MorphAnimation::CreateBRFAnimation()
{

	 /*
			Now we have
			- Mesh info of every mesh used in an animation
				- Mapped id to those meshes
			- Animations
				- Total frame time (the time of the last frame in the animation)
				- Mesh IDs
				- with frame information
					- Frames have:
						- mesh IDs of the meshes being used
						- influences of the meshes
						- a frame time

			The algorithm is as following

			For every animation
			{
				- loop through each frame
					- interpolate the vertices of the base mesh and the meshes being used that frame
					- Create a new mesh based on the new interpolated values. This mesh shall later be exported
					- This mesh is used as a "keyframe" in the engine. So in the game. we don't interpolate between many meshes. just one!
			}
	 */



}
