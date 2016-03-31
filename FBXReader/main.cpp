#include "FbxPrintFunctions.h"
#include "GetMeshData.h"

void main()
{

	const char* fileName = "test.fbx";

	FbxManager* fbxManager = FbxManager::Create(); //create the manager, This handles memory management



	/*To import the contents of an FBX file, a FbxIOSettings object and a FbxImporter object must be created. 
	A FbxImporter object is initialized by providing the -
	- filename of the file to import along with a FbxIOSettings object that has been appropriately configured to suit the importing needs (see I/O Settings).*/


	//Create IO settings object
	FbxIOSettings* ios = FbxIOSettings::Create(fbxManager, IOSROOT);
	fbxManager->SetIOSettings(ios);

	//Create the importer using the SDK manager
	FbxImporter* fImporter = FbxImporter::Create(fbxManager,"");

	//use the first argument as the filename for the importer

	if (!fImporter->Initialize(fileName, -1, fbxManager->GetIOSettings()))
	{
		std::cout << "Error loading file" << std::endl;

		std::cout << fImporter->GetStatus().GetErrorString() << std::endl;
		std::getchar();
		return;

	}
	
	std::cout << " THE FILE IS FOUND, HALLELUJA" << std::endl << std::endl;




	//Create a new scene so that the information can be loaded into it from the file
	//The FbxScene object acts as a container for elements existing within the scene.
	FbxScene* scene = FbxScene::Create(fbxManager, "myScene");

	fImporter->Import(scene);
	 
	//the file is imported. Destroy the importer
	fImporter->Destroy();



	FbxNode* rootNode = scene->GetRootNode();
	if (rootNode)
	{

		//PrintNode(rootNode);
		for (int i = 0; i < rootNode->GetChildCount(); i++)
		{
			PrintNode(rootNode->GetChild(i));
			GetMeshData(rootNode->GetChild(i));
		}
	}

	


	ios->Destroy();
	fbxManager->Destroy(); //destroy the manager. do this last
	std::getchar();
	return;

}



