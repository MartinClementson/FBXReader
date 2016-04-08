#include "BrfExporter.h"





BrfExporter::BrfExporter()
{
	meshes = new std::vector<MeshExport*>;
	materials = new std::vector<MaterialHeader>;
	skeletons = new std::vector<SkeletonExport> ;
	lights = new LightExport ;
	groups = new std::vector<GroupHeader>;
	morphAnim = new std::vector<MorphAnimExport>;
	cameras = new std::vector<CameraHeader>;
}


BrfExporter::~BrfExporter()
{
	for (unsigned int i = 0; i < meshes->size(); i++)
	{
		delete meshes->at(i);
	}
	delete meshes;

	delete materials;
	delete skeletons;
	delete lights;
	delete groups;
	delete morphAnim;
	delete cameras;
}

void BrfExporter::WriteToBinaryFile(char * fileName)
{

	std::ofstream outfile;
	/*
		Open file as binary
	*/

	//Write the main header first in the file (after golden number)
	CreateFileHeader(); //THis only creates the struct, It does not write to file


	std::cout << "\n\n\n\n\nWriting to binary file ........" << "NOT! \n";
	this->sceneInfo.meshAmount = meshes->size();

	std::cout << "Total amount of meshes exported : " << sceneInfo.meshAmount <<"\n";
	for (unsigned int i = 0; i < sceneInfo.meshAmount; i++)
	{
		std::cout << "Mesh #" << i+1 << "\n";
		meshes->at(i)->WriteToBinaryFile(&outfile);

	}

	if (this->lights != nullptr)
		lights->WriteToBinaryFile(&outfile);
	

}

void BrfExporter::CreateFileHeader()
{
	if (this->lights != nullptr)
		this->sceneInfo.lights = true;
	else
		this->sceneInfo.lights = false;

	this->sceneInfo.meshAmount = this->meshes->size();
	//ADD ALL ATTRIBUTES HERE



}