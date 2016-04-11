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
	/*delete joints;
	delete animations;
	delete animationJointCount;
	delete frames;*/
	//for (int i = 0; i < joints->size(); i++)
	//{
	//	delete &joints->at(i);
	//	//delete joints->at(i).jointID;
	//	//delete joints->at(i).ParentJointID;
	//	//delete joints->at(i).jointName;
	//	//delete joints->at(i).pos;
	//	//delete joints->at(i).rotation;
	//}
	/*for (int i = 0; i < animations->size(); i++)
	{
		animations->clear.at(i);
	}
	for (int i = 0; i < animationJointCount->size(); i++)
	{
		animationJointCount->clear.at(i);
	}
	for (int i = 0; i < frames->size(); i++)
	{
		frames->clear.at(i);
	}*/
	if (joints != nullptr)
	{
		joints->clear();
		//joints = 0;
		joints->shrink_to_fit();
	}
	if (animations != nullptr)
	{
		animations->clear();
		//animations = 0;
		animations->shrink_to_fit();
	}
	if (animationJointCount != nullptr)
	{
		animationJointCount->clear();
		//animationJointCount = 0;
		animationJointCount->shrink_to_fit();
	}
	if (frames != nullptr)
	{
		frames->clear();
		//frames = 0;
		frames->shrink_to_fit();
	}
}

void SkeletonExport::WriteToBinaryFile(std::ofstream * outfile)
{
}
