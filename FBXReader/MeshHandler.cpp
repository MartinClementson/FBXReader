#include "MeshHandler.h"
#include <stdio.h>
#include <string.h>
#include <math.h>



MeshHandler::MeshHandler()
{
}


MeshHandler::~MeshHandler()
{
}

void MeshHandler::GetMeshData(FbxNode * pNode, std::vector<MeshExport*>* outputMeshes)
{
	//Recursively extract the children
	for (int j = 0; j < pNode->GetChildCount(); j++)
		GetMeshData(pNode->GetChild(j),outputMeshes);

	

	if (pNode->GetMesh())
	{
		if (!IsBoundingBox(pNode)) // Don't export a mesh that is a boundingBox
		{

			MeshExport* tempMesh = new MeshExport(); // Create a temporary object to fill the information


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

			//std::cout << pNode->GetMaterial(0) << "\n"; //TODO! We need to get info on what material is used here!

			ProcessData(pNode->GetMesh(), tempMesh); //fill the information needed


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

void MeshHandler::ProcessData(FbxMesh * pMesh ,MeshExport* outPutMesh)
{
	/* Here we process all the data for the mesh,
	
	position
	normals
	UV
	tangent
	bitangent
	*/

	FbxGeometryElementMaterial * matte = pMesh->GetElementMaterial(0);
	std::cout << matte->GetOwner();
	//matte->get
	//Get vertices amount
	unsigned int vertCount = pMesh->GetControlPointsCount();
	//outPutMesh->meshInfo.vertexCount = vertCount;

	FbxNode * pNode = (FbxNode*)pMesh->GetDstObject();

	int numMaterials = pNode->GetSrcObjectCount<FbxSurfaceMaterial::ClassId>();
	for (int i = 0; i < numMaterials; i++)
	{
		FbxSurfaceMaterial * mat;
		mat = pNode->GetMaterial(i);
		std::cout << "\n\n" << mat->GetName();
	}


	outPutMesh->vertices->resize(vertCount);

	unsigned int polyCount = pMesh->GetPolygonCount();

	//Get the vertex indices
	int startindex;
	int *vert;
	for (int i = 0; i < polyCount; i++)
	{
		startindex = pMesh->GetPolygonVertexIndex(i); 
		vert = &pMesh->GetPolygonVertices()[startindex];
		int count = pMesh->GetPolygonSize(i);
		for (int j = 0; j < count; j++)
		{

			//std::cout << i << ": " << vert[j] << "\n";
			IndexHeader temp;
			temp.vertIndex = vert[j];
			outPutMesh->Addindex(temp);
		}
	}
	//outPutMesh->meshInfo.indexCount = outPutMesh->indices->size(); //store the amount of indices found

	//Get all the mesh elements (normals, binormals, position...)
	for (int i = 0; i < vertCount; i++)
	{
		GetVertPositions(pMesh, i, outPutMesh->vertices->at(i).pos);
		GetVertNormals(pMesh->GetElementNormal(), i, outPutMesh->vertices->at(i).normal);
	
		
		GetVertBiNormals(pMesh->GetElementBinormal(), i, outPutMesh->vertices->at(i).biTangent);
		
		GetVertTangents(pMesh->GetElementTangent(), i, outPutMesh->vertices->at(i).tangent);
		GetVertTextureUV(pMesh->GetElementUV(), i, outPutMesh->vertices->at(i).uv);
		//test print
		/*std::cout << "Vert #" << i
			<< " (" << vertices.at(i).position[0]
			<< "," << vertices.at(i).position[1]
			<< "," << vertices.at(i).position[2]
			<< ")" << "\n\t"
			<< "normal: (" << vertices.at(i).normal[0]
			<< "," << vertices.at(i).normal[1]
			<< "," << vertices.at(i).normal[2]
			<< ")" << "\n\t"
			<< "BiNormal: (" << vertices.at(i).biNormal[0]
			<< "," << vertices.at(i).biNormal[1]
			<< ")" << "\n\t"
			<< "Tangents: (" << vertices.at(i).tangents[0]
			<< "," << vertices.at(i).tangents[1]
			<< ")" << "\n\t"
			<< "UVs: (" << vertices.at(i).uv[0]
			<< "," << vertices.at(i).uv[1]
			<< ")" << "\n";*/
			

	}
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

void MeshHandler::GetSkeletonWeights(fbxsdk::FbxMesh * pMesh)
{
	//int numDeformers = pMesh->GetDeformerCount();
	FbxSkin * pSkin = (FbxSkin*)pMesh->GetDeformer(0, FbxDeformer::eSkin);
	if (pSkin != NULL)
	{
		int boneCount = pSkin->GetClusterCount();
		for (int boneIndex = 0; boneIndex < boneCount; boneIndex++)
		{
			FbxCluster * pCluster = pSkin->GetCluster(boneIndex);
			FbxNode* pBone = pCluster->GetLink();

			//std::cout << "\n\n" << pBone->GetName();

			int * pBoneVertIndices = pCluster->GetControlPointIndices();
			double * pBoneVertWeights = pCluster->GetControlPointWeights();

			int numBoneVertIndices = pCluster->GetControlPointIndicesCount();
			for (int boneVertIndex = 0; boneVertIndex < numBoneVertIndices; boneVertIndex++)
			{
				//store the weights here in the mesh vertices
				int boneVertexIndex = pBoneVertIndices[boneVertIndex];
				double boneWeight = pBoneVertWeights[boneVertIndex];
			}
		}
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
			

			//Find the extentions of the axises
			
			for (int i = 0; i < vertCount; i++)
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
