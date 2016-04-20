#include "MaterialExport.h"

using namespace BRFImporter;
MaterialExport::MaterialExport()
{
	materials = new std::vector<MaterialHeader>;
}

MaterialExport::~MaterialExport()
{
	
	delete materials;

}

void MaterialExport::WriteToBinaryFile(std::ofstream * outfile)
{
	this->main.materialAmount = materials->size();

	for (int i = 0; i < materials->size(); i++)
	{
		std::cout << "Material name  : " << this->materials->at(i).matName << std::endl;
		std::cout << "Diffuse Map Name: " << this->materials->at(i).diffMap << std::endl;
		std::cout << "Diffuse Value: R: "<< this->materials->at(i).diffuseVal[0] << " G: "<< this->materials->at(0).diffuseVal[1] << " B: " << this->materials->at(0).diffuseVal[2] << std::endl;
		std::cout << "Glow Map Name: " << this->materials->at(i).glowMap << std::endl;
		std::cout << "ID: " << this->materials->at(i).Id << std::endl;
		std::cout << "Normal Map Name: " << this->materials->at(i).normalMap << std::endl;
		std::cout << "Specular Map Name: " << this->materials->at(i).specMap << std::endl;
		std::cout << "Specular Value R: " << this->materials->at(i).specularVal[0] << " G: " << this->materials->at(0).specularVal[1] << " B: " << this->materials->at(0).specularVal[2] << std::endl;
		std::cout << "\n\n\n";

	}
	if (outfile->is_open())
	{
		outfile->write((const char*)(this->materials->data()), sizeof(MaterialHeader) * materials->size());
	}
}


