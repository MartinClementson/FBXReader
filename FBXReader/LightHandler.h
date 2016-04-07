#pragma once

#ifndef LIGHTHANDLER_H
#define LIGHTHANDLER_H

#include "fbxSdk.h"
#include "BRFImporterStructs.h"

class LightHandler
{

private:
	BRFImporter::LightHeader lightTypeStruct;
	BRFImporter::LightHeader light;
	BRFImporter::PointLightHeader point;
	BRFImporter::DirLightHeader directional;
	BRFImporter::SpotLightHeader spot;

	void GetLightPos(FbxNode * pNode, double * lightPosition);

	void GetLightRotation(FbxNode * pNode, double * lightRotation);

	void GetLightScaling(FbxNode * pNode, double * lightScaling);


public:

	LightHandler();
	~LightHandler();

	void DisplayLight(FbxNode * pNode);

	void SpotLight(FbxLight * pLight, float* lightColor);

	void Directional(FbxLight * pLight, float* lightColor);

	void PointLight(FbxLight * pLight, float* lightColor);

	void AreaLight(FbxLight * pLight, float* lightColor);

	void AmbientLight(FbxLight * pLight, float* lightColor);

	void DisplayDefaultValues(FbxLight * pLight);

};
#endif // !GETLIGHT_H