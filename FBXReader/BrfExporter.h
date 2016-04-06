#pragma once
#include <vector>
#include "BRFImporterStructs.h"
#include "MeshExport.h"
#include "LightExport.h"
#include "SkeletonExport.h"
#include "MorphAnimExport.h"


using namespace BRFImporter;

#pragma region Explaination
/*
	By : Martin Clementson

	This class is the main hub for all the information we convert
	from the fbx file that is bound to go into the BRF file.
	It has classes for all the types and it's dynamic.

	In the end we will call "WriteToBinaryFile". What it does is
	that it gathers the information from the vector arrays
	and fills the "sceneInfo" struct with the information.
	Then it starts by printing the mainHeader to the BRF.
	After that it will call all the objects in each vector array.
	Easy object will have their own "WriteToBinaryFile" function
	where we pass on a pointer to the file output stream.
	

	So everything will be written to the BRF file. Then the process is done


*/
#pragma endregion

class BrfExporter
{
private:

	MainHeader sceneInfo;

	MeshExport* meshes;
	std::vector<MaterialHeader>* materials;
	std::vector<SkeletonExport>* skeletons;
	std::vector<LightExport>* lights;
	std::vector<GroupHeader>* groups;
	std::vector<MorphAnimExport>* morphAnim;

public:
	BrfExporter();
	~BrfExporter();

	void WriteToBinaryFile(char* fileName); //return type could change


	MeshExport * GetMeshesRef()			{return this->meshes; };
	std::vector<MaterialHeader>* GetMatRef()		{ return this->materials; };
	std::vector<SkeletonExport>* GetSkeletonRef()   { return this->skeletons; };
	std::vector<LightExport>* GetLightsRef()		{ return this->lights; };
	std::vector<GroupHeader>* GetGroupsRef()		{ return this->groups; };
	std::vector<MorphAnimExport>* GetMorphAnimRef() {return this->morphAnim; };

	
};

