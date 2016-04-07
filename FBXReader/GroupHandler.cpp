#include "GroupHandler.h"

GroupHandler::GroupHandler()
{

}

GroupHandler::~GroupHandler()
{

}

void GroupHandler::GetGroupData(FbxNode * pNode)
{

	//FbxNode* pGroup;

	for (int i = 0; i < pNode->GetChildCount(); i++)
	{
		 pNode->GetChild(i);
		
		if (pNode->GetMesh())
		{
			std::cout << pNode->GetName() << std::endl;
		
		}
		if (pNode->GetLight())
		{
			std::cout << pNode->GetName() << std::endl;
			
		}

		if (pNode->GetCamera())
		{
			std::cout << pNode->GetName() << std::endl;
			
		}

		/*if (lChild->GetNodeAttribute())
		{
			if (lChild->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eMesh)
			{
				FbxMesh* pMesh = (FbxMesh*)lChild->GetNodeAttribute();

			}
			if (lChild->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eLight)
			{
				FbxLight* pLight = (FbxLight*)lChild->GetNodeAttribute();

			}
			if (lChild->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eCamera)
			{
				FbxCamera* pCamera = (FbxCamera*)lChild->GetNodeAttribute();
			}
		}*/
	}

	
	
		
}

void GroupHandler::ProcessGroupData(FbxNode * pGroup)
{	


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

