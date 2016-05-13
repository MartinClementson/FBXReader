#include "MorphAnimation.h"



bool MorphAnimation::isATargetMesh(FbxNode * pNode)
{
	char compare[12] ;
	char target [12] ;
	target[0] =  'A' ;
	target[1] =  'N' ;
	target[2] =  'I' ;
	target[3] =  'M' ;
	target[4] =  '_' ;
	target[5] =  'T' ;
	target[6] =  'A' ;
	target[7] =  'R' ;
	target[8] =  'G' ;
	target[9] =  'E' ;
	target[10] = 'T' ;
	target[11] = '\0';
	const char* name = pNode->GetName();
	for (int i = 0; i < 11; i++)
	{
		compare[i] = name[i];
	}
	compare[11] = '\0';
	if (strcmp(compare, target) == 0)
	{
		return true;
	}
	else
		return false;
}

void MorphAnimation::ExtractSourceMesh(FbxNode * pNode)
{


}

void MorphAnimation::ExtractTargetMesh(FbxNode * pNode)
{

	BlendMesh targetMesh;

	FbxMesh*				pMesh			= pNode->GetMesh();
	unsigned int			polyCount		= pMesh->GetPolygonCount();
	std::vector<int>		polyVertices;
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
	for (int i = 0; i < polyVertices.size(); ++i)
	{
		//std::vector<FbxVector2> tempValues;
		BlendVertexHeader tempVertex;

		FbxLayerElementArrayTemplate<FbxVector2>* uvVertices = 0;
		pMesh->GetTextureUV(&uvVertices, FbxLayerElement::eTextureDiffuse);

		//GetVertNormals(pMesh->GetElementNormal(), polyVertices.at(i), tempVertex.normal);

		GetVertPositions(  pMesh,						polyVertices.at(i),   tempVertex.pos	);
		GetPolygonNormals( tempVertex.normal,			&polyNormals.at(i)						);
		GetVertBiNormals(  pMesh->GetElementBinormal(), polyVertices.at(i), tempVertex.biTangent);
		GetVertTangents(   pMesh->GetElementTangent(),  polyVertices.at(i), tempVertex.tangent  );
		//GetVertTextureUV(  pMesh->GetElementUV(),		uvIndex.at(i), tempVertex.uv);

		if (targetMesh.vertices.size() != 0)
		{
			bool existWithinVerts = false;
			for (unsigned int j = 0; j < targetMesh.vertices.size(); j++)
			{
				if (targetMesh.vertices.at(j).pos[0]		== tempVertex.pos[0] &&
					targetMesh.vertices.at(j).pos[1]		== tempVertex.pos[1] &&
					targetMesh.vertices.at(j).pos[2]		== tempVertex.pos[2] &&
					targetMesh.vertices.at(j).normal[0]		== tempVertex.normal[0] &&
					targetMesh.vertices.at(j).normal[1]		== tempVertex.normal[1] &&
					targetMesh.vertices.at(j).normal[2]		== tempVertex.normal[2] &&
					targetMesh.vertices.at(j).biTangent[0]  == tempVertex.biTangent[0] &&
					targetMesh.vertices.at(j).biTangent[1]  == tempVertex.biTangent[1] &&
					targetMesh.vertices.at(j).tangent[0]	== tempVertex.tangent[0] &&
					targetMesh.vertices.at(j).tangent[1]	== tempVertex.tangent[1] ) //exclude UV, for now.
					//&&
					//targetMesh.vertices.at(j).uv[0]			== tempVertex.uv[0] &&
					//targetMesh.vertices.at(j).uv[1]			== tempVertex.uv[1])
				{
					existWithinVerts = true;
					IndexHeader tempInd;
					tempInd.vertIndex = j;
					//outPutMesh->indices->push_back(tempInd); //blend shapes don't need index.
					break;
				}
			}
			if (!existWithinVerts)
			{
				IndexHeader tempInd;
				tempInd.vertIndex = outPutMesh->verticesNoSkeleton->size();
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


	blendMeshes.push_back(targetMesh);
}

void MorphAnimation::ExtractAllMeshesInAnimation(FbxNode * pNode)
{
	for (int i = 0; i < pNode->GetChildCount(); i++)
	{
		ExtractAllMeshesInAnimation(pNode->GetChild(i)); //recursively go down the hierarchy and search for target meshes

		if (isATargetMesh(pNode->GetChild(i)))			 //if we find a target mesh.
		{
			ExtractTargetMesh(pNode->GetChild(i));		 //extract it
		}
	}

}

void MorphAnimation::GetMorphAnimation(FbxNode * pNode)
{
	
		ExtractAllMeshesInAnimation(pNode);

	


	FbxGeometry* pGeo = pNode->GetGeometry();								 // get Source
	int morphAnimCount = pGeo->GetDeformerCount(FbxDeformer::eBlendShape);	 //get amount of targets
	int morphChannelCount;
	int targetShapeCount;
	for (unsigned int i = 0; i < morphAnimCount; i++) //for each target
	{
		FbxBlendShape* morphAnim;
		morphAnim = (FbxBlendShape*)pGeo->GetDeformer(i, FbxDeformer::eBlendShape); //Get the blend shape #i

		morphChannelCount = morphAnim->GetBlendShapeChannelCount(); //Get how many channels the blend shape #i has
		std::cout << "ChannelCount: " << morphChannelCount << "\n\n";
	
		for (unsigned int j = 0; j < morphChannelCount; j++) //for every channel
		{
			std::cout << "channel nr: " << j << "\n";

			FbxBlendShapeChannel* morphChannel;
			morphChannel = morphAnim->GetBlendShapeChannel(j);
			morphChannel->GetBlendShapeDeformer();
			std::cout << "ChannelName: " << morphChannel->GetName() << "\n\n";   //usually blendshapeName.meshName

			targetShapeCount = morphChannel->GetTargetShapeCount();
			std::cout << "Target Shape Count: " << targetShapeCount << "\n\n";
			for (unsigned int k = 0; k < targetShapeCount; k++) //for every shape in this channel
			{
				FbxShape* shape;
			
				shape = morphChannel->GetTargetShape(k);
			}
		
		}



	}

}


MorphAnimation::MorphAnimation()
{
}


MorphAnimation::~MorphAnimation()
{
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