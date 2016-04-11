#pragma once
#include <fstream>
class AttributesExport
{
public:
	AttributesExport();
	~AttributesExport();
	void WriteToBinaryFile(std::ofstream* outfile);
};

