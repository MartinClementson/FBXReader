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
	std::cout << "Diffuse Value: R: "<< this->matInfo.diffuseVal[0] << "G: "<< this->matInfo.diffuseVal[1] << "B: " << this->matInfo.diffuseVal[2] << std::endl;
	std::cout << "Glow Map Name: " << this->matInfo.glowMap << std::endl;
	std::cout << "ID: " << this->matInfo.Id << std::endl;
	std::cout << "Normal Map Name: " << this->matInfo.normalMap << std::endl;
	std::cout << "Specular Map Name: " << this->matInfo.specMap << std::endl;
	std::cout << "Specular ValueR: " << this->matInfo.specularVal[0] << "G: " << this->matInfo.specularVal[1] << "B: " << this->matInfo.specularVal[2] << std::endl;
}

AttributesExport * MaterialExport::GetAttributeHandler()
{

	if (this->matAttributes == nullptr)
	{
		matAttributes = new AttributesExport;
	}

	return matAttributes;
}
