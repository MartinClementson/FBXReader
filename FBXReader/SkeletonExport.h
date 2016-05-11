#pragma once
#include "BRFImporterStructs.h"
#include "fbxSDK.h"
#include <fstream>
using namespace BRFImporter;

class SkeletonExport
{
public:
	SkeletonExport();
	~SkeletonExport();
	SkeletonHeader skeletonInfo;
	std::vector<JointHeader>* joints;
	std::vector<AnimationHeader>* animations;
	std::vector<JointCountHeader>* animationJointCount;
	std::vector<FrameHeader>* frames;

	void WriteToBinaryFile(std::ofstream* outfile);
};

