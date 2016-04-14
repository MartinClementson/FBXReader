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
	MainHeader mainStruct;
public:
	std::vector<CameraHeader>* cameras;
public:
	CameraExporter();
	~CameraExporter();

	void WriteToBinaryFile(std::ofstream* outfile);

	void AddCamera(MainHeader info);

	void AddCamera(CameraHeader input);

};