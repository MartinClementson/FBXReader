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
	weights.resize(4);
}


MeshExport::~MeshExport()
{
	if (indices != nullptr)
	{
		delete indices;
		indices = nullptr;
	}
	if (vertices != nullptr)
		delete vertices; 
	if (verticesNoSkeleton != nullptr)
		delete verticesNoSkeleton;

	if (this->meshAttributes != nullptr)
		delete meshAttributes;
}

void MeshExport::WriteToBinaryFile(std::ofstream * outfile)
{
	if (this->meshInfo.hasSkeleton)
		meshInfo.vertexCount = (unsigned int)vertices->size();
	else
		meshInfo.vertexCount = (unsigned int)verticesNoSkeleton->size();

	meshInfo.indexCount		 = (unsigned int)indices->size();

	std::cout << "has skeleton:" << (this->meshInfo.hasSkeleton ? "Yes" : "No") << "\n";
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


	if (meshInfo.hasSkeleton)
	{
		for (unsigned int i = 0; i < this->meshInfo.vertexCount; i++)
		{
			while (weights.at(i).size() < 4) //Pad the vertex weights. If it has less than 4 weights. add a weight with zero influence
			{
				WeigthsHeader temp;
				temp.influence = 0.0;
				temp.jointID = 0;
				weights.at(i).push_back(temp);
			}
			std::cout << "\nCurrent weights on vert nr" << i + 1 << ": "
				<< weights.at(i).size();
		}
	}



	//export
	
	if (outfile->is_open())
	{
		outfile->write((const char*)&this->meshInfo, sizeof(MeshHeader)); //write the information of the mesh to file

		//write all the vertices 
		if (this->meshInfo.hasSkeleton)
		{
			outfile->write((const char*)(this->vertices->data()), sizeof(VertexHeader) * this->vertices->size());
			for (unsigned int i = 0; i < this->weights.size(); i++)
				outfile->write((const char*)(&this->weights.at(i).at(0)), sizeof(WeigthsHeader) * 4);
		}
		else
			outfile->write((const char*)(this->verticesNoSkeleton->data()), sizeof(VertexHeaderNoSkeleton) * this->verticesNoSkeleton->size());
	
	
		////write all the indices
		if (this->indices->size() > 0)
			outfile->write((const char*) this->indices->data(), sizeof(IndexHeader) * this->indices->size());
		//outfile->flush();

		//if there is a bounding box, write it to the file.
		if (this->meshInfo.boundingBox)
			outfile->write((const char*)(&this->boundingBox), sizeof(OOBBHeader));

 		std::cout << "EXPORTED SUCCESSFULLY" << "\n\n\n\n\n";
	}
}

#pragma region Addfunctions
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

	// this code is wrong

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
#pragma endregion