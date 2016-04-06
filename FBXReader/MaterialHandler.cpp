#include "MaterialHandler.h"

MaterialHandler::MaterialHandler()
{

}
MaterialHandler::~MaterialHandler()
{

}

void MaterialHandler::GetMaterialData(FbxNode * pNode)
{
	//Recursively extract the children
	for (int j = 0; j < pNode->GetChildCount(); j++)
		GetMaterialData(pNode->GetChild(j));
	FbxGeometry* pGeometry = pNode->GetGeometry();
	int materialCount = 0;
	FbxNode* node = NULL;
	if (pGeometry) {
		node = pGeometry->GetNode();
		if (node)
			materialCount = node->GetMaterialCount();
	
		if (materialCount > 0)
		{
			for (int i = 0; i < materialCount; i++)
			{
				FbxSurfaceMaterial *pMaterial = node->GetMaterial(i);
				ProcessData(pMaterial, materialCount);
			}
		}
		
	
	}
}

void MaterialHandler::ProcessData(FbxSurfaceMaterial* pMaterial, unsigned int materialCount)
{

	
	std::vector<BRFImporter::MaterialHeader> materials(materialCount);

	BRFImporter::MaterialHeader tmpMaterial;
	
	//diffuse property
	FbxProperty diffProp = pMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);
	unsigned int diffMapCount = diffProp.GetSrcObjectCount<FbxFileTexture>();

	//check if there are texturemaps
	if (diffMapCount == 0)
	{
		GetDiffuse(pMaterial, tmpMaterial.diffuseVal);
	}
	else
	{
		GetTextureMap(diffProp, diffMapCount);
	}

	//SpecularProperty
	FbxProperty specProp = pMaterial->FindProperty(FbxSurfaceMaterial::sSpecular);
	unsigned int specMapCount = specProp.GetSrcObjectCount<FbxFileTexture>();
	if (diffMapCount == 0)
	{
		GetSpecular(pMaterial, tmpMaterial.specularVal);
	}
	else
	{
		GetSpecular(pMaterial, tmpMaterial.specularVal);
		GetSpecularMap(specProp, specMapCount);
	}
	
	
}

void MaterialHandler::GetTextureMap(FbxProperty diffProp ,unsigned int textureCount)
{

	std::cout << "filenumbers: " << textureCount << "\n";
	for (int j = 0; j<textureCount; j++)
	{
		const FbxFileTexture* texture = FbxCast<FbxFileTexture>(diffProp.GetSrcObject<FbxFileTexture>(j));
		

		const char* filePath = texture->GetFileName();
		const char* textureName = texture->GetRelativeFileName();

		std::cout << filePath << std::endl;
		std::cout << textureName << std::endl;
	}

	

	

}

void MaterialHandler::GetSpecularMap(FbxProperty specProp, unsigned int textureCount)
{
	

	std::cout << "filenumbers: " << textureCount << "\n";
	for (int j = 0; j<textureCount; j++)
	{
		const FbxFileTexture* texture = FbxCast<FbxFileTexture>(specProp.GetSrcObject<FbxFileTexture>(j));


		const char* filePath = texture->GetFileName();
		const char* textureName = texture->GetRelativeFileName();

		std::cout << filePath << std::endl;
		std::cout << textureName << std::endl;
	}
}

void MaterialHandler::GetDiffuse(FbxSurfaceMaterial* pMaterial, double* pTargetDiffuse)
{
	FbxPropertyT<FbxDouble3> lKFbxDouble3;
	FbxPropertyT<FbxDouble> lKFbxDouble1;
	FbxColor theColor;

	lKFbxDouble3 = ((FbxSurfacePhong*)pMaterial)->Diffuse;


	theColor.Set(lKFbxDouble3.Get()[0], lKFbxDouble3.Get()[1], lKFbxDouble3.Get()[2]);
	std::cout << "R: " << theColor.mRed << "G: " << theColor.mGreen << "B: " << theColor.mBlue << std::endl;

	pTargetDiffuse[0] = theColor.mRed;
	pTargetDiffuse[1] = theColor.mGreen;
	pTargetDiffuse[2] = theColor.mBlue;
}


void MaterialHandler::GetSpecular(FbxSurfaceMaterial* pMaterial, double* pTargetSpecular)
{
	FbxPropertyT<FbxDouble3> lKFbxDouble3;
	FbxPropertyT<FbxDouble> lKFbxDouble1;
	FbxColor theColor;

	lKFbxDouble3 = ((FbxSurfacePhong*)pMaterial)->Specular;


	theColor.Set(lKFbxDouble3.Get()[0], lKFbxDouble3.Get()[1], lKFbxDouble3.Get()[2]);
	std::cout << "SR: " << theColor.mRed << "SG: " << theColor.mGreen << "SB: " << theColor.mBlue << std::endl;

	pTargetSpecular[0] = theColor.mRed;
	pTargetSpecular[1] = theColor.mGreen;
	pTargetSpecular[2] = theColor.mBlue;
}

