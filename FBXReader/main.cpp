#include "FbxPrintFunctions.h"
#include "FbxImport.h"
#include "GetMeshData.h"

void main()
{

	const char* fileName = "Test1.fbx";
	FbxImport importer;

	importer.LoadFbxFile(fileName); //Load the fbx file
	importer.PrintScene(); 

	dummyStructClass outputClass; //create an output class, 

	importer.ConvertFbxToFile(&outputClass); //convert information from fbx to our format

	//information is in the outPutClass.
	// outPutClass.writeTofile(); //write to file

	//done
	std::getchar();
	return;

}



