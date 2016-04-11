#include "LightExport.h"



LightExport::LightExport()
{

	spotLights = new std::vector<SpotLightHeader>;
	ambLights = new std::vector<AmbLightHeader>;
	areaLights = new std::vector<AreaLightHeader>;
	pointLights = new std::vector<PointLightHeader>;
	dirLights = new std::vector<DirLightHeader>;
}


LightExport::~LightExport()
{

	delete spotLights;
	delete ambLights;
	delete areaLights;
	delete pointLights;
	delete dirLights;
}

void LightExport::WriteToBinaryFile(std::ofstream * outfile)
{
	//STUBBY STUB STUB
	this->lightTypesCount.spotCount = spotLights->size();
	this->lightTypesCount.ambientCount = ambLights->size();
	this->lightTypesCount.areaCount = areaLights->size();
	this->lightTypesCount.directionalCount = dirLights->size();
	this->lightTypesCount.pointCount = pointLights->size();

		std::cout << "Spotlights exported :" << spotLights->size() << "\n";
		std::cout << "ambLights exported :" << ambLights->size() << "\n";
		std::cout << "areaLights exported :" << areaLights->size() << "\n";
		std::cout << "dirLights exported :" << dirLights->size() << "\n";
		std::cout << "pointLights exported :" << pointLights->size() << "\n";
	for (int i = 0; i < spotLights->size(); i++)
	{
		//std::cout << "intensity:" << spotLights->at(i).intensity << "\n";
		//Continue here if you want more specific information
	}

}
