#include "BrfExporter.h"


BrfExporter::BrfExporter()
{
	materials   = new MaterialExport;
	lights		= new LightExport;
	cameras		= new CameraExporter;
	meshes		= new std::vector<MeshExport*>;
	skeletons   = new std::vector<SkeletonExport*>;
	morphAnim	= new std::vector<MorphAnimExport*>;
	groups = new std::vector<GroupExport*>;
	attributes = new AttributesExport;
}


BrfExporter::~BrfExporter()
{
	for (unsigned int i = 0; i < meshes->size(); i++)
		delete meshes->at(i);
	for (unsigned int i = 0; i < skeletons->size(); i++)
		delete skeletons->at(i);
	for (size_t i = 0; i	   < morphAnim->size(); i++)
		delete morphAnim->at(i);
	for (size_t i = 0; i < groups->size(); i++)
	{
		delete groups->at(i);

	}
	delete meshes;
	delete skeletons;
	delete morphAnim;
	delete groups;
	delete materials;
	delete lights;
	delete cameras;
	delete attributes;
}

void BrfExporter::WriteToBinaryFile(const char * fileName)
{
	/*
		Open file as binary
	*/
	std::ofstream outfile(fileName, std::ofstream::binary);
	if (!outfile.is_open())
	{
		std::cout << "Cannot write to file : " << fileName << "\n";
		return;
	}

	outfile.write((const char*)&this->goldenNumber, sizeof(int) * 2);

	//Write the main header first in the file (after golden number)
	CreateFileHeader(); //This only creates the struct, It does not write to file
	outfile.write((const char*)&this->sceneInfo, sizeof(MainHeader)); //now write it

	

	std::cout << "\n\n\n\n\nWriting to binary file .." << "\n";
	this->sceneInfo.meshAmount = (unsigned int)meshes->size();

	std::cout << "Total amount of meshes exported : " << sceneInfo.meshAmount << "\n";

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
	{
		cameras->WriteToBinaryFile(&outfile);
	}

	if (this->materials != nullptr)
	{
			std::cout << "Total amount of materials exported: " << sceneInfo.materialAmount << "\n";
			materials->WriteToBinaryFile(&outfile);
	}
	
	for (unsigned int i = 0; i < sceneInfo.skeletonAmount; i++)
	{
		std::cout << "Skeleton #" << i + 1 << "\n";
		skeletons->at(i)->WriteToBinaryFile(&outfile);
	}
	if (this->lights != nullptr)
		lights->WriteToBinaryFile(&outfile);

	if (this->attributes != nullptr)
		attributes->WriteToBinaryFile(&outfile);

	for (size_t i = 0; i < sceneInfo.morphAnimAmount; i++)
	{
		std::cout << "morph animation #" << i + 1 << "\n";
		morphAnim->at(i)->WriteToBinaryFile(&outfile);
	}
	outfile.close();
	
}

void BrfExporter::CreateFileHeader()
{
	if (this->lights != nullptr)
		this->sceneInfo.lights = true;
	else
		this->sceneInfo.lights = false;

	this->sceneInfo.meshAmount	    = (unsigned int) this->meshes->size();

	this->sceneInfo.skeletonAmount  = (unsigned int)this->skeletons->size();
	//ADD ALL ATTRIBUTES HERE

	this->sceneInfo.attributeAmount = 0;

	this->sceneInfo.cameraAmount	= (unsigned int)cameras->cameras->size();

	this->sceneInfo.materialAmount  = (unsigned int)materials->materials->size();

	this->sceneInfo.groupAmount	    = (unsigned int)this->groups->size();

	this->sceneInfo.morphAnimAmount = (unsigned int)morphAnim->size();

	//this->sceneInfo.skeletonAmount = 0;
	//ADD ALL ATTRIBUTES HERE
}