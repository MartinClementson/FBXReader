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
		FbxProperty prop = pNode->GetFirstProperty();
		std::vector<FbxProperty> properties;
		while (prop != NULL)
		{
			if( prop.GetName().Find("Attr_") == 0 || prop.GetName().Find("attr_") == 0)
			{
				properties.push_back(prop);
			}

			prop = pNode->GetNextProperty(prop);
			
		}

			for (int i = 0; i < properties.size(); i++)
			{
				std::cout << "\n\nGroupAttr: " << properties[i].GetName() << "\n\n";
				if (properties[i].HasMaxLimit())
				{
					std::cout << "\n\nMaxLimit: " << properties[i].GetMaxLimit();
				}
				if (properties[i].HasMinLimit())
				{
					std::cout << "\n\nMinLimit: " << properties[i].GetMinLimit();
				}
				switch (properties[i].GetPropertyDataType().GetType())
				{
				case eFbxBool:
					std::cout << "\n\nDataType:  " << properties[i].GetPropertyDataType().GetName() << std::endl;
					std::cout << "\n\nTrue/false: " << properties[i].Get<FbxBool>() << std::endl;
					break;
				case eFbxFloat:
					std::cout << "\n\nDataType:  " << properties[i].GetPropertyDataType().GetName() << std::endl;
					std::cout << "\n\nFloat: " << properties[i].Get<FbxFloat>()<< std::endl;
					break;
				case eFbxString:
					std::cout << "\n\nDataType:  " << properties[i].GetPropertyDataType().GetName() << std::endl;
					std::cout << "\n\nString: " << properties[i].Get<FbxString>()<< std::endl;
					break;
				case eFbxInt:
					std::cout << "\n\nDataType:  " << properties[i].GetPropertyDataType().GetName() << std::endl;
					std::cout << "\n\nInt: " << properties[i].Get<FbxInt>()<< std::endl;
					break;
				case eFbxEnum:
					std::cout << "\n\nDataType:  " << properties[i].GetPropertyDataType().GetName() << std::endl;
					std::cout << "\n\n enum: " <<properties[i].Get<FbxEnum>()<< std::endl;
					break;
				case eFbxDouble:
					std::cout << "\n\nDataType:  " << properties[i].GetPropertyDataType().GetName() << std::endl;
					std::cout << "\n\nDouble: " <<properties[i].Get<FbxDouble>()<< std::endl;
					break;
				}

				FbxInt attrcount = properties.size();
				tmpGroup->groupInfo.attrCount = attrcount;

				memcpy(tmpGroup->groupInfo.groupAttrName, properties[i].GetName(), sizeof(char) * 256);

				memcpy(tmpGroup->groupInfo.dataType, properties[i].GetPropertyDataType().GetName(), sizeof(char) * 256);

				
				outputGroup->push_back(tmpGroup);

			}

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



