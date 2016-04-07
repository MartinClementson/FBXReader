#pragma once

#ifndef LIGHTHANDLER_H
#define LIGHTHANDLER_H

#include "fbxSdk.h"
#include "BRFImporterStructs.h"

class LightHandler
{

private:
	BRFImporter::LightHeader lightTypeStruct;
	BRFImporter::PointLightHeader point;
	BRFImporter::DirLightHeader directional;
	BRFImporter::SpotLightHeader spot;
	BRFImporter::AmbLightHeader ambient;
	BRFImporter::AreaLightHeader area;

	void GetLightPos(FbxNode * pNode, double * lightPosition);

	void GetLightRotation(FbxNode * pNode, double * lightRotation);

	void GetLightScaling(FbxNode * pNode, double * lightScaling);


public:

	LightHandler();
	~LightHandler();

	void DisplayLight(FbxNode * pNode);

	void SpotLight(
		FbxLight* pLight,
		float* lightColor,
		double outerAngle,
		float intensity,
		unsigned int iD);

	void Directional(
		FbxLight* pLight,
		float* lightColor,
		float intensity,
		unsigned int iD);

	void PointLight(FbxLight* pLight,
		float* lightColor,
		float intensity,
		unsigned int iD);

	void AreaLight(
		FbxLight* pLight,
		float* lightColor,
		float intensity,
		unsigned int iD);

	void AmbientLight(
		FbxLight* pLight,
		float* lightColor,
		float intensity,
		unsigned int iD);

};
#endif // !GETLIGHT_H