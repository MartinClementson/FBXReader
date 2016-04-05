#ifndef MATERIALHANDLER_H
#define MATERIALHANDLER_H

#include "fbxSDK.h"


class MaterialHandler
{
public:
	MaterialHandler();
	~MaterialHandler();

	void GetMaterialData(FbxNode* pNode);

private:
	void ProcessData(FbxSurfaceMaterial* material, unsigned int matCount);
	void GetAmbient(FbxSurfaceMaterial* material, float* pTargetAmbient);

};


#endif // !MATERIALHANDLER_H