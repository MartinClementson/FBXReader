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
	free(tempVertex);
}

void MeshHandler::GetMeshData(FbxNode * pNode, std::vector<MeshExport*>* outputMeshes, SceneMap* sceneMap)
{
	//Recursively extract the children
	for (int j = 0; j < pNode->GetChildCount(); j++)
		GetMeshData(pNode->GetChild(j),outputMeshes, sceneMap);

	

	if (pNode->GetMesh())
	{
		if (!IsBoundingBox(pNode)) // Don't export a mesh that is a boundingBox
		{

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
			memcpy(tempMesh->meshInfo.meshName,pNode->GetName(),sizeof(char)* 256); //Get the name of the mesh and put it into the header. Memcpy is needed because the function wont return to a static array. So we cap it to 256 chars
		
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
			
			hasBoundingBox = GetBoundingBox(pNode,&tempMesh->boundingBox);
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

void MeshHandler::ProcessData(FbxMesh * pMesh, MeshExport* outPutMesh, bool hasSkeleton)
{
	/* Here we process all the data for the mesh,

	position
	normals
	UV
	tangent
	bitangent
	*/

	//FbxGeometryElementMaterial * matte = (FbxGeometryElementMaterial*)pMesh->GetAttributeType();
	//Get vertices amount
	unsigned int vertCount = pMesh->GetControlPointsCount();
	//outPutMesh->meshInfo.vertexCount = vertCount;


	//trying to find the material
	FbxNode * pNode = (FbxNode*)pMesh->GetDstObject();

	std::cout << pNode->GetMaterialCount();
	std::cout << (pNode->GetMaterial(0))->GetName();

	if (hasSkeleton)
	{
		outPutMesh->vertices->resize(vertCount);
		outPutMesh->weights.resize(vertCount);
	}
	else
		outPutMesh->verticesNoSkeleton->resize(vertCount);

	unsigned int polyCount = pMesh->GetPolygonCount();
	std::vector<int> polyVertices;
	for (int i = 0; i < polyCount; i++)
	{
		for (int j = 0; j < pMesh->GetPolygonSize(i); j++)
			polyVertices.push_back(pMesh->GetPolygonVertex(i, j));
	}

	//Get the vertex indices
	int startindex;
	int *vert;
	//for (unsigned int i = 0; i < polyCount; i++)
	//{
	//	startindex = pMesh->GetPolygonVertexIndex(i); 
	//	vert = &pMesh->GetPolygonVertices()[startindex];
	//	int count = pMesh->GetPolygonSize(i);
	//	for (int j = 0; j < count; j++)
	//	{

	//		//std::cout << i << ": " << vert[j] << "\n";
	//		IndexHeader temp;
	//		temp.vertIndex = vert[j];
	//		outPutMesh->Addindex(temp);
	//	}
	//}
	//outPutMesh->meshInfo.indexCount = outPutMesh->indices->size(); //store the amount of indices found

	//t5estingf uvs
	//int uvcount = pMesh->GetTextureUVIndex();

	//allt detta är en test på skit
	/*for (int i = 0; i < polyCount; ++i)
	{
		std::vector<FbxVector2> tempValues;
		FbxLayerElementArrayTemplate<FbxVector2>* uvVertices = 0;
		pMesh->GetTextureUV(&uvVertices, FbxLayerElement::eTextureDiffuse);

		for (int j = 0; j < pMesh->GetPolygonSize(i); ++j)
		{
			int UVIndex = pMesh->GetTextureUVIndex(i, j);
			uvIndex.push_back(UVIndex);
			FbxVector2 uv = uvVertices->GetAt(pMesh->GetTextureUVIndex(i, j));

			texturecoords[0] = uv[0];
			texturecoords[1] = uv[1];
			tempValues.push_back(texturecoords);
		}
		uvValues.push_back(tempValues);
	}*/
	std::vector<VertexHeader>* finalVertex;
	std::vector<int> uvIndex;
	//std::vector<std::vector<FbxVector2>> uvValues;
	FbxVector2 texturecoords;
	VertexHeader temp1Vertex;
	finalVertex = new std::vector<VertexHeader>;
	for (int i = 0; i < polyVertices.size(); ++i)
	{

		//std::vector<FbxVector2> tempValues;
		//FbxLayerElementArrayTemplate<FbxVector2>* uvVertices = 0;
		//pMesh->GetTextureUV(&uvVertices, FbxLayerElement::eTextureDiffuse);

		GetVertPositions(pMesh, polyVertices.at(i), temp1Vertex.pos);
		GetVertNormals(pMesh->GetElementNormal(), polyVertices.at(i), temp1Vertex.normal);
		GetVertBiNormals(pMesh->GetElementBinormal(), polyVertices.at(i), temp1Vertex.biTangent);
		GetVertTangents(pMesh->GetElementTangent(), polyVertices.at(i), temp1Vertex.tangent);
		//GetVertTextureUV(pMesh->GetElementUV(), i, tempVertex.uv);

		//for (int j = 0; j < pMesh->GetPolygonSize(i); ++j)
		//{
		//	//int UVIndex = pMesh->GetTextureUVIndex(i, j);
		//	//uvIndex.push_back(UVIndex);
		//	FbxVector2 uv = uvVertices->GetAt(pMesh->GetTextureUVIndex(i, j));

		//	temp1Vertex.uv[0] = uv[0];
		//	temp1Vertex.uv[1] = uv[1];
		//	//tempValues.push_back(texturecoords);
		//}
		finalVertex->push_back(temp1Vertex);
		//uvValues.push_back(tempValues);
	}

	std::vector<IndexHeader> indices;
	std::vector<VertexHeader>* vertex;
	unsigned int indexCounter = 0;
	bool existWithinVerts = false;
	unsigned int UVCounter = 0;
	vertex = new std::vector<VertexHeader>;
	tempVertex = new VertexHeader;


	FbxLayerElementArrayTemplate<FbxVector2>* uvVertices = 0;
	pMesh->GetTextureUV(&uvVertices, FbxLayerElement::eTextureDiffuse);

	for (unsigned int i = 0; i < finalVertex->size(); i++)
	{
		IndexHeader tempIndex;

		tempVertex->pos[0] = finalVertex->at(i).pos[0];
		tempVertex->pos[1] = finalVertex->at(i).pos[1];
		tempVertex->pos[2] = finalVertex->at(i).pos[2];

		tempVertex->normal[0] = finalVertex->at(i).normal[0];
		tempVertex->normal[1] = finalVertex->at(i).normal[1];
		tempVertex->normal[2] = finalVertex->at(i).normal[2];

		tempVertex->biTangent[0] = finalVertex->at(i).biTangent[0];
		tempVertex->biTangent[1] = finalVertex->at(i).biTangent[1];
		tempVertex->biTangent[2] = finalVertex->at(i).biTangent[2];

		tempVertex->tangent[0] = finalVertex->at(i).tangent[0];
		tempVertex->tangent[1] = finalVertex->at(i).tangent[1];
		tempVertex->tangent[2] = finalVertex->at(i).tangent[2];

		if (vertex->size() != 0)
		{
			for (unsigned int j = 0; j < vertex->size(); j++)
			{
				if (vertex->at(j).pos[0] == tempVertex->pos[0] &&
					vertex->at(j).pos[1] == tempVertex->pos[1] &&
					vertex->at(j).pos[2] == tempVertex->pos[2] &&
					vertex->at(j).normal[0] == tempVertex->normal[0] &&
					vertex->at(j).normal[1] == tempVertex->normal[1] &&
					vertex->at(j).normal[2] == tempVertex->normal[2] &&
					vertex->at(j).biTangent[0] == tempVertex->biTangent[0] &&
					vertex->at(j).biTangent[1] == tempVertex->biTangent[1] &&
					vertex->at(j).biTangent[2] == tempVertex->biTangent[2] &&
					vertex->at(j).tangent[0] == tempVertex->tangent[0] &&
					vertex->at(j).tangent[1] == tempVertex->tangent[1] &&
					vertex->at(j).tangent[2] == tempVertex->tangent[2])
				{
					UVCounter++;
					existWithinVerts = true;
					//tempIndex.vertIndex = j;
					//indices.push_back(tempIndex);
				}
			}
			if (existWithinVerts)
			{
				bool aleadyIndexed = false;
				FbxVector2 uv = uvVertices->GetAt(pMesh->GetTextureUVIndex(i, UVCounter));

				tempVertex->uv[0] = uv[0];
				tempVertex->uv[1] = uv[1];

				UVCounter = 0;
				for (unsigned int j = 0; j < vertex->size(); j++)
				{
					if (vertex->at(j).pos[0] == tempVertex->pos[0] &&
						vertex->at(j).pos[1] == tempVertex->pos[1] &&
						vertex->at(j).pos[2] == tempVertex->pos[2] &&
						vertex->at(j).normal[0] == tempVertex->normal[0] &&
						vertex->at(j).normal[1] == tempVertex->normal[1] &&
						vertex->at(j).normal[2] == tempVertex->normal[2] &&
						vertex->at(j).biTangent[0] == tempVertex->biTangent[0] &&
						vertex->at(j).biTangent[1] == tempVertex->biTangent[1] &&
						vertex->at(j).biTangent[2] == tempVertex->biTangent[2] &&
						vertex->at(j).tangent[0] == tempVertex->tangent[0] &&
						vertex->at(j).tangent[1] == tempVertex->tangent[1] &&
						vertex->at(j).tangent[2] == tempVertex->tangent[2] &&
						vertex->at(j).uv[0] == tempVertex->uv[0] &&
						vertex->at(j).uv[1] == tempVertex->uv[1])
					{
						aleadyIndexed = true;
						tempIndex.vertIndex = j;
						indices.push_back(tempIndex);
						break;
					}
				}
				if (!aleadyIndexed)
				{
					tempIndex.vertIndex = indexCounter;
					indexCounter++;
					indices.push_back(tempIndex);
				}
				vertex->push_back(*tempVertex);
			}
			if (!existWithinVerts)
			{
				FbxVector2 uv = uvVertices->GetAt(pMesh->GetTextureUVIndex(i, 0));

				tempVertex->uv[0] = uv[0];
				tempVertex->uv[1] = uv[1];

				vertex->push_back(*tempVertex);

				tempIndex.vertIndex = indexCounter;
				indexCounter++;
				indices.push_back(tempIndex);
			}
		}
		else
		{
			FbxVector2 uv = uvVertices->GetAt(pMesh->GetTextureUVIndex(i, 0));

			tempVertex->uv[0] = uv[0];
			tempVertex->uv[1] = uv[1];

			vertex->push_back(*tempVertex);

			tempIndex.vertIndex = indexCounter;
			indexCounter++;
			indices.push_back(tempIndex);
		}
		existWithinVerts = false;
	}
	/*for (unsigned int i = 0; i < finalVertex->size(); i++)
	{
		IndexHeader tempIndex;

		tempVertex->pos[0] = finalVertex->at(i).pos[0];
		tempVertex->pos[1] = finalVertex->at(i).pos[1];
		tempVertex->pos[2] = finalVertex->at(i).pos[2];

		tempVertex->normal[0] = finalVertex->at(i).normal[0];
		tempVertex->normal[1] = finalVertex->at(i).normal[1];
		tempVertex->normal[2] = finalVertex->at(i).normal[2];

		tempVertex->biTangent[0] = finalVertex->at(i).biTangent[0];
		tempVertex->biTangent[1] = finalVertex->at(i).biTangent[1];
		tempVertex->biTangent[2] = finalVertex->at(i).biTangent[2];

		tempVertex->tangent[0] = finalVertex->at(i).tangent[0];
		tempVertex->tangent[1] = finalVertex->at(i).tangent[1];
		tempVertex->tangent[2] = finalVertex->at(i).tangent[2];

		tempVertex->uv[0] = finalVertex->at(i).uv[0];
		tempVertex->uv[1] = finalVertex->at(i).uv[1];

		if (vertex->size() != 0)
		{
			for (unsigned int j = 0; j < vertex->size(); j++)
			{
				if (vertex->at(j).pos[0] == tempVertex->pos[0] &&
					vertex->at(j).pos[1] == tempVertex->pos[1] &&
					vertex->at(j).pos[2] == tempVertex->pos[2] &&
					vertex->at(j).normal[0] == tempVertex->normal[0] &&
					vertex->at(j).normal[1] == tempVertex->normal[1] &&
					vertex->at(j).normal[2] == tempVertex->normal[2] &&
					vertex->at(j).biTangent[0] == tempVertex->biTangent[0] &&
					vertex->at(j).biTangent[1] == tempVertex->biTangent[1] &&
					vertex->at(j).biTangent[2] == tempVertex->biTangent[2] &&
					vertex->at(j).tangent[0] == tempVertex->tangent[0] &&
					vertex->at(j).tangent[1] == tempVertex->tangent[1] &&
					vertex->at(j).tangent[2] == tempVertex->tangent[2] &&
					vertex->at(j).uv[0] == tempVertex->uv[0] &&
					vertex->at(j).uv[0] == tempVertex->uv[0])
				{
					existWithinVerts = true;
					tempIndex.vertIndex = j;
					indices.push_back(tempIndex);
					break;
				}
			}
			if (!existWithinVerts)
			{
				tempIndex.vertIndex = indexCounter;
				vertex->push_back(*tempVertex);
				indices.push_back(tempIndex);
				indexCounter++;
			}
		}
		else
		{
			tempIndex.vertIndex = indexCounter;
			vertex->push_back(*tempVertex);
			indices.push_back(tempIndex);
			indexCounter++;
		}
		existWithinVerts = false;
	}*/
	FbxLayerElementUV* elem = pMesh->GetElementUV();

	for (int i = 0; i < indices.size(); i++)
	{
		outPutMesh->indices->push_back(indices.at(i));
	}
	if (!hasSkeleton)
	{
		outPutMesh->verticesNoSkeleton->resize(vertex->size());
		for (int i = 0; i < vertex->size(); i++)
		{
			outPutMesh->verticesNoSkeleton->at(i).pos[0] = vertex->at(i).pos[0];
			outPutMesh->verticesNoSkeleton->at(i).pos[1] = vertex->at(i).pos[1];
			outPutMesh->verticesNoSkeleton->at(i).pos[2] = vertex->at(i).pos[2];

			outPutMesh->verticesNoSkeleton->at(i).normal[0] = vertex->at(i).normal[0];
			outPutMesh->verticesNoSkeleton->at(i).normal[1] = vertex->at(i).normal[1];
			outPutMesh->verticesNoSkeleton->at(i).normal[2] = vertex->at(i).normal[2];

			outPutMesh->verticesNoSkeleton->at(i).tangent[0] = vertex->at(i).tangent[0];
			outPutMesh->verticesNoSkeleton->at(i).tangent[1] = vertex->at(i).tangent[1];
			outPutMesh->verticesNoSkeleton->at(i).tangent[2] = vertex->at(i).tangent[2];

			outPutMesh->verticesNoSkeleton->at(i).biTangent[0] = vertex->at(i).biTangent[0];
			outPutMesh->verticesNoSkeleton->at(i).biTangent[1] = vertex->at(i).biTangent[1];
			outPutMesh->verticesNoSkeleton->at(i).biTangent[2] = vertex->at(i).biTangent[2];

			outPutMesh->verticesNoSkeleton->at(i).uv[0] = vertex->at(i).uv[0];
			outPutMesh->verticesNoSkeleton->at(i).uv[1] = vertex->at(i).uv[1];
		}
	}
	else
	{
		outPutMesh->vertices->resize(vertex->size());
		for (int i = 0; i < vertex->size(); i++)
		{
			outPutMesh->vertices->at(i).pos[0] = vertex->at(i).pos[0];
			outPutMesh->vertices->at(i).pos[1] = vertex->at(i).pos[1];
			outPutMesh->vertices->at(i).pos[2] = vertex->at(i).pos[2];

			outPutMesh->vertices->at(i).normal[0] = vertex->at(i).normal[0];
			outPutMesh->vertices->at(i).normal[1] = vertex->at(i).normal[1];
			outPutMesh->vertices->at(i).normal[2] = vertex->at(i).normal[2];

			outPutMesh->vertices->at(i).tangent[0] = vertex->at(i).tangent[0];
			outPutMesh->vertices->at(i).tangent[1] = vertex->at(i).tangent[1];
			outPutMesh->vertices->at(i).tangent[2] = vertex->at(i).tangent[2];

			outPutMesh->vertices->at(i).biTangent[0] = vertex->at(i).biTangent[0];
			outPutMesh->vertices->at(i).biTangent[1] = vertex->at(i).biTangent[1];
			outPutMesh->vertices->at(i).biTangent[2] = vertex->at(i).biTangent[2];

			outPutMesh->vertices->at(i).uv[0] = vertex->at(i).uv[0];
			outPutMesh->vertices->at(i).uv[1] = vertex->at(i).uv[1];
		}
		for (int i = 0; i < vertCount; i++)
			GetSkeletonWeights(pMesh, i, outPutMesh);
	}
	delete vertex;
	delete finalVertex;
	//delete tempVertex;
	//std::vector<FbxVector2> bajs;
	//FbxLayerElementArrayTemplate<FbxVector2> bajs(elem->GetDirectArray());

	////bajs = elem->GetDirectArray();
	//int test = bajs.GetCount();
	//if (elem->GetMappingMode() == FbxLayerElement::eByPolygonVertex)
	//	std::cout << "rätt";
	//if (elem->GetMappingMode() == FbxLayerElement::eByControlPoint)
	//	std::cout << "fel";

	//Get all the mesh elements (normals, binormals, position...)
	//for (unsigned int i = 0; i < vertCount; i++)
	//{
	//	if (hasSkeleton)
	//	{
	//		GetVertPositions(pMesh, i, outPutMesh->vertices->at(i).pos);
	//		GetVertNormals(pMesh->GetElementNormal(), i, outPutMesh->vertices->at(i).normal);
	//		GetVertBiNormals(pMesh->GetElementBinormal(), i, outPutMesh->vertices->at(i).biTangent);
	//		GetVertTangents(pMesh->GetElementTangent(), i, outPutMesh->vertices->at(i).tangent);
	//		GetVertTextureUV(pMesh->GetElementUV(), i, outPutMesh->vertices->at(i).uv);
	//		GetSkeletonWeights(pMesh, i, outPutMesh);
	//	}
	//	else
	//	{
	//		GetVertPositions(pMesh, i, outPutMesh->verticesNoSkeleton->at(i).pos);
	//		GetVertNormals(pMesh->GetElementNormal(), i, outPutMesh->verticesNoSkeleton->at(i).normal);
	//		GetVertBiNormals(pMesh->GetElementBinormal(), i, outPutMesh->verticesNoSkeleton->at(i).biTangent);
	//		GetVertTangents(pMesh->GetElementTangent(), i, outPutMesh->verticesNoSkeleton->at(i).tangent);
	//		GetVertTextureUV(pMesh->GetElementUV(), i, outPutMesh->verticesNoSkeleton->at(i).uv);
	//	}
	//	//test print
	//	/*std::cout << "Vert #" << i
	//		<< " (" << vertices.at(i).position[0]
	//		<< "," << vertices.at(i).position[1]
	//		<< "," << vertices.at(i).position[2]
	//		<< ")" << "\n\t"
	//		<< "normal: (" << vertices.at(i).normal[0]
	//		<< "," << vertices.at(i).normal[1]
	//		<< "," << vertices.at(i).normal[2]
	//		<< ")" << "\n\t"
	//		<< "BiNormal: (" << vertices.at(i).biNormal[0]
	//		<< "," << vertices.at(i).biNormal[1]
	//		<< ")" << "\n\t"
	//		<< "Tangents: (" << vertices.at(i).tangents[0]
	//		<< "," << vertices.at(i).tangents[1]
	//		<< ")" << "\n\t"
	//		<< "UVs: (" << vertices.at(i).uv[0]
	//		<< "," << vertices.at(i).uv[1]
	//		<< ")" << "\n";*/
	//}
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

void MeshHandler::GetVertTextureUV(fbxsdk::FbxGeometryElementUV * uvElement, int index, double * targetUV)
{
	FbxVector2 uvs = uvElement->GetDirectArray().GetAt(index);
	targetUV[0] = uvs[0];
	targetUV[1] = uvs[1];
}

void MeshHandler::GetSkeletonWeights(fbxsdk::FbxMesh * pMesh, int index, MeshExport* outputMesh)
{
	//int numDeformers = pMesh->GetDeformerCount();
	FbxSkin * pSkin = (FbxSkin*)pMesh->GetDeformer(0, FbxDeformer::eSkin);
	if (pSkin != NULL)
	{
		int boneCount = pSkin->GetClusterCount();
		for (int boneIndex = 0; boneIndex < boneCount; boneIndex++)
		{
			WeigthsHeader tempWeight;
			FbxCluster * pCluster = pSkin->GetCluster(boneIndex);
			FbxNode* pBone = pCluster->GetLink();

			//std::cout << "\n\n" << pBone->GetName();

			//int * pBoneVertIndices = pCluster->GetControlPointIndices();
			double * pBoneVertWeights = pCluster->GetControlPointWeights();

			//int numBoneVertIndices = pCluster->GetControlPointIndicesCount();

				//store the weights here in the mesh vertices
			//int boneVertexIndex = pBoneVertIndices[index];
			//double boneWeight = pBoneVertWeights[index];
			for (int i = 0; i < pCluster->GetControlPointIndicesCount(); i++)
			{
				if (index == pCluster->GetControlPointIndices()[i])
				{
					tempWeight.influence = pBoneVertWeights[index];
					tempWeight.jointID = boneIndex;

					outputMesh->weights.at(index).push_back(tempWeight);
					break;
				}
			}
		}
		
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
	{
		return true;
		

	}
	else
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
