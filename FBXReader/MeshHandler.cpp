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

	for (int i = 0; i < vertCount; i++)
	{
		GetVertPositions(pMesh, i, vertices.at(i).position);
		GetVertNormals(pMesh->GetElementNormal(), i, vertices.at(i).normal);

		//test print
		std::cout << "Vert #" << i
			<< " (" << vertices.at(i).normal[0]
			<< "," << vertices.at(i).normal[1]
			<< "," << vertices.at(i).normal[2]
			<< ")" << std::endl;

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
