#pragma once

#ifndef ATTRIBUTEHANDLER_H
#define ATTRIBUTEHANDLER_H

#include "BRFImporterStructs.h"
#include "GroupExport.h"
#include "MeshExport.h"
#include "AttributesExport.h"

class AttributeHandler
{

private:
	AttributesHeader attributes;


public:

	AttributesExport* tmpAttr;
	AttributeHandler();
	~AttributeHandler();

	void GetAttrData(FbxNode* pNode,AttributesExport* outPutAttributes);

	BRFImporter::FloatAttrHeader FloatAttr(AttributesExport*tmpAttr);
	BRFImporter::IntAttrHeader intAttr(AttributesExport*tmpAttr);
	BRFImporter::StringAttrHeader stringAttr(AttributesExport*tmpAttr);
	BRFImporter::BoolAttrHeader boolAttr(AttributesExport*tmpAttr);
	BRFImporter::VectorAttrHeader vectorAttr(AttributesExport*tmpAttr);


};
#endif