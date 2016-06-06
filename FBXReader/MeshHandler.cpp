#include "MeshHandler.h"
#include <stdio.h>
#include <string.h>
#include <math.h>



MeshHandler::MeshHandler()
{
	objectID = 0;
}


MeshHandler::~MeshHandler()
{
	//free(tempVertex);
	//delete vertex;
}

void MeshHandler::GetMeshData(FbxNode * pNode, std::vector<MeshExport*>* outputMeshes, SceneMap* sceneMap)
{
	//Recursively extract the children
	for (int j = 0; j < pNode->GetChildCount(); j++)
		GetMeshData(pNode->GetChild(j),outputMeshes, sceneMap);

	

	if (pNode->GetMesh())
	{
		if (!isATargetMesh(pNode->GetName())) //dont export a blendShape as a standard mesh
		{
			if (!HasMorphAnim(pNode)) //If it has morph animation, it will be exported in the animation handler, not here
			{
				if (!IsBoundingBox(pNode)) // Don't export a mesh that is a boundingBox
				{
					if (!IsGroup(pNode))
					{
						weightIndex = 0;
						bool hasSkeleton = HasSkeleton(pNode);

						MeshExport* tempMesh = new MeshExport(hasSkeleton); // Create a temporary object to fill the information

						tempMesh->meshInfo.hasSkeleton = hasSkeleton;
						tempMesh->meshInfo.objectID = objectID;
						objectID++;
						std::cout << pNode->GetName() << std::endl;
						/*
						First we need to get some specific information that  is relative to the object node
						this includes, name, translation,rotation and scale.

						After we have extracted that data we call "ProcessData" that processes the "mesh part" that is, vertices and such
						*/
						memcpy(tempMesh->meshInfo.meshName, pNode->GetName(), sizeof(char) * 256); //Get the name of the mesh and put it into the header. Memcpy is needed because the function wont return to a static array. So we cap it to 256 chars

						FbxDouble3 translation = pNode->LclTranslation.Get(); //Get the translation
						tempMesh->meshInfo.translation[0] = translation[0];
						tempMesh->meshInfo.translation[1] = translation[1];
						tempMesh->meshInfo.translation[2] = translation[2];


						FbxDouble3 rotation = pNode->LclRotation.Get();
						tempMesh->meshInfo.rotation[0] = rotation[0];
						tempMesh->meshInfo.rotation[1] = rotation[1];
						tempMesh->meshInfo.rotation[2] = rotation[2];


						FbxDouble3 scale = pNode->LclScaling.Get();
						tempMesh->meshInfo.scale[0] = scale[0];
						tempMesh->meshInfo.scale[1] = scale[1];
						tempMesh->meshInfo.scale[2] = scale[2];

						//getting the material id
						std::cout << pNode->GetMaterial(0)->GetName() << "\n";
						tempMesh->meshInfo.materialID = sceneMap->materialHash[pNode->GetMaterial(0)->GetName()];

						ProcessData(pNode->GetMesh(), tempMesh, hasSkeleton); //fill the information needed


						// Check if it has a boundingBox, If it has. then calculate it and store the information with the mesh
						bool hasBoundingBox = false;

						hasBoundingBox = GetBoundingBox(pNode, &tempMesh->boundingBox);
						if (hasBoundingBox)
						{
							tempMesh->meshInfo.boundingBox = hasBoundingBox;


							tempMesh->boundingBox.orientation[0] = rotation[0];
							tempMesh->boundingBox.orientation[1] = rotation[1];
							tempMesh->boundingBox.orientation[2] = rotation[2];

						}

						outputMeshes->push_back(tempMesh); //push back the temp mesh to the output class
					}
				}
			}
		}
	}
}

bool MeshHandler::isATargetMesh(const char * name)
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

