#include "GroupExport.h"

using namespace BRFImporter;

void GroupExport::WriteToBinaryFile(std::ofstream * outfile)
{
	this->attrInfo.boolAmount		 = (unsigned int)this->groupAttributesContainer->boolAttributes  .size();
	this->attrInfo.floatAmount	     = (unsigned int)this->groupAttributesContainer->floatAttributes .size();
	this->attrInfo.stringAmount		 = (unsigned int)this->groupAttributesContainer->stringAttributes.size();
	this->attrInfo.intAmount		 = (unsigned int)this->groupAttributesContainer->intAttributes	 .size();
	this->attrInfo.vectorAmount		 = (unsigned int)this->groupAttributesContainer->vectorAttributes.size();


	
	
	std::cout << "name: " << this->groupInfo.groupName << std::endl;
	std::cout << "translation :("<<this->groupInfo.translation[0]<<","<<this->groupInfo.translation[1]<<","<<this->groupInfo.translation[2]<<")"<<std::endl;
	std::cout << "rotation    :("<<this->groupInfo.rotation[0]<<","<<this->groupInfo.rotation[1]<<","<<this->groupInfo.rotation[2]<<")"<<std::endl;
	std::cout << "scale       :("<<this->groupInfo.scale[0]<<","<<this->groupInfo.scale[1]<<","<<this->groupInfo.scale[2]<<")"<<std::endl;
	for (int i = 0; i < groupAttributesContainer->vectorAttributes.size(); i++)
	{
		std::cout << "VectorName:" << this->groupAttributesContainer->vectorAttributes.at(i).attrName << std::endl;
		std::cout << "Value     :" << this->groupAttributesContainer->vectorAttributes.at(i).value << std::endl;
	}
	for (int i = 0; i < groupAttributesContainer->intAttributes.size(); i++)
	{
		std::cout << "IntName:" << this->groupAttributesContainer->intAttributes.at(i).attrName << std::endl;
		std::cout << "Min    :" << this->groupAttributesContainer->intAttributes.at(i).min << std::endl;
		std::cout << "max    :" << this->groupAttributesContainer->intAttributes.at(i).max << std::endl;
		std::cout << "Value  :" << this->groupAttributesContainer->intAttributes.at(i).value << std::endl;
	}
	for (int i = 0; i < groupAttributesContainer->stringAttributes.size(); i++)
	{
		std::cout << "StringName: " << this->groupAttributesContainer->stringAttributes.at(i).attrName << std::endl;
		std::cout << "Value     :" <<  this->groupAttributesContainer->stringAttributes.at(i).value << std::endl;
	}

	for (int i = 0; i < groupAttributesContainer->boolAttributes.size(); i++)
	{
		std::cout << "BoolName :" << this->groupAttributesContainer->boolAttributes.at(i).attrName << std::endl;
		std::cout << "Value    :" << this->groupAttributesContainer->boolAttributes.at(i).value << std::endl;

	}
	for (int i = 0; i < groupAttributesContainer->floatAttributes.size(); i++)
	{
		std::cout << "floatName: " << this->groupAttributesContainer->floatAttributes.at(i).attrName << std::endl;
		std::cout << "Max      : " << this->groupAttributesContainer->floatAttributes.at(i).max << std::endl;
		std::cout << "Min      : " << this->groupAttributesContainer->floatAttributes.at(i).min << std::endl;
		std::cout << "Value    : " << this->groupAttributesContainer->floatAttributes.at(i).value << std::endl;
	}
	std::cout << "EXPORTED SUCCESSFULLY" << "\n\n\n\n";

	if (outfile->is_open())
	{
		outfile->write((const char*)&this->groupInfo, sizeof(GroupHeader)); //write the information of the group to file

																		  
		outfile->write((const char*)this->groupAttributesHeader->data(), sizeof(GroupAttributeHeader)* groupInfo.attrCount);


		if (this->groupAttributesContainer->boolAttributes.size()		> 0)	// Write bool attributes to file
			outfile->write((const char*)this->groupAttributesContainer->boolAttributes.data(), sizeof(BoolAttrHeader) * attrInfo.boolAmount);
		
		if (this->groupAttributesContainer->floatAttributes.size() > 0) 	//write float to file
			outfile->write((const char*)this->groupAttributesContainer->floatAttributes.data(), sizeof(FloatAttrHeader) * attrInfo.floatAmount);
	
		if (this->groupAttributesContainer->intAttributes.size()    > 0)	// write int to file
			outfile->write((const char*)this->groupAttributesContainer->intAttributes.data(), sizeof(IntAttrHeader)* attrInfo.intAmount);

		if (this->groupAttributesContainer->stringAttributes.size() > 0)	// write string to file
			outfile->write((const char*)this->groupAttributesContainer->stringAttributes.data(), sizeof(StringAttrHeader) * attrInfo.stringAmount);

		if (this->groupAttributesContainer->vectorAttributes.size() > 0)	//write vector to file
			outfile->write((const char*)this->groupAttributesContainer->vectorAttributes.data(), sizeof(VectorAttrHeader) * attrInfo.vectorAmount);









	}

}

void GroupExport::addGroupInfo(GroupHeader info)
{

	this->groupInfo = info;
}

GroupExport::GroupExport()
{

	groupAttributesHeader = new std::vector<GroupAttributeHeader>;
	groupAttributesContainer = new groupAttrInfo;
}

GroupExport::~GroupExport()
{
	
	delete groupAttributesContainer;
	delete groupAttributesHeader;
}


AttributesExport * GroupExport::GetAttributeHandler()
{

	if (this->groupAttributes == nullptr)
	{
		groupAttributes = new AttributesExport;
	}


	return groupAttributes;
}
