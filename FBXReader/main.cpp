
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

	const char* fileName = "GroupinGroup.fbx";
	//FbxImport importer;

	//importer.LoadFbxFile(fileName); //Load the fbx file
	//importer.PrintScene(); 
	//const char* fileName = "3_shapes_1_Cam.fbx";
	FbxImport* importer = new FbxImport();
	
	
	importer->LoadFbxFile(fileName); //Load the fbx file
	importer->PrintScene(); 


	BrfExporter* outputClass = new BrfExporter(); //create an output class, 

	importer->ConvertFbxToFile(outputClass); //convert information from fbx to our format

	//information is in the outPutClass.
	outputClass->WriteToBinaryFile("Filename.BRF"); //write to file

	//done

	delete outputClass;
	delete importer;
	std::getchar();
	
	
	

	

	return;

}




