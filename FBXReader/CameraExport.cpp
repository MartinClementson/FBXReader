#include "CameraExport.h"

using namespace BRFImporter;

CameraExporter::CameraExporter()
{

}

CameraExporter::~CameraExporter()
{

}


void CameraExporter::WriteToBinaryFile(std::ofstream* outfile)
{
	this->mainStruct.cameraAmount = cameras->size();

	for (unsigned int i = 0; i < cameras->size(); i++)
	{
		std::cout << std::endl;

		std::cout << "Camera Name: " << cameras->at(i).camName << "\n";

		std::cout << "Camera position: X:" << cameras->at(i).position[0] << " Y: " << cameras->at(i).position[1] << " Z: " << cameras->at(i).position[2] << "\n";

		std::cout << "Camera Rotation: X:" << cameras->at(i).rotation[0] << " Y: " << cameras->at(i).rotation[1] << " Z: " << cameras->at(i).rotation[2] << "\n";

		std::cout << "\n\n\n";

		if (outfile->is_open())
		{
			outfile->write((const char*)(this->cameras->data()), sizeof(CameraHeader));
		}
	}

}

void CameraExporter::AddCamera(MainHeader info)
{
	this->mainStruct = info;
}

void CameraExporter::AddCamera(CameraHeader input)
{
	this->cameras->push_back(input);
}

