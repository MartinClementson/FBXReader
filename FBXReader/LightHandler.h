#pragma once

#ifndef LIGHTHANDLER_H
#define LIGHTHANDLER_H

#include "fbxSdk.h"
#include "BRFImporterStructs.h"
#include "LightExport.h"

class LightHandler
{

private:
	
	

	void GetLightPos(FbxNode * pNode, double * lightPosition);

	void GetLightRotation(FbxNode * pNode, double * lightRotation);

	void GetLightScaling(FbxNode * pNode, double * lightScaling);


public:

	LightHandler();
	~LightHandler();

	void GetLightData(FbxNode * pNode, LightExport* lights);

	BRFImporter::SpotLightHeader SpotLight(FbxLight* pLight);

	BRFImporter::DirLightHeader Directional(FbxLight* pLight);

	BRFImporter::PointLightHeader PointLight(FbxLight* pLight);
		

	BRFImporter::AreaLightHeader AreaLight(FbxLight* pLight);

};
#endif // !GETLIGHT_H