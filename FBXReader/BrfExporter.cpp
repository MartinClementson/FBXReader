#include "BrfExporter.h"



BrfExporter::BrfExporter()
{
	meshes = new MeshExport;
	materials = new std::vector<MaterialHeader>;
	skeletons = new std::vector<SkeletonExport> ;
	lights = new std::vector<LightExport> ;
	groups = new std::vector<GroupHeader>;
	morphAnim = new std::vector<MorphAnimExport>;
}


BrfExporter::~BrfExporter()
{
	delete meshes;
	delete materials;
	delete skeletons;
	delete lights;
	delete groups;
	delete morphAnim;
}

void BrfExporter::WriteToBinaryFile(char * fileName)
{
		//Stubby stub stub!
}
