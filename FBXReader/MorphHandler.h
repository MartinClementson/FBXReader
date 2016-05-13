#pragma once
#include "BRFImporterStructs.h"
#include "fbxSDK.h"
#include "MorphAnimExport.h"
using namespace BRFImporter;
class MorphHandler
{
public:
	MorphHandler();
	~MorphHandler();

	void GetMorphData(FbxNode* pNode, std::vector<MorphAnimExport>* outputMesh);	
private:
	void processMorphData(FbxNode* pNode, MorphAnimExport &output);
	void M_processMorphData(FbxNode* pNode, MorphAnimExport &output); //martins try
	std::vector<FbxBlendShapeChannel*> animatedChannels;
	std::vector<FbxShape*> animatedTargets;

	struct animatedShapes
	{
		FbxBlendShapeChannel* animatedChannels;
		std::vector<FbxTime> animatedTimes;
	};
	struct sameChannelAnimation
	{
		FbxTime time;
		std::vector<FbxBlendShapeChannel*> morphChannels;
	};

	std::vector<animatedShapes> animShapes;
	void processKeyFrames(FbxNode* pNode, animatedShapes &animShape);
	void evaluateAnimation(FbxNode* pNode, MorphAnimExport &output);
	void transferAnimation(FbxNode* pNode, MorphAnimExport &output, std::vector<sameChannelAnimation> &animations);
	//need an interpolatefunction here
	void GetVertBiNormals(fbxsdk::FbxGeometryElementBinormal* pBNElement, int index, double* targetBiNormal);
	void GetVertTangents(fbxsdk::FbxGeometryElementTangent* pTElement, int index, double* targetTangent);
	void GetPolygonNormals(double * targetNormal, FbxVector4 * sourceNormals);
	int tester;
};