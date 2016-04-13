#include "GroupExport.h"

using namespace BRFImporter;

void GroupExport::WriteToBinaryFile(std::ofstream * outfile)
{

	
	std::cout << "name: " << this->groupInfo.groupName << std::endl;
	std::cout << "translation :("<<this->groupInfo.translation[0]<<","<<this->groupInfo.translation[1]<<","<<this->groupInfo.translation[2]<<")"<<std::endl;
	std::cout << "rotation    :("<<this->groupInfo.rotation[0]<<","<<this->groupInfo.rotation[1]<<","<<this->groupInfo.rotation[2]<<")"<<std::endl;
	std::cout << "scale       :("<<this->groupInfo.scale[0]<<","<<this->groupInfo.scale[1]<<","<<this->groupInfo.scale[2]<<")"<<std::endl;
	std::cout << "AmountOfAttr : " << this->groupInfo.attrCount << std::endl;
	std::cout << "AttrName : " << this->intAttr.attrName <<this->boolAttr.attrName<<this->floatAttr.attrName<<this->stringAttr.attrName<<this->vecAttr.attrName<< std::endl;
	
	std::cout << "EXPORTED SUCCESSFULLY" << "\n\n\n\n";
	

}

void GroupExport::addGroupInfo(GroupHeader info)
{

	this->groupInfo = info;
}

GroupExport::GroupExport()
{

}

GroupExport::~GroupExport()
{
	
}


AttributesExport * GroupExport::GetAttributeHandler()
{
	if (this->groupAttributes == nullptr)
	{
		groupAttributes = new AttributesExport;
	}


	return groupAttributes;
}
