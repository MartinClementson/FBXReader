#pragma once
#include "fbxSDK.h"
class FbxPrinter
{
private:
	int numTabs = 0;


public:
	FbxPrinter();
	~FbxPrinter();
	void PrintNode(FbxNode* pNode);

private:
	FbxString GetAttributeTypeName(FbxNodeAttribute::EType type);
	void PrintAttribute(FbxNodeAttribute* pAttribute);
	void PrintTabs();
};

