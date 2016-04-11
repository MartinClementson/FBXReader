#include "GroupHandler.h"

#define PROPERTY ""

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
		FbxProperty prop = pNode->GetFirstProperty();
		std::vector<FbxProperty> properties;
		while (prop != NULL)
		{
			//std::cout << "\n\nProperty name: " << prop.GetName() << "\n\n";
			if( prop.GetName().Find("Attr") == 0 || prop.GetName().Find("attr") == 0)
			{
				if (prop.GetName().Find("Default") == -1)
				{
					properties.push_back(prop);
				}
			}
				//properties.push_back(prop);
			prop = pNode->GetNextProperty(prop);
			
		}

		for (int i = 0; i < properties.size(); i++)
		{
			std::cout << "\n\nGroupAttr: " << properties[i].GetName()<<"\n\n";
		}

		
	/*	
		FbxProperty p = pNode->FindProperty("AttrGroupTest",false);
		if (p.IsValid())
		{
			FbxString nodeName = p.GetName();

			std::cout << "\n\n\n" << "found property: " << nodeName << "\n\n\n";
			memcpy(tmpGroup->groupInfo.groupAttrName, nodeName, sizeof(char) * 256);

		}*/




		

		outputGroup->push_back(tmpGroup);
	}


	for (int i = 0; i < pNode->GetChildCount(); i++)
	{

		GetGroupData(pNode->GetChild(i), outputGroup);
		
	}
	
}

void GroupHandler::ProcessGroupData(FbxNode * pGroup,std::vector<GroupExport*>*group)
{	
	
}



