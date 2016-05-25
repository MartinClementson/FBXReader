#include "CameraExport.h"

using namespace BRFImporter;

CameraExporter::CameraExporter()
{
	cameras = new std::vector<CameraHeader>;
}

CameraExporter::~CameraExporter()
{
	delete cameras;
}

void CameraExporter::WriteToBinaryFile(std::ofstream* outfile)
{

	for (unsigned int i = 0; i < cameras->size(); i++)
	{
		std::cout << std::endl;

		std::cout << "Camera Name: " << cameras->at(i).camName << "\n";

		std::cout << "Camera position: X:" << cameras->at(i).position[0] << " Y: " << cameras->at(i).position[1] << " Z: " << cameras->at(i).position[2] << "\n";

		std::cout << "Camera Rotation: X:" << cameras->at(i).rotation[0] << " Y: " << cameras->at(i).rotation[1] << " Z: " << cameras->at(i).rotation[2] << "\n";

		std::cout << "\n\n\n";
		

		if (outfile->is_open())
		{
			outfile->write((const char*)(&this->cameras->at(i)), sizeof(CameraHeader));
		}
	}

}
