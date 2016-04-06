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

	void DisplayLight(FbxNode * pNode, double* pos);

	void SpotLight(FbxLight * pLight);

	void Directional(FbxLight * pLight);

	void PointLight(FbxLight * pLight);

	void ProcessLightData(FbxNode * pNode, FbxLight * pLight);

	void DisplayDefaultValues(FbxLight * pLight);

};
#endif // !GETLIGHT_H