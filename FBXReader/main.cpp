#include "FbxImport.h"
#include <iostream>

#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)


void main()
{
	#ifdef _DEBUG
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	#endif


	//const char* fileName = "3_lights.fbx"; //lights
	//const char* fileName = "PlayerModel.fbx"; //lights
	//const char* fileName = "onecube.fbx";
	//const char* fileName = "test2.fbx";

	//const char* fileName = "cames.fbx";
	//FbxImport importer;

	//importer.LoadFbxFile(fileName); //Load the fbx file
	//importer.PrintScene(); 
	const char* fileName = "3_shapes_1_Cam.fbx";

	//const char* fileName = "test.fbx"; //lights
	//const char* fileName = "test2.fbx";

	//const char* fileName = "skeleton_and_no_skeleton.fbx";
	//const char* fileName = "3_shapes_1_Cam.fbx";
	//const char* fileName = "blend2_3KeyFrames.fbx";
	//const char* fileName = "complex_blend.fbx";
	//const char* fileName   = "veryComplex_animation_one.fbx";
	//const char* fileName = "EnemyModelAnimated.fbx";
	//const char* fileName = "level_0.fbx";.fbx"
	//const char* fileName = "skeleton_and_no_skeleton.fbx";
	//const char* fileName = "3_shapes_1_Cam.fbx";
	//const char* fileName = "3meshes_1Cam_triangulated.fbx";
	//const char* fileName = "GroupScene.fbx";
	//const char* fileName = "BoundingBoxScene.fbx";

	FbxImport* importer = new FbxImport();
	
	


	importer->LoadFbxFile(fileName);			  //Load the fbx file
	importer->PrintScene(); 
	BrfExporter* outputClass = new BrfExporter(); //create an output class, 
	importer->ConvertFbxToFile(outputClass);	  //convert information from fbx to our format
	//information is in the outPutClass.
	outputClass->WriteToBinaryFile("Filename.BRF");
	//outputClass->WriteToBinaryFile("blyat.BRF"); //write to file

	delete outputClass;
	delete importer;
	std::getchar();

	return;

}
