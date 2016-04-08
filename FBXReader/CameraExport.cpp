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
		std::cout << "Camera Name: " << cameras->at(i).camName << "\n";

		std::cout << "Intrest position: X:" << cameras->at(i).intrest[0] << " Y: " << cameras->at(i).intrest[1] << " Z: " << cameras->at(i).intrest[2] << "\n";

		std::cout << "Camera position: X:" << cameras->at(i).position[0] << " Y: " << cameras->at(i).position[1] << " Z: " << cameras->at(i).position[2] << "\n";

		std::cout << "Camera Roll" << cameras->at(i).roll;

		std::cout << "\n\n\n\n";
	}
}