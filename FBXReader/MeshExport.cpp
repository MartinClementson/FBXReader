#include "MeshExport.h"




using namespace BRFImporter;
MeshExport::MeshExport()
{

	indices  = new std::vector<IndexHeader>;
	vertices = new std::vector<VertexHeader>;
	
	
}

MeshExport::MeshExport(bool hasSkeleton)
{
	if (hasSkeleton)
	{
		vertices = new std::vector<VertexHeader>;
		verticesNoSkeleton = NULL;
	}
	else
	{
		vertices = NULL;
		verticesNoSkeleton = new std::vector<VertexHeaderNoSkeleton>;
	}
	indices = new std::vector<IndexHeader>;
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
	meshInfo.vertexCount = vertices->size();
	meshInfo.indexCount = indices->size();

	std::cout << "Mesh name  : " << this->meshInfo.meshName << std::endl;
	std::cout << "Vert amount  : " << this->meshInfo.vertexCount << std::endl;
	std::cout << "Index amount  : " << this->meshInfo.indexCount << std::endl;
	std::cout << "Bounding Box  : " <<  (this->meshInfo.boundingBox ? "Yes" : "NO") << std::endl;
	if (this->meshInfo.boundingBox)
	{
		std::cout << "\t Extents: (" << this->boundingBox.extents[0] << "," << this->boundingBox.extents[1] << "," << this->boundingBox.extents[2] << ")" << std::endl;
		std::cout << "\t Orientation: (" << this->boundingBox.orientation[0] << "," << this->boundingBox.orientation[1] << "," << this->boundingBox.orientation[2] << ")" << std::endl;
	}
	//std::cout << "Test Index: (" << this->indices->at(0).vertIndex << "," << this->indices->at(1).vertIndex << "," << this->indices->at(2).vertIndex << ")" << std::endl;
	std::cout << "Translation: (" << this->meshInfo.translation[0] << "," << this->meshInfo.translation[1] << "," << this->meshInfo.translation[2] << ")" << std::endl;
	
	std::cout << "Rotation   : (" << this->meshInfo.rotation[0] << "," << this->meshInfo.rotation[1] << "," << this->meshInfo.rotation[2] << ")" << std::endl;

	std::cout << "Scale      : (" << this->meshInfo.scale[0] << "," << this->meshInfo.scale[1] << "," << this->meshInfo.scale[2] << ")\n" << std::endl;

	std::cout << "EXPORTED SUCCESSFULLY" << "\n\n\n\n\n";

	for (int i = 0; i < this->meshInfo.vertexCount; i++)
	{
		std::cout << "\nCurrent weights on vert nr" << i+1 << ": "
			<< weights.at(i).size();
	}


	//export

	if (outfile)
	{
		outfile->write((const char*)&this->meshInfo, sizeof(MeshHeader)); //write the information of the mesh to file

		//write all the vertices 
		outfile->write(reinterpret_cast<char*>(&this->vertices[0]), sizeof(VertexHeader) * this->vertices->size());

		//write all the indices
		outfile->write(reinterpret_cast<char*>(&this->indices[0]), sizeof(IndexHeader) * this->indices->size());

		//if there is a bounding box, write it to the file.
		if(this->meshInfo.boundingBox)
			outfile->write(reinterpret_cast<char*>(&this->boundingBox), sizeof(OOBBHeader));

		//write the weights to the file

		//outfile->write(reinterpret_cast<char*>(&this->weights[0]), sizeof(weights) * 4);



		//if there are any attributes, write it to the file.
		if (this->meshInfo.attrCount > 0)
			meshAttributes->WriteToBinaryFile(outfile);

	}



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
	//if (this->weights.size() < 4) //make sure we have a maximum of 4 weights
	//{
	//	this->weights.push_back(input);

	//}
	//else
	//{
	//	std::cout << "Maximum amount of weights reached." << "\n"
	//		<< "Weight not added \n"<<
	//		"OBJECT ID: " << this->meshInfo.objectID;

	//	return;
	//}
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
