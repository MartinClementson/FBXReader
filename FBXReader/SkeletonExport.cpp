#include "SkeletonExport.h"



SkeletonExport::SkeletonExport()
{
	joints = new std::vector<JointHeader>;
	animations = new std::vector<AnimationHeader>;
	animationJointCount = new std::vector<JointCountHeader>;
	frames = new std::vector<FrameHeader>;
}


SkeletonExport::~SkeletonExport()
{
	delete joints;
	delete animations;
	delete animationJointCount;
	delete frames;
}

void SkeletonExport::WriteToBinaryFile(std::ofstream * outfile)
{
}