bool MeshHandler::HasMorphAnim(FbxNode * pNode)
{
	if (pNode->GetGeometry())			 //if we find source mesh
	{
		FbxGeometry* pGeo = pNode->GetGeometry();
		if (pGeo->GetDeformerCount(FbxDeformer::eBlendShape) > 0)	 //if there is any blendshapes
		{
			return true;
		}
	}
	return false;
}

void MeshHandler::ProcessData(FbxMesh * pMesh, MeshExport* outPutMesh, bool hasSkeleton)
{
	/* Here we process all the data for the mesh,

	position
	normals
	UV
	tangent
	bitangent
	*/

	//Get vertices amount
	unsigned int vertCount = pMesh->GetControlPointsCount();




	
	unsigned int polyCount = pMesh->GetPolygonCount();


	std::vector<int> polyVertices;
	std::vector<FbxVector4> polyNormals;
	for (unsigned int i = 0; i < polyCount; i++)
	{
		for (int j = 0; j < pMesh->GetPolygonSize(i); j++)
		{
			FbxVector4 tempNormal;
			polyVertices.push_back(pMesh->GetPolygonVertex(i, j));
			pMesh->GetPolygonVertexNormal(i, j, tempNormal);
			polyNormals.push_back(tempNormal); 
		}
	}

	//Get the vertex indices

	std::vector<int> uvIndex;
	for (unsigned int i = 0; i < polyCount; ++i)
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
	
	//LÄGG TILL SKELETON SKTI
	if (!hasSkeleton)
	{
	
		for (int i = 0; i < polyVertices.size(); ++i)
		{
		
			VertexHeaderNoSkeleton tempVertex;

			FbxLayerElementArrayTemplate<FbxVector2>* uvVertices = 0;
			pMesh->GetTextureUV(&uvVertices, FbxLayerElement::eTextureDiffuse);

			GetVertPositions(pMesh, polyVertices.at(i), tempVertex.pos);
			GetPolygonNormals(tempVertex.normal, &polyNormals.at(i));
			GetVertBiNormals(pMesh->GetElementBinormal(), polyVertices.at(i), tempVertex.biTangent);
			GetVertTangents(pMesh->GetElementTangent(), polyVertices.at(i), tempVertex.tangent);
			GetVertTextureUV(pMesh->GetElementUV(), uvIndex.at(i), tempVertex.uv);

			if (outPutMesh->verticesNoSkeleton->size() != 0)
			{
				bool existWithinVerts = false;
				for (unsigned int j = 0; j < outPutMesh->verticesNoSkeleton->size(); j++)						 //Loop through the vertices we already have
				{
					if (outPutMesh->verticesNoSkeleton->at(j).pos[0] == tempVertex.pos[0] &&					   
						outPutMesh->verticesNoSkeleton->at(j).pos[1] == tempVertex.pos[1] &&
						outPutMesh->verticesNoSkeleton->at(j).pos[2] == tempVertex.pos[2] &&					  ////////////////////////////////////////////////////////////////////////////////////////
						outPutMesh->verticesNoSkeleton->at(j).normal[0] == tempVertex.normal[0] &&				  ////////////////////////////////////////////////////////////////////////////////////////
						outPutMesh->verticesNoSkeleton->at(j).normal[1] == tempVertex.normal[1] &&				  ////////////////////////////////////////////////////////////////////////////////////////
						outPutMesh->verticesNoSkeleton->at(j).normal[2] == tempVertex.normal[2] &&				  ////////////////////////////////////////////////////////////////////////////////////////
						outPutMesh->verticesNoSkeleton->at(j).biTangent[0] == tempVertex.biTangent[0] &&		  //    Test if a vert exactly like this has been found before. Then reuse it's index. 
						outPutMesh->verticesNoSkeleton->at(j).biTangent[1] == tempVertex.biTangent[1] &&		  //    This is done as a means of optimizing the mesh.
						outPutMesh->verticesNoSkeleton->at(j).tangent[0] == tempVertex.tangent[0] &&			  ////////////////////////////////////////////////////////////////////////////////////////
						outPutMesh->verticesNoSkeleton->at(j).tangent[1] == tempVertex.tangent[1] &&			  ////////////////////////////////////////////////////////////////////////////////////////
						outPutMesh->verticesNoSkeleton->at(j).uv[0] == tempVertex.uv[0] &&						  ////////////////////////////////////////////////////////////////////////////////////////
						outPutMesh->verticesNoSkeleton->at(j).uv[1] == tempVertex.uv[1])						  ////////////////////////////////////////////////////////////////////////////////////////
					{
						existWithinVerts = true;
						IndexHeader tempInd;
						tempInd.vertIndex = j;
						outPutMesh->indices->push_back(tempInd);
						break;
					}
				}
				if (!existWithinVerts)
				{
					IndexHeader tempInd;
					tempInd.vertIndex = (unsigned int) outPutMesh->verticesNoSkeleton->size();
					outPutMesh->indices->push_back(tempInd);
					outPutMesh->verticesNoSkeleton->push_back(tempVertex);
				}
			}
			else
			{
				IndexHeader tempInd;
				tempInd.vertIndex = i;
				outPutMesh->indices->push_back(tempInd);
				outPutMesh->verticesNoSkeleton->push_back(tempVertex);
			}
		}
	}
	else if (hasSkeleton)
	{

		for (int i = 0; i < (int)polyVertices.size(); ++i)
		{
			VertexHeader tempVertex;

			FbxLayerElementArrayTemplate<FbxVector2>* uvVertices = 0;
			pMesh->GetTextureUV(&uvVertices, FbxLayerElement::eTextureDiffuse);

			GetVertPositions(	pMesh, polyVertices.at(i),	    tempVertex.pos);										 // Get postiions
			GetVertNormals(		pMesh->GetElementNormal(),		polyVertices.at(i), tempVertex.normal);					 // Get Normals
			GetVertBiNormals(	pMesh->GetElementBinormal(),    polyVertices.at(i), tempVertex.biTangent);			     // Get BiTangents
			GetVertTangents(	pMesh->GetElementTangent(),     polyVertices.at(i), tempVertex.tangent);				 // Get Tangents
			GetVertTextureUV(	pMesh->GetElementUV(),	        uvIndex.at(i),	    tempVertex.uv);					     // Get UVs
			

			if (outPutMesh->vertices->size() != 0)
			{
				bool existWithinVerts = false;
				for (unsigned int j = 0; j < outPutMesh->vertices->size(); j++)							 //Loop through the vertices we already have
				{
					if (outPutMesh->vertices->at(j).pos[0]		 == tempVertex.pos[0]		&&			////////////////////////////////////////////////////////////////////////////////////////
						outPutMesh->vertices->at(j).pos[1]		 == tempVertex.pos[1]		&&			////////////////////////////////////////////////////////////////////////////////////////
						outPutMesh->vertices->at(j).pos[2]		 == tempVertex.pos[2]		&&			////////////////////////////////////////////////////////////////////////////////////////
						outPutMesh->vertices->at(j).normal[0]	 == tempVertex.normal[0]	&&			////////////////////////////////////////////////////////////////////////////////////////
						outPutMesh->vertices->at(j).normal[1]	 == tempVertex.normal[1]	&&		    //    Test if a vert exactly like this has been found before. Then reuse it's index. 
						outPutMesh->vertices->at(j).normal[2]	 == tempVertex.normal[2]	&&		    //    This is done as a means of optimizing the mesh.
						outPutMesh->vertices->at(j).biTangent[0] == tempVertex.biTangent[0] &&		    ////////////////////////////////////////////////////////////////////////////////////////
						outPutMesh->vertices->at(j).biTangent[1] == tempVertex.biTangent[1] &&		    ////////////////////////////////////////////////////////////////////////////////////////
						outPutMesh->vertices->at(j).tangent[0]   == tempVertex.tangent[0]   &&		    ////////////////////////////////////////////////////////////////////////////////////////
						outPutMesh->vertices->at(j).tangent[1]   == tempVertex.tangent[1]   &&		    ////////////////////////////////////////////////////////////////////////////////////////
						outPutMesh->vertices->at(j).uv[0]		 == tempVertex.uv[0]		&&
						outPutMesh->vertices->at(j).uv[1]		 == tempVertex.uv[1])
					{
						existWithinVerts = true;
						IndexHeader tempInd;
						tempInd.vertIndex = j;						 //If it exists. just store the index
						outPutMesh->indices->push_back(tempInd);
						break;
					}
				}
				if (!existWithinVerts) // If its a brand new vertex. Store it. Else go on. (the index has been stored above)
				{
					if (outPutMesh->vertices->size() >= 4)
					{
						std::vector<WeigthsHeader> emptyWeight;
						outPutMesh->weights.push_back(emptyWeight);
					}
					IndexHeader tempInd;
				
					tempInd.vertIndex = (unsigned int)outPutMesh->vertices->size();

					outPutMesh->indices ->push_back(tempInd);		//Store index
					outPutMesh->vertices->push_back(tempVertex);    //Store vertex
					
					GetSkeletonWeights(pMesh, polyVertices.at(i), outPutMesh);
					
				}
			}
			else
			{
				if (outPutMesh->weights.size() < 4)
				{
					std::vector<WeigthsHeader> emptyWeight;
					outPutMesh->weights.push_back(emptyWeight);
				}
				if (outPutMesh->weights.size() > 4)
				{
					std::vector<WeigthsHeader> emptyWeight;
					outPutMesh->weights.push_back(emptyWeight);
				}
				IndexHeader tempInd;
				std::vector<WeigthsHeader> emptyWeight;
				tempInd.vertIndex = i;
				outPutMesh->indices ->push_back(tempInd);
				outPutMesh->vertices->push_back(tempVertex);

				GetSkeletonWeights(pMesh, i, outPutMesh);		
			}
		}
	
	}



	std::cout << "\n";
}

