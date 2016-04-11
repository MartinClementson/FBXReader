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
	if (joints != nullptr)
	{
		joints->clear();
		joints = nullptr;
	}
	if (animations != nullptr)
	{
		animations->clear();
		animations = nullptr;
	}
	if (animationJointCount != nullptr)
	{
		animationJointCount->clear();
		animationJointCount = nullptr;
	}
	if (frames != nullptr)
	{
		frames->clear();
		frames = nullptr;
	}
}

void SkeletonExport::WriteToBinaryFile(std::ofstream * outfile)
{
}
