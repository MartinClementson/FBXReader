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

void MaterialHandler::GetMaterialData(FbxNode * pNode, MaterialExport* outputMat)
{
	//Recursively extract the children
	for (int j = 0; j < pNode->GetChildCount(); j++)
		GetMaterialData(pNode->GetChild(j),outputMat);


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
					ProcessData(pMaterial, materialCount, outputMat);
				}
				
			}
		}
		
	
	}
}

#pragma endregion

#pragma region Process Data

void MaterialHandler::ProcessData(FbxSurfaceMaterial* pMaterial, unsigned int materialCount, MaterialExport* outputMat)
{
	

	

	MaterialHeader materialStruct;
	
	//diffuse property
	FbxProperty diffProp = pMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);
	unsigned int diffMapCount = diffProp.GetSrcObjectCount<FbxFileTexture>();
	
	memcpy(materialStruct.matName, pMaterial->GetName(), sizeof(char) * 256);
	//check if there are texturemaps
	if (diffMapCount > 0)
	{
		memcpy(materialStruct.diffMap, GetTextureMap(diffProp), sizeof(char) * 256);
		materialStruct.diffuseVal[0] = 0.0f;
		materialStruct.diffuseVal[1] = 0.0f;
		materialStruct.diffuseVal[2] = 0.0f;
	}
	else
	{
		GetDiffuse(pMaterial, materialStruct.diffuseVal);
		memcpy(materialStruct.diffMap, "", sizeof(char) * 256);
	}

	//SpecularProperty
	FbxProperty specProp = pMaterial->FindProperty(FbxSurfaceMaterial::sSpecular);
	unsigned int specMapCount = specProp.GetSrcObjectCount<FbxFileTexture>();
	FbxSurfacePhong* tmpCompare = (FbxSurfacePhong*)pMaterial;
	if (specMapCount > 0)
	{
		memcpy(materialStruct.specMap, GetSpecularMap(specProp), sizeof(char) * 256);
		materialStruct.specularVal[0] = 0.0f;
		materialStruct.specularVal[1] = 0.0f;
		materialStruct.specularVal[2] = 0.0f;
		
	}
	else
	{
		if (pMaterial->GetClassId().Is(FbxSurfacePhong::ClassId))
		{
			GetSpecular(pMaterial, materialStruct.specularVal);
			memcpy(materialStruct.specMap, "", sizeof(char) * 256);
		}
		else
		{
			materialStruct.specularVal[0] = 0.0f;
			materialStruct.specularVal[1] = 0.0f;
			materialStruct.specularVal[2] = 0.0f;
			memcpy(materialStruct.specMap, "", sizeof(char) * 256);
		}

	}

	//NormalMap properties
	FbxProperty normMapProp = pMaterial->FindProperty(FbxSurfaceMaterial::sBump);
	unsigned int normMapCount = normMapProp.GetSrcObjectCount<FbxFileTexture>();

	if (normMapCount > 0)
	{
		memcpy(materialStruct.normalMap, GetNormalMap(normMapProp), sizeof(char) * 256);
	}
	else
	{

		memcpy(materialStruct.normalMap, "", sizeof(char) * 256);
	}

	//GlowMap proporties
	
	FbxProperty glowMapProp = pMaterial->FindProperty(FbxSurfaceMaterial::sEmissive);
	unsigned int glowMapCount = glowMapProp.GetSrcObjectCount<FbxFileTexture>();

	if (glowMapCount > 0)
	{
		memcpy(materialStruct.glowMap, GetGlowMap(glowMapProp), sizeof(char) * 256);
	}
	else
	{
		memcpy(materialStruct.glowMap, "", sizeof(char) * 256);
	}

	outputMat->materials->push_back(materialStruct);
	std::cout << "";
	
}

#pragma endregion



#pragma region Get Texture Map

const char* MaterialHandler::GetTextureMap(FbxProperty diffMapProp)
{
	const char* textureName;
	
	const FbxFileTexture* texture = FbxCast<FbxFileTexture>(diffMapProp.GetSrcObject<FbxFileTexture>(0));

	textureName = texture->GetRelativeFileName();

	return textureName;

}

#pragma endregion

#pragma region Get Specular Map

//In the alpha channel we have placed cosine power
const char* MaterialHandler::GetSpecularMap(FbxProperty specProp)
{
	const char* textureName;
	const FbxFileTexture* texture = FbxCast<FbxFileTexture>(specProp.GetSrcObject<FbxFileTexture>(0));
	textureName = texture->GetRelativeFileName();

	return textureName;
	
}

#pragma endregion

#pragma region Get Normal Map

const char* MaterialHandler::GetNormalMap(FbxProperty normMapProp)
{


	const FbxFileTexture* texture = FbxCast<FbxFileTexture>(normMapProp.GetSrcObject<FbxFileTexture>(0));

	const char* textureName = texture->GetRelativeFileName();

	return textureName;

}

#pragma endregion

#pragma region Get Glow Map

const char* MaterialHandler::GetGlowMap(FbxProperty glowMapProp)
{

	const FbxFileTexture* texture = FbxCast<FbxFileTexture>(glowMapProp.GetSrcObject<FbxFileTexture>(0));


	const char* textureName = texture->GetRelativeFileName();

	return textureName;


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
