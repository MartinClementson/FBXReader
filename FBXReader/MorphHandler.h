#pragma once
#include "BRFImporterStructs.h"
#include "fbxSDK.h"

class MorphHandler
{
public:
	MorphHandler();
	~MorphHandler();

	void GetMorphData(FbxNode* pNode);
private:
	void ProcessData(FbxGeometry* pGeo);
	
};