void MeshHandler::GetVertPositions(FbxMesh * pMesh, int index, double * targetPos)
{
	FbxVector4 position = pMesh->GetControlPointAt(index);

	targetPos[0] = (double)position[0];
	targetPos[1] = (double)position[1];
	targetPos[2] = (double)position[2];
}

void MeshHandler::GetVertNormals(fbxsdk::FbxGeometryElementNormal * pNElement, int index, double * targetNormal)
{
	FbxVector4 normal = pNElement->GetDirectArray().GetAt(index);

	targetNormal[0] = normal[0];
	targetNormal[1] = normal[1];
	targetNormal[2] = normal[2];
}

void MeshHandler::GetVertBiNormals(fbxsdk::FbxGeometryElementBinormal * pBNElement, int index, double * targetBiNormal)
{
	FbxVector4 biNormal = pBNElement->GetDirectArray().GetAt(index);
	targetBiNormal[0] = biNormal[0];
	targetBiNormal[1] = biNormal[1];
}

void MeshHandler::GetVertTangents(fbxsdk::FbxGeometryElementTangent * pTElement, int index, double * targetTangent)
{
	FbxVector4 tangent = pTElement->GetDirectArray().GetAt(index);
	targetTangent[0] = tangent[0];
	targetTangent[1] = tangent[1];
}

