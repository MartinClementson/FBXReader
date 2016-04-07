#include "GroupHandler.h"

GroupHandler::GroupHandler()
{

}

GroupHandler::~GroupHandler()
{

}

void GroupHandler::GetGroupData(FbxNode * pNode)
{
	for (int i = 0; i < pNode->GetChildCount(); i++)
	{
		GetGroupData(pNode->GetChild(i));
	}
	if (pNode->GetMesh())
	{
		std::cout << pNode->GetName() << std::endl;
		ProcessData(pNode->GetMesh());
	}
	
		
}

void GroupHandler::ProcessData(FbxMesh * pGroup)
{

}

void GroupHandler::GetTranslation(FbxNode * pNode, double translation)
{

}

void GroupHandler::GetScaling(FbxNode * pNode, double scaling)
{

}

void GroupHandler::GetRotation(FbxNode * pNode, double rotation)
{

}

void GroupHandler::GetName(FbxNode * pNode, char name)
{


}

void GroupHandler::GetId(FbxNode * pNode, unsigned int id)
{


}

void GroupHandler::GetParentId(FbxNode * pGroup, unsigned int id)
{


}


