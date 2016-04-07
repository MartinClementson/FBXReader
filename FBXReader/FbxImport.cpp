#include "FbxImport.h"
#include "BRFImporterStructs.h"




FbxImport::FbxImport()
{
}


FbxImport::~FbxImport()
{
	ios->Destroy();
	fbxManager->Destroy(); //destroy the manager. do this last
}

void FbxImport::ConvertFbxToFile(BrfExporter * outputFile)
{
	for (int i = 0; i < this->rootNode->GetChildCount(); i++)
	{
		GetMeshData(this->rootNode->GetChild(i));
		GetCameraData(this->rootNode->GetChild(i));
		GetSkeletonData(this->rootNode->GetChild(i));
	}
}

void FbxImport::LoadFbxFile(const char * fileName)
{

	fbxManager = FbxManager::Create(); //create the manager, This handles memory management



	/*To import the contents of an FBX file, a FbxIOSettings object and a FbxImporter object must be created.
	A FbxImporter object is initialized by providing the -
	- filename of the file to import along with a FbxIOSettings object that has been appropriately configured to suit the importing needs (see I/O Settings).*/


	//Create IO settings object
	 ios = FbxIOSettings::Create(fbxManager, IOSROOT);
	fbxManager->SetIOSettings(ios);

	//Create the importer using the SDK manager
	FbxImporter* fImporter = FbxImporter::Create(fbxManager, "");

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
	scene = FbxScene::Create(fbxManager, "myScene");

	fImporter->Import(scene);

	//the file is imported. Destroy the importer
	fImporter->Destroy();



	rootNode = scene->GetRootNode();
	




	


}

void FbxImport::PrintNode(FbxNode * pNode)
{
	this->printer.PrintNode(pNode);
}

void FbxImport::PrintScene()
{
	if (rootNode)
	{

		//PrintNode(rootNode);
		for (int i = 0; i < rootNode->GetChildCount(); i++)
		{
			PrintNode(rootNode->GetChild(i));
			
		}
	}

}

void FbxImport::GetMeshData(FbxNode * pNode, BrfExporter* outputClass)
{
	meshHandler.GetMeshData(pNode);

	
}

void FbxImport::GetCameraData(FbxNode* pNode, BrfExporter* outputClass)
{
	cameraHandler.GetCameraData(pNode);

	
}

void FbxImport::GetSkeletonData(FbxNode * pNode, BrfExporter* outputClass)
{
	skeletonHandler.GetSkeletonData(pNode);

	
}

void FbxImport::GetAnimationData(FbxNode * pNode, BrfExporter * outputClass)
{
}

void FbxImport::GetMaterialData(FbxNode * pNode, BrfExporter * outputClass)
{
}

void FbxImport::GetLightData(FbxNode * pNode, BrfExporter * outputClass)
{
}

void FbxImport::GetMorphAnimData(FbxNode * pNode, BrfExporter * outputClass)
{
}

void FbxImport::GetGroupData(FbxNode * pNode, BrfExporter * outputClass)
{
}

void FbxImport::GetAttributesData(FbxNode * pNode, BrfExporter * outputClass)
{
}
