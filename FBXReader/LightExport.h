#pragma once
#include "BRFImporterStructs.h"
#include <vector>
#include <iostream>
using namespace BRFImporter;

class LightExport
{
private:
	LightHeader lightTypesCount;
public:
	std::vector<SpotLightHeader>* spotLights;
	std::vector<AmbLightHeader>* ambLights;
	std::vector<AreaLightHeader>* areaLights;
	std::vector<PointLightHeader>* pointLights;
	std::vector<DirLightHeader>* dirLights;


	LightExport();
	~LightExport();

	void WriteToBinaryFile(std::ofstream* outfile);
};