void MeshHandler::GetVertTextureUV(fbxsdk::FbxGeometryElementUV* uvElement, int index, double * targetUV)
{
	FbxVector2 uvs = uvElement->GetDirectArray().GetAt(index);
	targetUV[0] = uvs[0];
	targetUV[1] = 1 - uvs[1];
}

void MeshHandler::GetSkeletonWeights(fbxsdk::FbxMesh * pMesh, int index, MeshExport* outputMesh)
{
	FbxSkin * pSkin = (FbxSkin*)pMesh->GetDeformer(0, FbxDeformer::eSkin);
	if (pSkin != NULL)
	{
		int boneCount = pSkin->GetClusterCount();
		for (int boneIndex = 0; boneIndex < boneCount; boneIndex++)
		{
			WeigthsHeader tempWeight;
			FbxCluster * pCluster = pSkin->GetCluster(boneIndex);
			FbxNode* pBone = pCluster->GetLink();
			double * pBoneVertWeights = pCluster->GetControlPointWeights();
			for (int i = 0; i < pCluster->GetControlPointIndicesCount(); i++)
			{
				if (index == pCluster->GetControlPointIndices()[i])
				{
					tempWeight.influence = pBoneVertWeights[index];
					tempWeight.jointID = boneIndex;
					outputMesh->weights.at(weightIndex).push_back(tempWeight);
					break;
				}
			}
		}
		weightIndex++;
		
	}
	else
	{
		return;
	}
}

