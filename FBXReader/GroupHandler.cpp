#include "GroupHandler.h"

GroupHandler::GroupHandler()
{

}

GroupHandler::~GroupHandler()
{

}

void GroupHandler::GetGroupData(FbxNode * pNode)
{

	int nrAttr = pNode->GetNodeAttributeCount();

	for(int i = 0; i < nrAttr; i++)
	{
	
		FbxNodeAttribute * nodeAttr = pNode->GetNodeAttributeByIndex(i);
		FbxNodeAttribute::EType attrType = nodeAttr->GetAttributeType();
		

		switch (attrType)
		{
			case 
		}
	}

	for (int i = 0; i < pNode->GetChildCount(); i++)
	{
		FbxNode* lChild = pNode->GetChild(i);
		if (lChild->GetNodeAttribute())
		{
			if (lChild->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eMesh)
			{
				FbxMesh* pMesh = (FbxMesh*)lChild->GetNodeAttribute();
			}
			if (lChild->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eLight)
			{
				processLightData();
			}
			if (lChild->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eCamera)
			{
				processCameraData();
			}
		}
		

		std::cout << pNode->GetName() << std::endl;

	}

	if (pNode->GetNodeAttribute())
	{


	}
	
	
}

void GroupHandler::ProcessGroupData(FbxNode * pGroup)
{
	const char * lLevelsGroup;

	


}

//STUFF
//if (pNode->GetMesh())
//{
//	std::cout << pNode->GetName() << std::endl;
//	ProcessData(pNode->GetMesh());
//}
//if (pNode->GetCamera())
//{
//	std::cout << pNode->GetName() << std::endl;
//}
//if (pNode->GetLight())
//{
//	std::cout << pNode->GetName() << std::endl;
//}

