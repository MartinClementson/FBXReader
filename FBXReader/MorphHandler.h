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
private:
	void processMorphData(FbxNode* pNode, MorphAnimExport &output);
	void processKeyFrames(FbxNode* pNode, MorphAnimExport &output, FbxBlendShapeChannel* morphChannel);

	std::vector<FbxBlendShapeChannel*> animatedChannels;

	int tester;
};