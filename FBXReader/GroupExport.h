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

	void WriteToBinaryFile(std::ofstream* outfile);
	GroupHeader groupInfo;
	
	AttributesHeader attrInfo;
	VectorAttrHeader vecAttr;
	StringAttrHeader stringAttr;
	FloatAttrHeader floatAttr;
	BoolAttrHeader boolAttr;
	IntAttrHeader intAttr;

	std::vector<VectorAttrHeader>* vectorAttributes;
	std::vector<StringAttrHeader>*stringAttributes;
	std::vector<FloatAttrHeader>*floatAttributes;
	std::vector<BoolAttrHeader>*boolAttributes;
	std::vector<IntAttrHeader>*intAttributes;

	AttributesExport* groupAttributes = nullptr;

	void addGroupInfo(GroupHeader info);

	GroupExport();
	~GroupExport();

	AttributesExport* GetAttributeHandler();

private: 


};





#endif // !1

