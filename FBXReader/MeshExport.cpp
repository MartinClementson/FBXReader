#include "MeshExport.h"




using namespace BRFImporter;
MeshExport::MeshExport()
{

	indices  = new std::vector<IndexHeader>;
	vertices = new std::vector<VertexHeader>;
	
}


MeshExport::~MeshExport()
{
	delete indices;
	delete vertices; 

	if (this->meshAttributes != nullptr)
		delete meshAttributes;
}

void MeshExport::WriteToBinaryFile(std::ofstream * outfile)
{
}

void MeshExport::AddVertex(VertexHeader input)
{
	this->vertices->push_back(input);
}

void MeshExport::Addindex(IndexHeader input)
{
	this->indices->push_back(input);
}

void MeshExport::AddBoundingBox(OOBBHeader input)
{
	
	this->boundingBox = input;
}

void MeshExport::AddWeight(WeigthsHeader input)
{
	if (this->weights.size() < 4) //make sure we have a maximum of 4 weights
	{
		this->weights.push_back(input);

	}
	else
	{
		std::cout << "Maximum amount of weights reached." << "\n"
			<< "Weight not added \n"<<
			"OBJECT ID: " << this->meshInfo.objectID;

		return;
	}
}

void MeshExport::AddMeshInfo(MeshHeader info)
{

	this->meshInfo = info;
}

AttributesExport * MeshExport::GetAttributeHandler()
{

	if (this->meshAttributes == nullptr)
	{
		meshAttributes = new AttributesExport;
	}

	return meshAttributes;
}
