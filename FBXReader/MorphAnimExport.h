#pragma once
#include "BRFImporterStructs.h"
#include "fbxSDK.h"
#include <fstream>
class MorphAnimExport
{
public:
	MorphAnimExport();
	~MorphAnimExport();

	std::vector<BRFImporter::MorphAnimHeader>		  * morphAnim;
	std::vector<BRFImporter::MorphAnimKeyFrameHeader> * morphFrames;
	std::vector<BRFImporter::MorphVertexHeader>		  * morphVertices;

	void WriteToBinaryFile(std::ofstream* outfile);
};

