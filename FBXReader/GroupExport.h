#pragma once

#ifndef GROUPEXPORT_H
#define GROUPEXPORT_H

#include <vector>
#include "fbxSDK.h"
#include "BRFImporterStructs.h"
#include "AttributesExport.h"
#include <fstream>
#include <iostream>

using namespace BRFImporter;

class GroupExport
{
public:

	void WriteToBinaryFile(std::ofstream* outfile);
	GroupHeader groupInfo;

	AttributesExport* groupAttributes = nullptr;



	GroupExport();
	~GroupExport();

	AttributesExport* GetAttributeHandler();
private: 


};





#endif // !1

