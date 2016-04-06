#include "MeshHandler.h"



MeshHandler::MeshHandler()
{
}


MeshHandler::~MeshHandler()
{
}

void MeshHandler::GetMeshData(FbxNode * pNode)
{
	//Recursively extract the children
	for (int j = 0; j < pNode->GetChildCount(); j++)
		GetMeshData(pNode->GetChild(j));


	if (pNode->GetMesh())
	{

		std::cout << pNode->GetName() << std::endl;
		ProcessData(pNode->GetMesh());
	}
}

void MeshHandler::ProcessData(FbxMesh * pMesh)
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
	std::vector<dummyStructVert> vertices(vertCount);
	unsigned int polyCount = pMesh->GetPolygonCount();
	int startindex;
	int *vert;
	//int propCount = pMesh->GetProp
	FbxPropertyHandle handle, test;
	handle = pMesh->GetPropertyHandle();
	FbxProperty prop;
	test = handle.GetChild();
	prop = pMesh->GetFirstProperty();
	//std::cout << handle.GetName() << "\n" << test.GetName() << "\n\n";
	/*std::cout << "\n" << prop.GetName();
	while (prop != NULL)
	{
		prop = pMesh->GetNextProperty(prop);
		std::cout << "\n" << prop.GetName();
	}
	std::cout << "\nEnd of custom attributes\n";*/
	for (int i = 0; i < polyCount; i++)
	{
		startindex = pMesh->GetPolygonVertexIndex(i); 
		vert = &pMesh->GetPolygonVertices()[startindex];
		int count = pMesh->GetPolygonSize(i);
		/*for (int j = 0; j < count; j++)
			std::cout << i << ": " << vert[j] << "\n";*/
	}
	for (int i = 0; i < vertCount; i++)
	{
		GetVertPositions(pMesh, i, vertices.at(i).position);
		GetVertNormals(pMesh->GetElementNormal(), i, vertices.at(i).normal);
		GetVertBiNormals(pMesh->GetElementBinormal(), i, vertices.at(i).biNormal);
		GetVertTangents(pMesh->GetElementTangent(), i, vertices.at(i).tangents);
		GetVertTextureUV(pMesh->GetElementUV(), i, vertices.at(i).uv);
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

void MeshHandler::GetVertPositions(FbxMesh * pMesh, int index, float * targetPos)
{
	FbxVector4 position = pMesh->GetControlPointAt(index);
	targetPos[0] = (float)position[0];
	targetPos[1] = (float)position[1];
	targetPos[2] = (float)position[2];
}

void MeshHandler::GetVertNormals(FbxGeometryElementNormal * pNElement, int index, float * targetNormal)
{
	FbxVector4 normal = pNElement->GetDirectArray().GetAt(index);
	targetNormal[0] = normal[0];
	targetNormal[1] = normal[1];
	targetNormal[2] = normal[2];
}

void MeshHandler::GetVertBiNormals(FbxGeometryElementBinormal * pBNElement, int index, float * targetBiNormal)
{
	FbxVector4 biNormal = pBNElement->GetDirectArray().GetAt(index);
	targetBiNormal[0] = biNormal[0];
	targetBiNormal[1] = biNormal[1];
}

void MeshHandler::GetVertTangents(FbxGeometryElementTangent * pTElement, int index, float * targetTangent)
{
	FbxVector4 tangent = pTElement->GetDirectArray().GetAt(index);
	targetTangent[0] = tangent[0];
	targetTangent[1] = tangent[1];
}

void MeshHandler::GetVertTextureUV(FbxGeometryElementUV * uvElement, int index, float * targetUV)
{
	FbxVector2 uvs = uvElement->GetDirectArray().GetAt(index);
	targetUV[0] = uvs[0];
	targetUV[1] = uvs[1];
}
