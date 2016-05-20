#include "GroupHandler.h"

#define PROPERTY ""

GroupHandler::GroupHandler()
{
	tmpAttr = new AttributesExport();
	tmpGroup = new GroupExport();
}


void GroupHandler::GetGroupData(FbxNode * pNode, std::vector<GroupExport*>*outputGroup)
{
	
	
	FbxNodeAttribute::EType lAttributeType = pNode->GetNodeAttribute()->GetAttributeType();

	if (lAttributeType == FbxNodeAttribute::EType::eNull)
	{

		//AttributesExport * outputAttribute = nullptr;

		FbxProperty lProperty = pNode->GetFirstProperty();
		
		int lCount = 0;
		std::cout << "Group has attributes!! " << std::endl;

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

		while (lProperty.IsValid())
		{
			if (lProperty.GetFlag(FbxPropertyFlags::eUserDefined))
			{
				lCount++;
			}
			lProperty = pNode->GetNextProperty(lProperty);
		}

		if (lCount == 0)
		{
			std::cout << "No custom Attributes" << std::endl;
		}
		
		lProperty = pNode->GetFirstProperty();
		int i = 0;

		while (lProperty.IsValid())
		{

			if (lProperty.GetFlag(FbxPropertyFlags::eUserDefined))
			{
				
				FbxDataType lPropertyDataType = lProperty.GetPropertyDataType();

				if (lPropertyDataType.GetType() == eFbxBool)
				{
					FbxString lName = lProperty.GetName();
					memcpy(tmpGroup->boolAttr.attrName, lName, sizeof(char) * 256);
					FbxBool lValue = lProperty.Get<FbxBool>();
					tmpGroup->boolAttr.value = lValue;

					BoolAttrHeader tmp;

					memcpy(tmp.attrName, tmpGroup->boolAttr.attrName, sizeof(char) * 256);

					tmp.value = tmpGroup->boolAttr.value;

					tmpGroup->boolAttributes->push_back(tmp);

				}
				else if (lPropertyDataType.GetType() == eFbxDouble) // float
				{
					FbxString lName = lProperty.GetName();
					memcpy(tmpGroup->floatAttr.attrName, lName, sizeof(char) * 256);
					tmpGroup->floatAttr.value = lProperty.Get<FbxFloat>();
					tmpGroup->floatAttr.min = lProperty.GetMinLimit();
					tmpGroup->floatAttr.max = lProperty.GetMaxLimit();

					FloatAttrHeader tmp;

					memcpy(tmp.attrName, tmpGroup->floatAttr.attrName, sizeof(char) * 256);
					tmp.max = tmpGroup->floatAttr.max;
					tmp.min = tmpGroup->floatAttr.min;
					tmp.value = tmpGroup->floatAttr.value;

					tmpGroup->floatAttributes->push_back(tmp);
				}
				else if (lPropertyDataType.GetType() == eFbxInt)
				{
					FbxString lName = lProperty.GetName();
					memcpy(tmpGroup->intAttr.attrName, lName, sizeof(char) * 256);
					tmpGroup->intAttr.value = lProperty.Get<FbxInt>();
					tmpGroup->intAttr.min = lProperty.GetMinLimit();
					tmpGroup->intAttr.max = lProperty.GetMaxLimit();

					IntAttrHeader tmp;

					memcpy(tmp.attrName, tmpGroup->intAttr.attrName, sizeof(char) * 256);

					tmp.max = tmpGroup->intAttr.max;
					tmp.min = tmpGroup->intAttr.min;
					tmp.value = tmpGroup->intAttr.value;

					tmpGroup->intAttributes->push_back(tmp);
				}
				else if (lPropertyDataType.GetType() == eFbxString)
				{
					FbxString lName = lProperty.GetName();
					memcpy(tmpGroup->stringAttr.attrName, lName, sizeof(char) * 256);
					FbxString lValue = lProperty.Get<FbxString>();
					memcpy(tmpGroup->stringAttr.value, lValue, sizeof(char) * 256);

					StringAttrHeader tmp;

					memcpy(tmp.attrName, tmpGroup->stringAttr.attrName, sizeof(char) * 256);
					memcpy(tmp.value, tmpGroup->stringAttr.value,sizeof(char)*256);

					tmpGroup->stringAttributes->push_back(tmp);
				}
				else if (lPropertyDataType.GetType() == eFbxDouble3) // vector
				{
					FbxString lName = lProperty.GetName();
					memcpy(tmpGroup->vecAttr.attrName, lName, sizeof(char) * 256);
					FbxDouble3 lValue = lProperty.Get<FbxDouble3>();

					tmpGroup->vecAttr.value[0] = lValue[0];
					tmpGroup->vecAttr.value[1] = lValue[1];
					tmpGroup->vecAttr.value[2] = lValue[2];
					

					VectorAttrHeader tmp;

					memcpy(tmp.attrName, tmpGroup->vecAttr.attrName, sizeof(char) * 256);
					tmp.value[0] = tmpGroup->vecAttr.value[0];
					tmp.value[1] = tmpGroup->vecAttr.value[1];
					tmp.value[2] = tmpGroup->vecAttr.value[2];

					tmpGroup->vectorAttributes->push_back(tmp);

				
				}
				i++;
			}
			lProperty = pNode->GetNextProperty(lProperty);
		}

		outputGroup->push_back(tmpGroup);
	
	}
}

