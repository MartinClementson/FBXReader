#pragma once
#ifndef GROUPHANDLER_H
#define GROUPHANDLER_H

#include "fbxSDK.h"
#include "BRFImporterStructs.h"
#include "GroupExport.h"
#include <string.h>


class GroupHandler
{

public:
	GroupHandler();
	~GroupHandler();
	GroupExport* tmpGroup;

	AttributesExport* tmpAttr;

	void GetGroupData(FbxNode* pNode, std::vector<GroupExport*>* outputGroup);

	BRFImporter::FloatAttrHeader FloatAttr(AttributesExport*tmpAttr);
	BRFImporter::IntAttrHeader intAttr(AttributesExport*tmpAttr);
	BRFImporter::StringAttrHeader stringAttr(AttributesExport*tmpAttr);
	BRFImporter::BoolAttrHeader boolAttr(AttributesExport*tmpAttr);
	BRFImporter::VectorAttrHeader vectorAttr(AttributesExport*tmpAttr);


private:

	
	//void ProcessGroupData(FbxNode* pGroup, std::vector<GroupExport*>*group);

};
#endif // !GROUPHANDLER