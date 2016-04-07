#include "MaterialHandler.h"
#pragma region Init & Destruct

MaterialHandler::MaterialHandler()
{

}
MaterialHandler::~MaterialHandler()
{

}

#pragma endregion




#pragma region Material Main

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
			materialCount = pNode->GetMaterialCount();
			
	
		if (materialCount > 0)
		{
			
			for (int i = 0; i < materialCount; i++)
			{
				if (pNode->GetMaterial(i))
				{
					FbxSurfaceMaterial *pMaterial = node->GetMaterial(i);
					ProcessData(pMaterial, materialCount);
				}
				
			}
		}
		
	
	}
}

#pragma endregion

#pragma region Process Data

void MaterialHandler::ProcessData(FbxSurfaceMaterial* pMaterial, unsigned int materialCount)
{

	
	std::vector<BRFImporter::MaterialHeader> materials(materialCount);

	BRFImporter::MaterialHeader materialStruct;
	
	//diffuse property
	FbxProperty diffProp = pMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);
	unsigned int diffMapCount = diffProp.GetSrcObjectCount<FbxFileTexture>();
	

	//check if there are texturemaps
	if (diffMapCount == 0)
	{
		GetDiffuse(pMaterial, materialStruct.diffuseVal);
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
		GetSpecular(pMaterial, materialStruct.specularVal);
	}
	else
	{
		GetSpecularMap(specProp, specMapCount);
	}

	//NormalMap properties
	FbxProperty normMapProp = pMaterial->FindProperty(FbxSurfaceMaterial::sBump);
	unsigned int normMapCount = normMapProp.GetSrcObjectCount<FbxFileTexture>();

	if (normMapCount > 0)
	{
		GetNormalMap(normMapProp, normMapCount);
	}

	//GlowMap proporties
	
	FbxProperty glowMapProp = pMaterial->FindProperty(FbxSurfaceMaterial::sEmissive);
	unsigned int glowMapCount = glowMapProp.GetSrcObjectCount<FbxFileTexture>();

	if (glowMapCount > 0)
	{
		GetGlowMap(glowMapProp, glowMapCount);
	}
	
}

#pragma endregion



#pragma region Get Texture Map

void MaterialHandler::GetTextureMap(FbxProperty diffMapProp ,unsigned int mapCount)
{

	std::cout << "filenumbers: " << mapCount << "\n";
	for (int j = 0; j<mapCount; j++)
	{
		const FbxFileTexture* texture = FbxCast<FbxFileTexture>(diffMapProp.GetSrcObject<FbxFileTexture>(j));


		const char* filePath = texture->GetFileName();
		const char* textureName = texture->GetRelativeFileName();

		std::cout << filePath << std::endl;
		std::cout << textureName << std::endl;
	}

	

	

}

#pragma endregion

#pragma region Get Specular Map

//In the alpha channel we have placed cosine power
void MaterialHandler::GetSpecularMap(FbxProperty specProp, unsigned int mapCount)
{
	

	std::cout << "filenumbers: " << mapCount << "\n";
	for (int j = 0; j<mapCount; j++)
	{
		const FbxFileTexture* texture = FbxCast<FbxFileTexture>(specProp.GetSrcObject<FbxFileTexture>(j));


		const char* filePath = texture->GetFileName();
		const char* textureName = texture->GetRelativeFileName();

		std::cout << filePath << std::endl;
		std::cout << textureName << std::endl;
	}
}

#pragma endregion

#pragma region Get Normal Map

void MaterialHandler::GetNormalMap(FbxProperty normMapProp, unsigned int mapCount)
{


	std::cout << "filenumbers: " << mapCount << "\n";
	for (int j = 0; j<mapCount; j++)
	{
		const FbxFileTexture* texture = FbxCast<FbxFileTexture>(normMapProp.GetSrcObject<FbxFileTexture>(j));


		const char* filePath = texture->GetFileName();
		const char* textureName = texture->GetRelativeFileName();

		std::cout << filePath << std::endl;
		std::cout << textureName << std::endl;
	}
}

#pragma endregion

#pragma region Get Glow Map

void MaterialHandler::GetGlowMap(FbxProperty glowMapProp, unsigned int mapCount)
{
	std::cout << "filenumbers: " << mapCount << "\n";
	for (int j = 0; j<mapCount; j++)
	{

		const FbxFileTexture* texture = FbxCast<FbxFileTexture>(glowMapProp.GetSrcObject<FbxFileTexture>(j));

		const char* filePath = texture->GetFileName();
		const char* textureName = texture->GetRelativeFileName();

		std::cout << filePath << std::endl;
		std::cout << textureName << std::endl;

	}
}

#pragma endregion

#pragma region Get Diffuse

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

#pragma endregion

#pragma region Get Specular

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

#pragma endregion