BRFImporter::FloatAttrHeader GroupHandler::FloatAttr(AttributesExport * tmpAttr)
{
	FloatAttrHeader tmp;
	FbxString lName = tmpAttr->floatAttr.attrName;
	FbxFloat lValue = tmpAttr->floatAttr.value;
	FbxFloat lMin = tmpAttr->floatAttr.min;
	FbxFloat lMax = tmpAttr->floatAttr.max;

	memcpy(tmp.attrName, lName, sizeof(char) * 256);
	tmp.max = lMax;
	tmp.min = lMin;
	tmp.value = lValue;
	std::cout << "kurwa1" << std::endl;
	std::cout << "\n\nname Of Float: " << tmp.attrName << std::endl;

	return tmp;
}

BRFImporter::IntAttrHeader GroupHandler::intAttr(AttributesExport * tmpAttr)
{
	IntAttrHeader tmp;

	FbxString lName = tmpAttr->intAttr.attrName;
	FbxInt lValue = tmpAttr->intAttr.value;
	FbxInt lMin = tmpAttr->intAttr.min;
	FbxInt lMax = tmpAttr->intAttr.max;

	memcpy(tmp.attrName, lName, sizeof(char) * 256);
	tmp.value = lValue;
	tmp.max = lMax;
	tmp.min = lMin;
	std::cout << "kurwa2" << std::endl;

	return tmp;
}

BRFImporter::StringAttrHeader GroupHandler::stringAttr(AttributesExport * tmpAttr)
{
	StringAttrHeader tmp;

	FbxString lName = tmpAttr->stringAttr.attrName;;
	FbxString lValue = tmpAttr->stringAttr.value;

	memcpy(tmp.attrName, lName, sizeof(char) * 256);
	memcpy(tmp.value, lValue, sizeof(char) * 256);


	std::cout << "name Of String: " << tmp.attrName << std::endl;
	std::cout << "String Value:  " << tmpAttr->stringAttr.value << std::endl;
	std::cout << "kurwa3" << std::endl;

	return tmp;
}

BRFImporter::BoolAttrHeader GroupHandler::boolAttr(AttributesExport * tmpAttr)
{
	BoolAttrHeader tmp;

	FbxString lName = tmpAttr->boolAttr.attrName;
	FbxBool lValue = tmpAttr->boolAttr.value;

	memcpy(tmp.attrName, lName, sizeof(char) * 256);
	tmp.value = lValue;
	std::cout << "kurwa4" << std::endl;
	std::cout << "\n\nname Of Bool: " << lName << std::endl;
	return tmp;
}

BRFImporter::VectorAttrHeader GroupHandler::vectorAttr(AttributesExport * tmpAttr)
{
	VectorAttrHeader tmp;

	FbxString lName = tmpAttr->vecAttr.attrName;
	FbxFloat lValue = tmpAttr->vecAttr.value[3];

	memcpy(tmp.attrName, lName, sizeof(char) * 256);
	tmp.value[0] = tmpAttr->vecAttr.value[0];
	tmp.value[1] = tmpAttr->vecAttr.value[1];
	tmp.value[3] = tmpAttr->vecAttr.value[2];

	std::cout << "kurwa5" << std::endl;
	std::cout << "\nname Of Vector: " << tmp.attrName << std::endl;

	return tmp;
}

GroupHandler::~GroupHandler()
{
	delete tmpGroup;
	
	delete tmpAttr;

}