bool MeshHandler::GetBoundingBox(FbxNode * pNode,OOBBHeader* boundingBox)
{
	for (int j = 0; j < pNode->GetChildCount(); j++)
	{
		
		if (IsBoundingBox(pNode->GetChild(j)))
		{

			std::cout << "\t Bounding box name : ";
			std::cout << pNode->GetChild(j)->GetName() << std::endl;


			FbxMesh* pMesh = pNode->GetChild(j)->GetMesh();
			//Get vertices amount
			unsigned int vertCount = pMesh->GetControlPointsCount();

			//find length, of x,y,z here

			double maxX = -INFINITY;
			

			double maxY = -INFINITY;
			

			double maxZ = -INFINITY;
			

			//Find the extensions of the axises
			
			for (unsigned int i = 0; i < vertCount; i++)
			{
				double vert[3];

				GetVertPositions(pMesh, i, vert);
			
				if (fabs(vert[0]) > maxX)
					maxX = fabs(vert[0]);

				if (fabs(vert[1]) > maxY)
					maxY = fabs(vert[1]);

				if (fabs(vert[2]) > maxZ)
					maxZ = fabs(vert[2]);


			}

			boundingBox->extents[0] = maxX;
			boundingBox->extents[1] = maxY;
			boundingBox->extents[2] = maxZ;







			return true;
		}

	}
	return false;
}

bool MeshHandler::IsBoundingBox(FbxNode * pNode)
{

	//We had a namecode for our boundingBoxes in maya. the name was to Start with OOBB
	//If it was a boundingbox. then the mesh would not be exported, only the bounding information was needed

	char compare[5];
	char target[5];
	target[0] = 'O';
	target[1] = 'O';
	target[2] = 'B';
	target[3] = 'B';
	target[4] = '\0';
	const char* name = pNode->GetName();

	for (int i = 0; i < 4; i++)
	{
		compare[i] = name[i];
	}
	compare[4] = '\0';
	if (strcmp(compare, target) == 0)
		return true;	
	
	return false;
}

bool MeshHandler::HasSkeleton(FbxNode * pNode)
{
	FbxMesh * pMesh = pNode->GetMesh();
	FbxSkin * pSkin = (FbxSkin*)pMesh->GetDeformer(0, FbxDeformer::eSkin);
	if (pSkin != NULL)
		return true;
	else
		return false;
}

bool MeshHandler::IsGroup(FbxNode * pNode)
{
	FbxNodeAttribute::EType lAttributeType = pNode->GetNodeAttribute()->GetAttributeType();

	if (lAttributeType == FbxNodeAttribute::EType::eNull)
		return true;
	else
		return false;
}

void MeshHandler::GetPolygonNormals(double * targetNormal, FbxVector4 * sourceNormals)
{
	targetNormal[0] = sourceNormals->mData[0];
	targetNormal[1] = sourceNormals->mData[1];
	targetNormal[2] = sourceNormals->mData[2];
}
