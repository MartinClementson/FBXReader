#include "MaterialExport.h"

using namespace BRFImporter;
MaterialExport::MaterialExport()
{

	

}


MaterialExport::~MaterialExport()
{
	

	if (this->matAttributes != nullptr)
		delete matAttributes;
}

void MaterialExport::WriteToBinaryFile(std::ofstream * outfile)
{

	std::cout << "Mesh name  : " << this->matInfo.matName << std::endl;
	std::cout << "Diffuse Map Name: " << this->matInfo.diffMap << std::endl;
	std::cout << "Diffuse Value: "<< this->matInfo.diffuseVal << std::endl;
	std::cout << "Glow Map Name: " << this->matInfo.glowMap << std::endl;
	std::cout << "ID: " << this->matInfo.Id << std::endl;
	std::cout << "Normal Map Name: " << this->matInfo.normalMap << std::endl;
	std::cout << "Specular Map Name: " << this->matInfo.specMap << std::endl;
	std::cout << "Specular Value: " <<this->matInfo.specularVal << std::endl;
}