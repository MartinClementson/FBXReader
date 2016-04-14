#pragma once

#ifndef ATTRIBUTESEXPORT_H
#define ATTRIBUTESEXPORT_H

#include <fstream>
#include "BRFImporterStructs.h"
#include <vector>
#include <iostream>
//#include "GroupExport.h"
using namespace BRFImporter;
class AttributesExport
{
public:
	AttributesExport();
	~AttributesExport();
	void WriteToBinaryFile(std::ofstream* outfile);

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


private:
};
#endif // !ATTRIBUTESEXPORT_H
