#pragma once
#include "BRFImporterStructs.h"
#include "fbxSDK.h"
#include <fstream>
class MorphAnimExport
{
public:
	MorphAnimExport();
	~MorphAnimExport();

	BRFImporter::MorphAnimHeader								  * morphAnim;
	std::vector<BRFImporter::MorphAnimKeyFrameHeader>			  * morphFrames;
	std::vector<std::vector<BRFImporter::MorphVertexHeader>>	  * morphVertices; //2d vector,

	void WriteToBinaryFile(std::ofstream* outfile);
};

