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

	void GetGroupData(FbxNode* pNode,std::vector<GroupExport*>* outputGroup);



private:

	
	void ProcessGroupData(FbxNode* pGroup, std::vector<GroupExport*>*group);

};
#endif // !GROUPHANDLER