#ifndef MATERIALHANDLER_H
#define MATERIALHANDLER_H

#include "fbxSDK.h"
#include "BRFImporterStructs.h"
#include "BrfExporter.h"
#include "MaterialExport.h"


class MaterialHandler
{
public:
	MaterialHandler();
	~MaterialHandler();

	void GetMaterialData(FbxNode* pNode, std::vector<MaterialHeader>* outputMat);

private:
	void ProcessData(FbxSurfaceMaterial* pMaterial, unsigned int matCount, std::vector<MaterialHeader>* outputMat);

	//get RGB(A) values
	void GetDiffuse(FbxSurfaceMaterial* pMaterial, double *pTargetDiffuse);
	void GetSpecular(FbxSurfaceMaterial* pMaterial, double *pTargetSpecular);

	//GetMaps
	const char* GetTextureMap(FbxProperty diffMapProp, unsigned int mapCount);
	const char* GetSpecularMap(FbxProperty specMapProp, unsigned int mapCount);
	const char* GetNormalMap(FbxProperty normMapProp, unsigned int mapCount);
	const char* GetGlowMap(FbxProperty glowMapProp, unsigned int mapCount);
};


#endif // !MATERIALHANDLER_H