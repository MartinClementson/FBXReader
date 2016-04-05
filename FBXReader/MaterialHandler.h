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
	void ProcessData(FbxSurfaceMaterial* material);


};


#endif // !MATERIALHANDLER_H