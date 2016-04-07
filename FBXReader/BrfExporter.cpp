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
		//Stubby stub stub! mmmmm... so stubby...
	std::ofstream outfile;


	std::cout << "Writing to binary file ........" << "NOT! \n";
	this->sceneInfo.meshAmount = meshes->size();

	std::cout << "Total amount of meshes exported : " << sceneInfo.meshAmount <<"\n";
	for (unsigned int i = 0; i < sceneInfo.meshAmount; i++)
	{
		std::cout << "Mesh #" << i+1 << "\n";
		meshes->at(i)->WriteToBinaryFile(&outfile);

	}
}
