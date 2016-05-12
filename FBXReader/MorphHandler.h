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

	std::vector<FbxBlendShapeChannel*> animatedChannels;
	std::vector<FbxShape*> animatedTargets;

	struct animatedShapes
	{
		FbxBlendShapeChannel* animatedChannels;
		std::vector<FbxTime> animatedTimes;
	};

	std::vector<animatedShapes> animShapes;
	void processKeyFrames(FbxNode* pNode, animatedShapes &animShape);
	void evaluateAnimation(FbxNode* pNode, MorphAnimExport &output);
	int tester;
};