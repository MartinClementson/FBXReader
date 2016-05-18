#include "MorphAnimExport.h"



MorphAnimExport::MorphAnimExport()
{
	this->morphAnim		= new BRFImporter::MorphAnimHeader;
	this->morphFrames	= new std::vector<BRFImporter::MorphAnimKeyFrameHeader>;
	this->morphVertices = new std::vector<BRFImporter::MorphVertexHeader>;
}


MorphAnimExport::~MorphAnimExport()
{
	delete this->morphAnim;
	delete this->morphFrames;
	delete this->morphVertices;
}

void MorphAnimExport::WriteToBinaryFile(std::ofstream * outfile)
{

	for (size_t frame = 0; frame < morphFrames->size(); frame++)
	{
		for (size_t vertex = 0; vertex < morphVertices->size(); vertex++)
		{

		}
	}


}
