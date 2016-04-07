#pragma once
#include <vector>
#include "BRFImporterStructs.h"
#include "AttributesExport.h"
#include <fstream>
#include <iostream>
using namespace BRFImporter;

#pragma region Explaination
/*
This class handles a single mesh

The functions are used to add the information

in the end when we write to the file. we calculate the
final amount of vertices and indices and add that to the meshInfo struct

*/
#pragma endregion

class MaterialExport
{


public:
	MaterialHeader matInfo;
	MaterialHeader* material;
	AttributesExport* matAttributes = nullptr;

public:
	MaterialExport();
	~MaterialExport();

	void WriteToBinaryFile(std::ofstream* outfile);
	AttributesExport* GetAttributeHandler();
};

