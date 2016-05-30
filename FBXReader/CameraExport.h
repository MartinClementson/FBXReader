#pragma once
#include <vector>
#include "BRFImporterStructs.h"
#include "AttributesExport.h"
#include <fstream>
#include <iostream>
using namespace BRFImporter;

#pragma region Explaination
/*

This class handles all cameras

*/
#pragma endregion

class CameraExporter
{
public:
	std::vector<CameraHeader>* cameras;
	CameraHeader camInfo;
	MainHeader mainStruct;
public:
	CameraExporter();
	~CameraExporter();

	void WriteToBinaryFile(std::ofstream* outfile);


};