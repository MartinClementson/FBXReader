#include "GroupExport.h"

using namespace BRFImporter;

void GroupExport::WriteToBinaryFile(std::ofstream * outfile)
{
	this->attrInfo.boolAmount = boolAttributes->size();
	this->attrInfo.floatAmount = floatAttributes->size();
	this->attrInfo.stringAmount = stringAttributes->size();
	this->attrInfo.intAmount = intAttributes->size();
	this->attrInfo.vectorAmount = vectorAttributes->size();
	
	std::cout << "name: " << this->groupInfo.groupName << std::endl;
	std::cout << "translation :("<<this->groupInfo.translation[0]<<","<<this->groupInfo.translation[1]<<","<<this->groupInfo.translation[2]<<")"<<std::endl;
	std::cout << "rotation    :("<<this->groupInfo.rotation[0]<<","<<this->groupInfo.rotation[1]<<","<<this->groupInfo.rotation[2]<<")"<<std::endl;
	std::cout << "scale       :("<<this->groupInfo.scale[0]<<","<<this->groupInfo.scale[1]<<","<<this->groupInfo.scale[2]<<")"<<std::endl;
	for (int i = 0; i < vectorAttributes->size(); i++)
	{
		std::cout << "VectorName:" << this->vectorAttributes->at(i).attrName << std::endl;
		std::cout << "Value     :" << this->vectorAttributes->at(i).value << std::endl;
	}
	for (int i = 0; i < intAttributes->size(); i++)
	{
		std::cout << "IntName:" << this->intAttributes->at(i).attrName << std::endl;
		std::cout << "Min    :" << this->intAttributes->at(i).min << std::endl;
		std::cout << "max    :" << this->intAttributes->at(i).max << std::endl;
		std::cout << "Value  :" << this->intAttributes->at(i).value << std::endl;
	}
	for (int i = 0; i < stringAttributes->size(); i++)
	{
		std::cout << "StringName: " << this->stringAttributes->at(i).attrName << std::endl;
		std::cout << "Value     :" << this->stringAttributes->at(i).value << std::endl;
	}

	for (int i = 0; i < boolAttributes->size(); i++)
	{
		std::cout << "BoolName :" << this->boolAttributes->at(i).attrName << std::endl;
		std::cout << "Value    :" << this->boolAttributes->at(i).value << std::endl;

	}
	for (int i = 0; i < floatAttributes->size(); i++)
	{
		std::cout << "floatName: " << this->floatAttributes->at(i).attrName << std::endl;
		std::cout << "Max      : " << this->floatAttributes->at(i).max << std::endl;
		std::cout << "Min      : " << this->floatAttributes->at(i).min << std::endl;
		std::cout << "Value    : " << this->floatAttributes->at(i).value << std::endl;
	}
	std::cout << "EXPORTED SUCCESSFULLY" << "\n\n\n\n";

	if (outfile->is_open())
	{
		outfile->write((const char*)&this->groupInfo, sizeof(GroupHeader)); //write the information of the mesh to file

																		  //write all the vertices 
		for (int i = 0; i < groupInfo.attrCount; i++)
		{
			outfile->write((const char*)&this->groupAttributesH->at(i), sizeof(GroupAttributeHeader));
		}
		for (int i = 0; i < groupInfo.attrCount; i++)
		{
			if (this->groupAttributesH->at(i).attrNr == 0)
				outfile->write((const char*)&this->groupAttributesContainer->at(i).boolAttributes, sizeof(BoolAttrHeader));
			else if (this->groupAttributesH->at(i).attrNr == 1)
				outfile->write((const char*)&this->groupAttributesContainer->at(i).floatAttributes, sizeof(FloatAttrHeader));
			else if (this->groupAttributesH->at(i).attrNr == 2)
				outfile->write((const char*)&this->groupAttributesContainer->at(i).intAttributes, sizeof(IntAttrHeader));
			else if (this->groupAttributesH->at(i).attrNr == 3)
				outfile->write((const char*)&this->groupAttributesContainer->at(i).stringAttributes, sizeof(StringAttrHeader));
			else if (this->groupAttributesH->at(i).attrNr == 4)
				outfile->write((const char*)&this->groupAttributesContainer->at(i).vectorAttributes, sizeof(VectorAttrHeader));
		}


	}

}

void GroupExport::addGroupInfo(GroupHeader info)
{

	this->groupInfo = info;
}

GroupExport::GroupExport()
{
	vectorAttributes = new std::vector<VectorAttrHeader>;
	stringAttributes = new std::vector<StringAttrHeader>;
	floatAttributes = new std::vector<FloatAttrHeader>;
	boolAttributes = new std::vector<BoolAttrHeader>;
	intAttributes = new std::vector<IntAttrHeader>;
	groupAttributesH = new std::vector<GroupAttributeHeader>;
	groupAttributesContainer = new std::vector<groupAttrInfo>;
}

GroupExport::~GroupExport()
{
	delete vectorAttributes;
	delete stringAttributes;
	delete floatAttributes;
	delete boolAttributes;
	delete intAttributes;
	delete groupAttributesH;
	delete groupAttributesContainer;
	for (size_t i = 0; i < groupAttributesContainer->size(); i++)
	{
		delete &groupAttributesContainer->at(i);
	}
}


AttributesExport * GroupExport::GetAttributeHandler()
{

	if (this->groupAttributes == nullptr)
	{
		groupAttributes = new AttributesExport;
	}


	return groupAttributes;
}
