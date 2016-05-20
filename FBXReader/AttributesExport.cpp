#include "AttributesExport.h"



AttributesExport::AttributesExport()
{
	vectorAttributes = new std::vector<VectorAttrHeader>;
	stringAttributes = new std::vector<StringAttrHeader>;
	floatAttributes = new std::vector<FloatAttrHeader>;
	boolAttributes = new std::vector<BoolAttrHeader>;
	intAttributes = new std::vector<IntAttrHeader>;

}


AttributesExport::~AttributesExport()
{
	delete vectorAttributes;
	delete stringAttributes;
	delete floatAttributes;
	delete boolAttributes;
	delete intAttributes;

}

void AttributesExport::WriteToBinaryFile(std::ofstream * outfile)
{

	this->attrInfo.boolAmount = boolAttributes->size();
	this->attrInfo.floatAmount = floatAttributes->size();
	this->attrInfo.stringAmount = stringAttributes->size();
	this->attrInfo.intAmount = intAttributes->size();
	this->attrInfo.vectorAmount = vectorAttributes->size();

			for (int i = 0; i < vectorAttributes->size(); i++)
			{
				std::cout << "VectorName:" << this->vectorAttributes->at(i).attrName << std::endl;
				std::cout << "Value     :" << this->vectorAttributes->at(i).value << std::endl;
			}
			for (int i = 0; i < intAttributes->size(); i++)
			{
				std::cout << "IntName:" << this->intAttributes->at(i).attrName << std::endl;
				std::cout << "Min    :" << this->intAttributes->at(i).min << std::endl;
				std::cout << "max    :" << this->intAttributes->at(i).max << std::endl;
				std::cout << "Value  :" << this->intAttributes->at(i).value << std::endl;
			}
			for (int i = 0; i < stringAttributes->size(); i++)
			{
				std::cout << "StringName: " << this->stringAttributes->at(i).attrName << std::endl;
				std::cout << "Value     :" << this->stringAttributes->at(i).value << std::endl;
			}

			for (int i = 0; i < boolAttributes->size(); i++)
			{
				std::cout << "BoolName :" << this->boolAttributes->at(i).attrName << std::endl;
				std::cout << "Value    :" << this->boolAttributes->at(i).value << std::endl;

			}
			for (int i = 0; i < floatAttributes->size(); i++)
			{
				std::cout << "floatName: " << this->floatAttributes->at(i).attrName << std::endl;
				std::cout << "Max      : " << this->floatAttributes->at(i).max << std::endl;
				std::cout << "Min      : " << this->floatAttributes->at(i).min << std::endl;
				std::cout << "Value    : " << this->floatAttributes->at(i).value << std::endl;
			}
			

	


}
