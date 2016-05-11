#include "MorphAnimExport.h"



MorphAnimExport::MorphAnimExport()
{
	this->morphAnim = new std::vector<BRFImporter::MorphAnimHeader>;
	this->morphVertices = new std::vector<BRFImporter::MorphVertexHeader>;
}


MorphAnimExport::~MorphAnimExport()
{
	delete this->morphAnim;
	delete this->morphVertices;
}

void MorphAnimExport::WriteToBinaryFile(std::ofstream * outfile)
{
}
