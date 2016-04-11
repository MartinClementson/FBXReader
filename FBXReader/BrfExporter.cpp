#include "BrfExporter.h"





BrfExporter::BrfExporter()
{
	meshes = new std::vector<MeshExport*>;
	materials = new MaterialExport;
	skeletons = new std::vector<SkeletonExport> ;
	lights = new LightExport ;
	groups = new std::vector<GroupExport*>;
	morphAnim = new std::vector<MorphAnimExport>;
	cameras = new CameraExporter;
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

	/*
		Open file as binary
	*/
	std::ofstream outfile(fileName, std::ofstream::binary);
	//outfile.write((const char*)&this->goldenNumber, 8);

	////Write the main header first in the file (after golden number)
	CreateFileHeader(); //THis only creates the struct, It does not write to file
	//outfile.write((const char*)&this->sceneInfo, sizeof(MainHeader)); //now write it

	//meshes->at(0)->WriteToBinaryFile(&outfile);
	//outfile.close();

	//std::cout << "\n\n\n\n\nWriting to binary file ........" << "NOT! \n";
	//this->sceneInfo.meshAmount = meshes->size();

	std::cout << "Total amount of meshes exported : " << sceneInfo.meshAmount <<"\n";
	for (unsigned int i = 0; i < sceneInfo.meshAmount; i++)
	{
		std::cout << "Mesh #" << i+1 << "\n";
		meshes->at(i)->WriteToBinaryFile(&outfile);

	}

	for (unsigned int i = 0; i < groups->size(); i++)
	{
		std::cout << "Group #" << i + 1 << "\n";
		groups->at(i)->WriteToBinaryFile(&outfile);
	}


	if (this->cameras != nullptr)
		cameras->WriteToBinaryFile(&outfile);

	if (this->materials != nullptr)
		materials->WriteToBinaryFile(&outfile);

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