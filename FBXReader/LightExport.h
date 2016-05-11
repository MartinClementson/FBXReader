#pragma once
#include "BRFImporterStructs.h"
#include <vector>
#include <iostream>
#include <fstream>

using namespace BRFImporter;

class LightExport
{
private:
	LightHeader lightTypesCount;
public:
	std::vector<SpotLightHeader>* spotLights;
	std::vector<AreaLightHeader>* areaLights;
	std::vector<PointLightHeader>* pointLights;
	std::vector<DirLightHeader>* dirLights;


	LightExport();
	~LightExport();

	void WriteToBinaryFile(std::ofstream* outfile);
	void AddLightInfo(LightHeader info);
	void AddSpotLights(SpotLightHeader input);
	void AddAreaLights(AreaLightHeader input);
	void AddPointLights(PointLightHeader input);
	void AddDirectionalLights(DirLightHeader input);
};

