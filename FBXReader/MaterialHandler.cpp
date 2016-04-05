#include "MaterialHandler.h"

MaterialHandler::MaterialHandler()
{

}
MaterialHandler::~MaterialHandler()
{

}

void MaterialHandler::GetMaterialData(FbxNode * pNode)
{
	//Recursively extract the children
	for (int j = 0; j < pNode->GetChildCount(); j++)
		GetMaterialData(pNode->GetChild(j));



	if (pNode->GetMaterial)
	{

		std::cout << pNode->GetName() << std::endl;

		
		ProcessData(pNode->GetMaterialCount, pNode->GetMaterialCount);
	}
}

void MaterialHandler::ProcessData(FbxSurfaceMaterial* material, unsigned int materialCount)
{

	
	std::vector<dummyStructVert> vertices();

	GetAmbient(material, );
}

