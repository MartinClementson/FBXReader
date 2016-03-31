#include "GetMeshData.h"
void GetMeshData(FbxNode* pNode)
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

void ProcessData(FbxMesh* pMesh)
{
	//Get vertices amount
	unsigned int vertCount = pMesh->GetControlPointsCount();
	std::vector<dummyStructVert> vertices(vertCount);
	
	
	for (int i = 0; i < vertCount; i++)
	{
		GetVertPositions(pMesh, i,vertices.at(i).position);
		
		//test print
		std::cout << "Vert #" << i 
			<< " (" << vertices.at(i).position[0]
			<< "," << vertices.at(i).position[1]
			<< "," << vertices.at(i).position[2]
			<< ")" << std::endl;

	}
	
}


void GetVertPositions(FbxMesh* pMesh, int index ,float* targetPos)
{
	
	
		FbxVector4 position = pMesh->GetControlPointAt(index);
		targetPos[0] = (float)position[0];
		targetPos[0] = (float)position[0];
		targetPos[0] = (float)position[0];
		
	
}

