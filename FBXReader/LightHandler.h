#pragma once

#ifndef LIGHTHANDLER_H
#define LIGHTHANDLER_H

#include "fbxSdk.h"
#include "BRFImporterStructs.h"

using namespace std;

class LightHandler
{

private:
	BRFImporter::LightHeader lightTypeStruct;

public:

	LightHandler();
	~LightHandler();

	void DisplayLight(FbxNode * pNode);

	void DisplayDefaultValues(FbxLight * pLight);

};
#endif // !GETLIGHT_H