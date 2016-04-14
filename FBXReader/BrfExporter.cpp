#include "BrfExporter.h"


BrfExporter::BrfExporter()
{
	meshes = new std::vector<MeshExport*>;
	materials = new MaterialExport;
	skeletons = new std::vector<SkeletonExport> ;
	lights = new LightExport;
	groups = new std::vector<GroupHeader>;
	morphAnim = new std::vector<MorphAnimExport>;
	cameras = new std::vector<CameraExporter*>;
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

	std::ofstream outfile(fileName, std::ofstream::binary );
	if (!outfile.is_open())
	{
		std::cout << "Cannot write to file : " << fileName << "\n";
		return;
	}

	outfile.write((const char*)&this->goldenNumber, sizeof(int)*2);

	//Write the main header first in the file (after golden number)
	CreateFileHeader(); //THis only creates the struct, It does not write to file
	outfile.write((const char*)&this->sceneInfo, sizeof(MainHeader)); //now write it

	

	std::cout << "\n\n\n\n\nWriting to binary file ........" << "NOT! \n";
	this->sceneInfo.meshAmount = meshes->size();
	this->sceneInfo.cameraAmount = cameras->size();
	//meshes->at(0)->WriteToBinaryFile(&outfile);

	std::cout << "Total amount of meshes exported : " << sceneInfo.meshAmount <<"\n";
	for (unsigned int i = 0; i < sceneInfo.meshAmount; i++)
	{
		std::cout << "Mesh #" << i << "\n";
		meshes->at(i)->WriteToBinaryFile(&outfile);
	}

	if (this->cameras != nullptr)
	{
		std::cout << "Total amount of cameras exported: " << sceneInfo.cameraAmount << "\n";
		for (unsigned int a = 0; a < sceneInfo.cameraAmount; a++)
		{
			std::cout << "Camera #" << a << "\n";
			cameras->at(a)->WriteToBinaryFile(&outfile);
		}
	}

	if (this->materials != nullptr)
		materials->WriteToBinaryFile(&outfile);

	if (this->lights != nullptr)
		lights->WriteToBinaryFile(&outfile);
	outfile.close();
	
}

void BrfExporter::CreateFileHeader()
{
	if (this->lights != nullptr)
		this->sceneInfo.lights = true;
	else
		this->sceneInfo.lights = false;

	this->sceneInfo.meshAmount = this->meshes->size();

	this->sceneInfo.attributeAmount = 0;

	this->sceneInfo.cameraAmount = this->cameras->size();

	this->sceneInfo.materialAmount = 0;

	this->sceneInfo.groupAmount = 0;

	this->sceneInfo.morphAnimAmount = 0;

	this->sceneInfo.skeletonAmount = 0;
	//ADD ALL ATTRIBUTES HERE



}