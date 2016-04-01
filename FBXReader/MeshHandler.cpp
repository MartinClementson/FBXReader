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

		//test print
		std::cout << "Vert #" << i
			<< " (" << vertices.at(i).position[0]
			<< "," << vertices.at(i).position[1]
			<< "," << vertices.at(i).position[2]
			<< ")" << std::endl;

	}
}

void MeshHandler::GetVertPositions(FbxMesh * pMesh, int index, float * targetPos)
{
	FbxVector4 position = pMesh->GetControlPointAt(index);
	targetPos[0] = (float)position[0];
	targetPos[0] = (float)position[0];
	targetPos[0] = (float)position[0];
}
