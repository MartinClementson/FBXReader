#include "GroupHandler.h"

#define PROPERTY ""

GroupHandler::GroupHandler()
{
	tmpAttr = new AttributesExport();
	
}


void GroupHandler::GetGroupData(FbxNode * pNode, std::vector<GroupExport*>*outputGroup)
{
	for (int j = 0; j < pNode->GetChildCount(); j++)
		GetGroupData(pNode->GetChild(j), outputGroup);
	
	FbxNodeAttribute::EType lAttributeType = pNode->GetNodeAttribute()->GetAttributeType();
	std::cout << pNode->GetName() << "\n";

	if (lAttributeType == FbxNodeAttribute::EType::eNull)
	{
		GroupExport* tmpGroup = new GroupExport();
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
		tmpGroup->groupInfo.attrCount = lCount;
		
		lProperty = pNode->GetFirstProperty();
		int i = 0;

		while (lProperty.IsValid())
		{

			if (lProperty.GetFlag(FbxPropertyFlags::eUserDefined))
			{
				
				GroupAttributeHeader tempAttr;
				//GroupExport::groupAttrInfo tempInfo;
				FbxDataType lPropertyDataType = lProperty.GetPropertyDataType();

				if (lPropertyDataType.GetType() == eFbxBool) //0
				{
					BoolAttrHeader tmp;

					FbxString lName = lProperty.GetName();
					memcpy(tmp.attrName, lName, sizeof(char) * 256);

					FbxBool lValue = lProperty.Get<FbxBool>();

					tmp.value = lValue;

					tmpGroup->groupAttributesContainer->boolAttributes.push_back(tmp);
					tempAttr.attrNr = 0;
					tmpGroup->groupAttributesHeader->push_back(tempAttr);
				}
				else if (lPropertyDataType.GetType() == eFbxDouble) //1
				{
					FloatAttrHeader tmp;
					FbxString lName = lProperty.GetName();
					memcpy(tmp.attrName, lName, sizeof(char) * 256);
			
					tmp.value	= lProperty.Get<FbxFloat>();
					tmp.min		= (float)lProperty.GetMinLimit();
					tmp.max = (float)lProperty.GetMaxLimit();

					tmpGroup->groupAttributesContainer->floatAttributes.push_back(tmp);
					tempAttr.attrNr = 1;
					tmpGroup->groupAttributesHeader->push_back(tempAttr);
				}

				else if (lPropertyDataType.GetType() == eFbxInt) //2
				{
					IntAttrHeader tmp;

					FbxString lName = lProperty.GetName();
					memcpy(tmp.attrName, lName, sizeof(char) * 256);
					tmp.value = lProperty.Get<FbxInt>();
					tmp.min = (unsigned int)lProperty.GetMinLimit();
					tmp.max = (unsigned int)lProperty.GetMaxLimit();

				
					tmpGroup->groupAttributesContainer->intAttributes.push_back(tmp);
					tempAttr.attrNr = 2;
					tmpGroup->groupAttributesHeader->push_back(tempAttr);
				}
				else if (lPropertyDataType.GetType() == eFbxString) //3
				{

					StringAttrHeader tmp;
					FbxString lName = lProperty.GetName();
					memcpy(tmp.attrName, lName, sizeof(char) * 256);

					FbxString lValue = lProperty.Get<FbxString>();
					memcpy(tmp.value, lValue, sizeof(char) * 256);

					tmpGroup->groupAttributesContainer->stringAttributes.push_back(tmp);
					tempAttr.attrNr = 3;
					tmpGroup->groupAttributesHeader->push_back(tempAttr);
				}

				else if (lPropertyDataType.GetType() == eFbxDouble3) //4
				{

					VectorAttrHeader tmp;

					FbxString lName = lProperty.GetName();
					memcpy(tmp.attrName, lName, sizeof(char) * 256);
					FbxDouble3 lValue = lProperty.Get<FbxDouble3>();

					tmp.value[0] = (float)lValue[0];
					tmp.value[1] = (float)lValue[1];
					tmp.value[2] = (float)lValue[2];
	

				
					tmpGroup->groupAttributesContainer->vectorAttributes.push_back(tmp);
					tempAttr.attrNr = 4;
					tmpGroup->groupAttributesHeader->push_back(tempAttr);
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
	FbxFloat lMin   = tmpAttr->floatAttr.min;
	FbxFloat lMax   = tmpAttr->floatAttr.max;

	memcpy(tmp.attrName, lName, sizeof(char) * 256);
	tmp.max = lMax;
	tmp.min = lMin;
	tmp.value = lValue;
	
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
	//delete tmpGroup;
	
	delete tmpAttr;

}



