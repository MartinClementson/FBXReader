#pragma once

#ifndef GROUPEXPORT_H
#define GROUPEXPORT_H

#include <vector>
#include "fbxSDK.h"
#include "BRFImporterStructs.h"
#include "AttributesExport.h"
#include <fstream>
#include <iostream>

using namespace BRFImporter;

class GroupExport
{
public:
	struct groupAttrInfo
	{
		std::vector<VectorAttrHeader> vectorAttributes;
		std::vector<StringAttrHeader> stringAttributes;
		std::vector<FloatAttrHeader> floatAttributes;
		std::vector<BoolAttrHeader> boolAttributes;
		std::vector<IntAttrHeader> intAttributes;
	};
	void WriteToBinaryFile(std::ofstream* outfile);
	GroupHeader groupInfo;
	//


	std::vector<GroupAttributeHeader>* groupAttributesHeader;
	groupAttrInfo* groupAttributesContainer;
	AttributesHeader attrInfo;

	AttributesExport* groupAttributes = nullptr;

	void addGroupInfo(GroupHeader info);

	GroupExport();
	~GroupExport();

	AttributesExport* GetAttributeHandler();

private: 


};





#endif // !1

