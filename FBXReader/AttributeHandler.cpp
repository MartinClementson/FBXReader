#include "AttributeHandler.h"
//#include <fbxpropertydef.h>



AttributeHandler::AttributeHandler()
{
	tmpAttr = new AttributesExport();
}

AttributeHandler::~AttributeHandler()
{
	delete tmpAttr;
}

void AttributeHandler::GetAttrData(FbxNode*pNode,AttributesExport* outPutAttributes)
{
	int lCount = 0;
	FbxProperty lProperty = pNode->GetFirstProperty();
	
	//attributes = new AttributesExport();
	std::cout << "Attributes!!  " << std::endl;
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
		std::cout << "No Attributes" << std::endl;
		//attributes = new AttributesExport();
	}

	lProperty = pNode->GetFirstProperty();

	int i = 0;
	while (lProperty.IsValid())
	{
		if (lProperty.GetFlag(FbxPropertyFlags::eUserDefined))
		{
			FbxString lString = lProperty.GetLabel();
			//displaystring here..
			lString = lProperty.GetName();

			FbxDataType lPropertyDataType = lProperty.GetPropertyDataType();

			if (lPropertyDataType.GetType() == eFbxBool)
			{
				FbxString lName = lProperty.GetName();
				memcpy(tmpAttr->floatAttr.attrName, lName, sizeof(char) * 256);
				FbxBool lValue = lProperty.Get<FbxBool>();
				tmpAttr->boolAttr.value = lValue;

				BoolAttrHeader tmp = boolAttr(tmpAttr);
				outPutAttributes->boolAttributes->push_back(tmp);
			}
			else if (lPropertyDataType.GetType() == eFbxDouble)
			{

				FbxString lName = lProperty.GetName();
				memcpy(tmpAttr->floatAttr.attrName, lName, sizeof(char) * 256);
				tmpAttr->floatAttr.min = lProperty.GetMinLimit();
				tmpAttr->floatAttr.max = lProperty.GetMaxLimit();
				tmpAttr->floatAttr.value = lProperty.Get<FbxDouble>();
				FloatAttrHeader tmp = FloatAttr(tmpAttr);
				
				outPutAttributes->floatAttributes->push_back(tmp);

			}
			else if (lPropertyDataType.GetType() == eFbxInt)
			{
				FbxString lName = lProperty.GetName();
				memcpy(tmpAttr->intAttr.attrName, lName, sizeof(char) * 256);
				tmpAttr->intAttr.value = lProperty.Get<FbxInt>();
				tmpAttr->intAttr.max = lProperty.GetMaxLimit();
				tmpAttr->intAttr.min = lProperty.GetMinLimit();
				IntAttrHeader tmp = intAttr(tmpAttr);

				outPutAttributes->intAttributes->push_back(tmp);
			}
			else if (lPropertyDataType.GetType() == eFbxDouble3)
			{		
				FbxString lName = lProperty.GetName();
				FbxDouble3 lValue = lProperty.Get<FbxDouble3>();
				tmpAttr->vecAttr.value[0] = lValue[0];
				tmpAttr->vecAttr.value[1] = lValue[1];
				tmpAttr->vecAttr.value[2] = lValue[2];
				memcpy(tmpAttr->vecAttr.attrName, lName, sizeof(char) * 256);

				VectorAttrHeader tmp = vectorAttr(tmpAttr);
				outPutAttributes->vectorAttributes->push_back(tmp);
	
			}
			else if (lPropertyDataType.GetType() == eFbxString)
			{

				FbxString lName = lProperty.GetName();
				FbxString lValue = lProperty.Get<FbxString>();
				memcpy(tmpAttr->stringAttr.attrName, lName, sizeof(char) * 256);
				memcpy(tmpAttr->stringAttr.value, lValue, sizeof(char) * 256);

				StringAttrHeader tmp = stringAttr(tmpAttr);

				outPutAttributes->stringAttributes->push_back(tmp);
			}

			else
			{
				//nothing
			}
			i++;
		}
		lProperty = pNode->GetNextProperty(lProperty);
		
	
	}
	//delete tmpAttr;

}
BRFImporter::FloatAttrHeader AttributeHandler::FloatAttr(AttributesExport * tmpAttr)
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
BRFImporter::IntAttrHeader AttributeHandler::intAttr(AttributesExport * tmpAttr)
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
BRFImporter::StringAttrHeader AttributeHandler::stringAttr(AttributesExport * tmpAttr)
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
BRFImporter::BoolAttrHeader AttributeHandler::boolAttr(AttributesExport * tmpAttr)
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
BRFImporter::VectorAttrHeader AttributeHandler::vectorAttr(AttributesExport * tmpAttr)
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




