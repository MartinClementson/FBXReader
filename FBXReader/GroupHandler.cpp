#include "GroupHandler.h"

#define PROPERTY ""

GroupHandler::GroupHandler()
{

}



void GroupHandler::GetGroupData(FbxNode * pNode, std::vector<GroupExport*>*outputGroup)
{
	FbxNodeAttribute::EType lAttributeType = pNode->GetNodeAttribute()->GetAttributeType();
	if (lAttributeType == FbxNodeAttribute::EType::eNull)
	{
		int boolAmount = 0;
		int stringAmount = 0;
		int intAmount = 0;
		int floatAmount = 0;
		int enumAmount = 0;
		int doubleAmount = 0;
		
		int attrCount = pNode->GetNodeAttributeCount();
		FbxProperty prop = pNode->GetFirstProperty();
		std::vector<FbxProperty> properties;

		while (prop != NULL)
		{
			if (prop.GetName().Find("Attr_") == 0 || prop.GetName().Find("attr_") == 0)
			{
				properties.push_back(prop);
			}
			prop = pNode->GetNextProperty(prop);
		}

		for (int i = 0; i < properties.size(); i++)
		{
			std::cout << "\n\nHow many properties in this group: " << properties.size() << std::endl;
			tmpGroup = new GroupExport();

			switch (properties[i].GetPropertyDataType().GetType())
			{
			case eFbxBool:
				std::cout << "\n\nName of attribute: " << properties[i].GetName() << "\n\n";
				std::cout << "\n\nDataType:  " << properties[i].GetPropertyDataType().GetName() << std::endl;
				std::cout << "\n\nTrue/false: " << properties[i].Get<FbxBool>() << std::endl;
				boolAmount++;
				memcpy(tmpGroup->boolAttr.attrName, properties[i].GetName(), sizeof(char) * 256);
				tmpGroup->boolAttr.value = properties[i].Get<FbxBool>();
				break;
			case eFbxFloat:
				std::cout << "\n\nName of attribute: " << properties[i].GetName() << "\n\n";
				std::cout << "\n\nDataType:  " << properties[i].GetPropertyDataType().GetName() << std::endl;
				std::cout << "\n\nFloat: " << properties[i].Get<FbxFloat>() << std::endl;
				floatAmount++;
				memcpy(tmpGroup->floatAttr.attrName, properties[i].GetName(), sizeof(char) * 256);
				tmpGroup->floatAttr.value = properties[i].Get<FbxFloat>();
				tmpGroup->floatAttr.min = properties[i].GetMinLimit();
				tmpGroup->floatAttr.max = properties[i].GetMaxLimit();

				break;
			case eFbxString:
				std::cout << "\n\nName of attribute: " << properties[i].GetName() << "\n\n";
				std::cout << "\n\nDataType:  " << properties[i].GetPropertyDataType().GetName() << std::endl;
				std::cout << "\n\nString: " << properties[i].Get<FbxString>() << std::endl;
				stringAmount++;
				memcpy(tmpGroup->stringAttr.attrName, properties[i].GetName(), sizeof(char) * 256);
				memcpy(tmpGroup->stringAttr.value, properties[i].Get<FbxString>(), sizeof(char) * 256);
				break;
			case eFbxInt:
				std::cout << "\n\nName of attribute: " << properties[i].GetName() << "\n\n";
				std::cout << "\n\nDataType:  " << properties[i].GetPropertyDataType().GetName() << std::endl;
				std::cout << "\n\nInt: " << properties[i].Get<FbxInt>() << std::endl;
				intAmount++;
				memcpy(tmpGroup->intAttr.attrName, properties[i].GetName(), sizeof(char) * 256);
				tmpGroup->intAttr.value = properties[i].Get<FbxInt>();
				tmpGroup->intAttr.min = properties[i].GetMinLimit();
				tmpGroup->intAttr.max = properties[i].GetMaxLimit();
				break;
			case eFbxEnum:
				std::cout << "\n\nName of attribute: " << properties[i].GetName() << "\n\n";
				std::cout << "\n\nDataType:  " << properties[i].GetPropertyDataType().GetName() << std::endl;
				std::cout << "\n\nEnum: " << properties[i].Get<FbxEnum>() << std::endl;
				enumAmount++;
				//memcpy(tmpGroup->, properties[i].GetName(), sizeof(char) * 256);

				break;
			case eFbxDouble:
				std::cout << "\n\nName of attribute: " << properties[i].GetName() << "\n\n";
				std::cout << "\n\nDataType:  " << properties[i].GetPropertyDataType().GetName() << std::endl;
				std::cout << "\n\nDouble: " << properties[i].Get<FbxDouble>() << std::endl;
				doubleAmount++;

				memcpy(tmpGroup->floatAttr.attrName, properties[i].GetName(), sizeof(char) * 256);
				tmpGroup->floatAttr.value = properties[i].Get<FbxDouble>();
				tmpGroup->floatAttr.min = properties[i].GetMinLimit();
				tmpGroup->floatAttr.max = properties[i].GetMaxLimit();
				//memcpy(tmpGroup->, properties[i].GetName(), sizeof(char) * 256);
				
				break;
		
			}
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

			FbxString attrName = properties[i].GetName();
			FbxString datatype = properties[i].GetPropertyDataType().GetName();

			std::cout << "How many custom int's: " << intAmount << "\n\n";
			std::cout << "How many custom booleans: " << boolAmount << "\n\n";
			std::cout << "How many custom strings: " << stringAmount << "\n\n";
			std::cout << "How many custom float: " << floatAmount << "\n\n";
			std::cout << "How many custom Double: " << doubleAmount << "\n\n";
			std::cout << "How many custom enum: " << enumAmount << "\n\n";

			tmpGroup->attrInfo.boolAmount = boolAmount;
			tmpGroup->attrInfo.intAmount = intAmount;
			tmpGroup->attrInfo.floatAmount = floatAmount;
			tmpGroup->attrInfo.stringAmount = stringAmount;

			outputGroup->push_back(tmpGroup);
		}

	}
	
	for (int i = 0; i < pNode->GetChildCount(); i++)
	{

		GetGroupData(pNode->GetChild(i), outputGroup);
		
	}
	
}

void GroupHandler::ProcessGroupData(FbxNode * pGroup,std::vector<GroupExport*>*group)
{	
	
}
GroupHandler::~GroupHandler()
{
	delete tmpGroup;
	


}



