#include "MorphAnimExport.h"



MorphAnimExport::MorphAnimExport()
{
	this->morphAnim		= new BRFImporter::MorphAnimHeader;
	this->morphFrames	= new std::vector<BRFImporter::MorphAnimKeyFrameHeader>;
	this->morphVertices = new std::vector<std::vector<BRFImporter::MorphVertexHeader>>;
}


MorphAnimExport::~MorphAnimExport()
{
	delete this->morphAnim;
	delete this->morphFrames;
	delete this->morphVertices;
}

void MorphAnimExport::WriteToBinaryFile(std::ofstream * outfile)
{
	if (outfile->is_open())
	{
		outfile->write((const char*)&this->morphAnim, sizeof(BRFImporter::MorphAnimHeader)); //write the information of the animation to file

		for (size_t frame = 0; frame < morphFrames->size(); frame++)
		{
			outfile->write((const char*)& this->morphFrames->at(frame), sizeof(BRFImporter::MorphAnimKeyFrameHeader)); //frame header
			
			outfile->write((const char*) this->morphVertices->at(frame).data(), sizeof(BRFImporter::MorphVertexHeader)*this->morphVertices->at(frame).size());
		
		}
	} //end if(isopen)
}
