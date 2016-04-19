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
	std::cout << "Processing skeleton\nNumber of Joints: " << skeletonInfo.jointCount << "\n";
	std::cout << "Number of animations: " << skeletonInfo.animationCount << "\n";

	for (unsigned int i = 0; i < skeletonInfo.jointCount; i++)
	{
		std::cout << "\tJoint name: " << joints->at(i).jointName << "\n";
		std::cout << "\tJoint ID: " << joints->at(i).jointID << "\n";
		std::cout << "\tParent ID: " << joints->at(i).ParentJointID << "\n";
		std::cout << "\tPosition: (" << joints->at(i).pos[0] << ", " << joints->at(i).pos[1]
			<< ", " << joints->at(i).pos[2] << ")\n";
		std::cout << "\tRotation: (" << joints->at(i).rotation[0] << ", "
			<< joints->at(i).rotation[1] << ", " << joints->at(i).rotation[2] << ")\n\n";
	}
	for (unsigned int k = 0; k < skeletonInfo.animationCount; k++)
	{
		int frameIndex = 0;
		std::cout << "\nProcessing animation\nAnimation name: " << animations->at(k).animationName
			<< "\n";
		std::cout << "Animation ID: " << animations->at(k).animationID << "\n";
		std::cout << "Number of joints in this animation: " << animations->at(k).jointCount << "\n";
		for (unsigned int i = 0; i < animations->at(k).jointCount; i++)
		{
			std::cout << "Number of frames for Joint "
				<< animationJointCount->at(i).jointID << ": " << animationJointCount->at(i).frameCount
				<< "\n";
			for (unsigned int j = 0; j < animationJointCount->at(i).frameCount; j++)
			{
				std::cout << "Frame ID: " << frames->at(frameIndex).frameID << "\n";
				std::cout << "Matrix: (" << frames->at(frameIndex).frameMatrix[0][0] << ", "
					<< frames->at(frameIndex).frameMatrix[0][1] << ", " << frames->at(frameIndex).frameMatrix[0][2]
					<< ", " << frames->at(frameIndex).frameMatrix[0][3] << ") etc.\n";
				frameIndex++;
			}
		}
	}
	//export

	if (outfile)
	{
		//write the information of the skeleton to file
		outfile->write((const char*)&this->skeletonInfo, sizeof(SkeletonHeader)); 

		//write all the the joints 
		outfile->write(reinterpret_cast<char*>(this->joints->data()), sizeof(JointHeader) * this->joints->size());

		//write all the animations
		outfile->write(reinterpret_cast<char*>(this->animations->data()), sizeof(AnimationHeader) * this->animations->size());

		//making an int to hold the offset between the frames
		int frameIndex = 0;

		//write the joint/frame animations
		for (unsigned int i = 0; i < animationJointCount->size(); i++)
		{
			//First we write the jointContHeader which hold the information
			//on how many frames that specified joint has the frames
			outfile->write(reinterpret_cast<char*>(&this->animationJointCount->at(i)), sizeof(JointCountHeader));

			//writing the specified number of frames that belong to the
			//processed joint. The frame also holds which animation layer
			//it belongs to (ex. Running animation, Walking animation)
			outfile->write(reinterpret_cast<char*>(&this->frames->at(frameIndex)), sizeof(FrameHeader) * this->animationJointCount->at(i).frameCount);

			//calculating the offset between the frames. Seeing as the
			//layers are stored in a long list, we use the offset to
			//store the frames that belong to the processed joint after
			//we have written the joint
			frameIndex += this->animationJointCount->at(i).frameCount;
		}
	}
}
