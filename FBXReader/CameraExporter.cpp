#include "CameraExporter.h"

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
	std::cout << "Intrest position: X:" << cameras->at(0).intrest[0] << "Y: " << cameras->at(0).intrest[1] << "Y: " << cameras->at(0).intrest[2] << "\n";

	std::cout << "Camera position: X:" << cameras->at(0).position[0] << "Y: " << cameras->at(0).position[1] << "Y: " << cameras->at(0).position[2] << "\n";

	std::cout << "Camera Roll" << cameras->at(0).roll;
}