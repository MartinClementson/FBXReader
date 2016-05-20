#pragma once
#include <vector>
#include "BRFImporterStructs.h"
#include "MeshExport.h"
#include "GroupExport.h"
#include "LightExport.h"
#include "SkeletonExport.h"
#include "MorphAnimExport.h"

#include <fstream>

#include "MaterialExport.h"
#include "CameraExport.h"



using namespace BRFImporter;

#pragma region Explaination
/*
	By : Martin Clementson

	This class is the main hub for all the information we convert -
	from the fbx file that is bound to go into the BRF file.
	It has classes for all the types and it's dynamic.

	In the end we will call "WriteToBinaryFile". What it does is -
	that it gathers the information from the vector arrays
	and fills the "sceneInfo" struct with the information.
	Then it starts by printing the goldenNumber & mainHeader to the BRF.
	After that it will call all the objects in each vector array.
	Easy object will have their own "WriteToBinaryFile" function -
	where we pass on a pointer to the file output stream.
	
	So everything will be written to the BRF file. Then the process is done
*/
#pragma endregion

class BrfExporter
{
private:
	int goldenNumber[2] = { 7,6 }; //this is the file identifier

	MainHeader sceneInfo;

	std::vector<MeshExport*>*	  meshes;
	MaterialExport*				  materials;
	std::vector<SkeletonExport*>* skeletons;
	LightExport*				  lights = nullptr;
	CameraExporter*				  cameras = nullptr;
	std::vector<MorphAnimExport*>* morphAnim;

	std::vector<GroupExport*>* groups;
	AttributesExport * attributes;


	void CreateFileHeader(); //this is called before writing to file. it gathers the information for the main header

public:
	BrfExporter();
	~BrfExporter();

	void WriteToBinaryFile(char* fileName); //return type could change
	std::vector<MeshExport*>* GetMeshesRef()		 { return this->meshes;		 };
	MaterialExport* GetMatRef()						 { return this->materials;	 };
	std::vector<SkeletonExport*>* GetSkeletonRef()   { return this->skeletons;	 };
	LightExport* GetLightsRef()						 { return this->lights;		 };
	std::vector<MorphAnimExport*>* GetMorphAnimRef() { return this->morphAnim;	 };
	CameraExporter* GetCamerasRef()					 { return this->cameras;		 };
	std::vector<GroupExport*>* GetGroupsRef()		{ return this->groups; };
	AttributesExport * GetAttributesRef() { return this->attributes; };

	
};

