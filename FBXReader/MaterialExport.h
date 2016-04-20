#pragma once
#include <vector>
#include "BRFImporterStructs.h"
#include "AttributesExport.h"
#include <fstream>
#include <iostream>
using namespace BRFImporter;

#pragma region Explaination
/*

This class handles all materials

*/

#pragma endregion

class MaterialExport
{
public:
	MainHeader main;

	std::vector<MaterialHeader>* materials;
	

public:
	MaterialExport();
	~MaterialExport();

	void WriteToBinaryFile(std::ofstream* outfile);
};

