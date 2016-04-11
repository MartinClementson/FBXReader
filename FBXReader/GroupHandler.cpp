#include "GroupHandler.h"

#define PROPERTY "attribute_name"

GroupHandler::GroupHandler()
{

}

GroupHandler::~GroupHandler()
{

}

void GroupHandler::GetGroupData(FbxNode * pNode, std::vector<GroupExport*>*outputGroup)
{
	FbxNodeAttribute::EType lAttributeType = pNode->GetNodeAttribute()->GetAttributeType();


	if (lAttributeType == FbxNodeAttribute::EType::eNull)
	{
		GroupExport* tmpGroup = new GroupExport();

		std::cout << pNode->GetName() << std::endl;

		memcpy(tmpGroup->groupInfo.groupName, pNode->GetName(), sizeof(char) * 256);

		FbxDouble3 translation = pNode->LclTranslation.Get();
		tmpGroup->groupInfo.translation[0] = translation[0];
		tmpGroup->groupInfo.translation[1] = translation[1];
		tmpGroup->groupInfo.translation[2] = translation[2];

		FbxDouble3 rotation = pNode->LclRotation.Get();
		tmpGroup->groupInfo.rotation[0] = rotation[0];
		tmpGroup->groupInfo.rotation[1] = rotation[1];
		tmpGroup->groupInfo.rotation[2] = rotation[2];

		FbxDouble3 scaling = pNode->LclScaling.Get();
		tmpGroup->groupInfo.scale[0] = scaling[0];
		tmpGroup->groupInfo.scale[1] = scaling[1];
		tmpGroup->groupInfo.scale[2] = scaling[2];

		
		int attrCount = pNode->GetNodeAttributeCount();
		//FbxMesh* pMesh = (FbxMesh*)pNode->GetNodeAttribute();
		
		
		FbxProperty p = pNode->FindProperty(PROPERTY,false);
		if (p.IsValid())
		{
			FbxString nodeName = p.GetName();

			std::cout << "found property: " << nodeName << "\n\n\n";

		}


		

		outputGroup->push_back(tmpGroup);
	}


	for (int i = 0; i < pNode->GetChildCount(); i++)
	{

		GetGroupData(pNode->GetChild(i), outputGroup);
		
	}


	FbxProperty p = pNode->FindProperty("GroupAttrTest", false);
	if (p.IsValid())
	{
		FbxString nodeName = p.GetName();

		std::cout << "found property: " << nodeName << "\n\n\n";

	}
	
	
}

void GroupHandler::ProcessGroupData(FbxNode * pGroup,std::vector<GroupExport*>*group)
{	
	
}



