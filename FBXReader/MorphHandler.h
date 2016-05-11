#pragma once
#include "BRFImporterStructs.h"
#include "fbxSDK.h"
#include "MorphAnimExport.h"

class MorphHandler
{
public:
	MorphHandler();
	~MorphHandler();

	void GetMorphData(FbxNode* pNode, std::vector<MorphAnimExport>* outputMesh);	
};