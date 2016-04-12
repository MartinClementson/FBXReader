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
	/*for (int i = 0; i < joints->size(); i++)
	{
		delete &joints->at(i);
	}
	delete joints;
	for (int i = 0; i < animations->size(); i++)
	{
		delete &animations->at(i);
	}
	delete animations;
	for (int i = 0; i < animationJointCount->size(); i++)
	{
		delete &animationJointCount->at(i);
	}
	delete animationJointCount;
	for (int i = 0; i < frames->size(); i++)
	{
		delete &frames->at(i);
	}
	delete frames;*/
	//if (joints != nullptr)
	//{
	//	joints->clear();
	//	joints = NULL;
	//	delete joints;
	//	//joints->shrink_to_fit();
	//}
	//if (animations != nullptr)
	//{
	//	animations->clear();
	//	animations = NULL;
	//	delete animations;
	//	//animations->shrink_to_fit();
	//}
	//if (animationJointCount != nullptr)
	//{
	//	animationJointCount->clear();
	//	animationJointCount = NULL;
	//	delete animationJointCount;
	//	//animationJointCount->shrink_to_fit();
	//}
	//if (frames != nullptr)
	//{
	//	frames->clear();
	//	frames = NULL;
	//	delete frames;
	//	//frames->shrink_to_fit();
	//}
}

void SkeletonExport::WriteToBinaryFile(std::ofstream * outfile)
{
}
