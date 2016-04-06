#include "FbxPrintFunctions.h"
#include "FbxImport.h"
#include "GetMeshData.h"
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC

void main()
{

	const char* fileName = "test2.fbx";
	FbxImport importer;

	importer.LoadFbxFile(fileName); //Load the fbx file
	importer.PrintScene(); 

	BrfExporter outputClass; //create an output class, 

	importer.ConvertFbxToFile(&outputClass); //convert information from fbx to our format

	//information is in the outPutClass.
	outputClass.WriteToBinaryFile("Filename.BRF"); //write to file

	//done
	std::getchar();
	_CrtCheckMemory();
	_CrtDumpMemoryLeaks();
	return;

}



