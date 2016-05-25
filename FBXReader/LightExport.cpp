#include "LightExport.h"


using namespace BRFImporter;
LightExport::LightExport()
{
	spotLights = new std::vector<SpotLightHeader>;
	areaLights = new std::vector<AreaLightHeader>;
	pointLights = new std::vector<PointLightHeader>;
	dirLights = new std::vector<DirLightHeader>;
}


LightExport::~LightExport()
{
	delete spotLights;
	delete areaLights;
	delete pointLights;
	delete dirLights;
}

void LightExport::WriteToBinaryFile(std::ofstream * outfile)
{
	//STUBBY STUB STUB
	this->lightTypesCount.spotCount = spotLights->size();
	this->lightTypesCount.areaCount = areaLights->size();
	this->lightTypesCount.pointCount = pointLights->size();
	this->lightTypesCount.directionalCount = dirLights->size();

		std::cout << "Spotlights exported :" << spotLights->size() << "\n";
		std::cout << "areaLights exported :" << areaLights->size() << "\n";
		std::cout << "dirLights exported :" << dirLights->size() << "\n";
		std::cout << "pointLights exported :" << pointLights->size() << "\n";
		
	for (int i = 0; i < spotLights->size(); i++)
	{
		std::cout << std::endl;

		std::cout << "Spotlight nr: " << i << std::endl;

		std::cout << "ID: " << spotLights->at(i).objectID << std::endl;

		std::cout << "Pos X: " << spotLights->at(i).pos[0] <<
		" Pos Y: " << spotLights->at(i).pos[1] <<
		" Pos Z: " << spotLights->at(i).pos[2] << std::endl;

		std::cout << "Rot X: " << spotLights->at(i).rot[0] <<
		" Rot Y: " << spotLights->at(i).rot[1] <<
		" Rot Z: " << spotLights->at(i).rot[2] << std::endl;
		
		std::cout << "Color G: " << spotLights->at(i).color[0] <<
		" Color G: " << spotLights->at(i).color[1] <<
		" Color B: " << spotLights->at(i).color[2] << std::endl;

		std::cout << "Scale X: " << spotLights->at(i).scale[0] <<
		" Scale Y: " << spotLights->at(i).scale[1] <<
		" Scale Z: " << spotLights->at(i).scale[2] << std::endl;

		std::cout << "Intensity: " << spotLights->at(i).intensity << "\n";

		std::cout << "OuterAngle: " << spotLights->at(i).spotRadius << std::endl;

		//Continue here if you want more specific information
	}
	
	for (int i = 0; i < areaLights->size(); i++)
	{
		std::cout << std::endl;

		std::cout << "Arealight nr: " << i << std::endl;

		std::cout << "ID: " << areaLights->at(i).objectID << std::endl;

		std::cout << "Pos X: " << areaLights->at(i).pos[0] <<
			" Pos Y: " << areaLights->at(i).pos[1] <<
			" Pos Z: " << areaLights->at(i).pos[2] << std::endl;

		std::cout << "Rot X: " << areaLights->at(i).rot[0] <<
			" Rot Y: " << areaLights->at(i).rot[1] <<
			" Rot Z: " << areaLights->at(i).rot[2] << std::endl;

		std::cout << "Color R: " << areaLights->at(i).color[0] <<
			" Color G: " << areaLights->at(i).color[1] <<
			" Color B: " << areaLights->at(i).color[2] << std::endl;

		std::cout << "Scale X: " << areaLights->at(i).scale[0] <<
			" Scale Y: " << areaLights->at(i).scale[1] <<
			" SCale Z: " << areaLights->at(i).scale[2] << std::endl;

		std::cout << "Intensity: " << areaLights->at(i).intensity << "\n";
	}

	for (int i = 0; i < pointLights->size(); i++)
	{
		std::cout << std::endl;

		std::cout << "Pointlight: " << i << std::endl;

		std::cout << "ID: " << pointLights->at(i).objectID << std::endl;

		std::cout << "Pos X: " << pointLights->at(i).pos[0] <<
			" Pos Y: " << pointLights->at(i).pos[1] <<
			" Pos Z: " << pointLights->at(i).pos[2] << std::endl;

		std::cout << "Color R: " << pointLights->at(i).color[0] <<
			" Color G: " << pointLights->at(i).color[1] <<
			" Color B: " << pointLights->at(i).color[2] << std::endl;

		std::cout << "Intensity: " << pointLights->at(i).intensity << "\n";
	}

	for (int i = 0; i < dirLights->size(); i++)
	{
		std::cout << std::endl;

		std::cout << "Directional Lights nr: " << i << std::endl;

		std::cout << "ID: " << dirLights->at(i).objectID << std::endl;

		std::cout << "Pos X: " << dirLights->at(i).pos[0] <<
			" Pos Y: " << dirLights->at(i).pos[1] <<
			" Pos Z: " << dirLights->at(i).pos[2] << std::endl;

		std::cout << "Rot X: " << dirLights->at(i).rot[0] <<
			" Rot Y: " << dirLights->at(i).rot[1] <<
			" Rot Z: " << dirLights->at(i).rot[2] << std::endl;

		std::cout << "Color R: " << dirLights->at(i).color[0] <<
			" Color G: " << dirLights->at(i).color[1] <<
			" Color B: " << dirLights->at(i).color[2] << std::endl;

		std::cout << "Intensity: " << dirLights->at(i).intensity << "\n";
	}

	if (outfile->is_open())
	{
		outfile->write((const char*)&this->lightTypesCount, sizeof(LightHeader));

		//if (spotLights->size > 0) <- kolla om du ska skriva in detta överallt
		outfile->write((const char*)(this->spotLights->data()), sizeof(SpotLightHeader) * spotLights->size());
		outfile->write((const char*)(this->areaLights->data()), sizeof(AreaLightHeader) * areaLights->size());
		outfile->write((const char*)(this->pointLights->data()), sizeof(PointLightHeader) * areaLights->size());
		outfile->write((const char*)(this->dirLights->data()), sizeof(DirLightHeader) * dirLights->size());
	}
}

#pragma region Addfunctions
void LightExport::AddLightInfo(LightHeader info)
{
	this->lightTypesCount = info;
}

void LightExport::AddSpotLights(SpotLightHeader input)
{
	this->spotLights->push_back(input);
}

void LightExport::AddAreaLights(AreaLightHeader input)
{
	this->areaLights->push_back(input);
}

void LightExport::AddPointLights(PointLightHeader input)
{
	this->pointLights->push_back(input);
}

void LightExport::AddDirectionalLights(DirLightHeader input)
{
	this->dirLights->push_back(input);
}
#pragma endregion 