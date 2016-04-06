
#include "LightHandler.h"

LightHandler::LightHandler()
{

}

LightHandler::~LightHandler()
{

}

void LightHandler::DisplayLight(FbxNode* pNode)
{
	if (pNode->GetLight())
	{
		cout << "Light Data :" << endl;
		FbxLight* lLight = (FbxLight*)pNode->GetNodeAttribute();

		cout << "Light Name: ", (char *)pNode->GetName();

		char* lLightTypes[] = { "Point", "Directional", "Spot" };

		cout << "Light Type: ", lLightTypes[lLight->LightType.Get()];

		if ((char*)lLight->LightType.Get() == "Point")
		{
			PointLight(lLight);
		}
		if ((char*)lLight->LightType.Get() == "Directional")
		{
			Directional(lLight);
		}
		if ((char*)lLight->LightType.Get() == "Spot")
		{
			SpotLight(lLight);
		}
	}
}

void LightHandler::SpotLight(FbxLight* pLight)
{
	cout << "Spotlight Values: " << endl;
	FbxDouble3 c = pLight->Color.Get();
	FbxColor lColor(c[0], c[1], c[2]);
	cout << "Color: ", lColor;
	cout << "Intensity: ", pLight->Intensity.Get();
	cout << "Outer Angle: ", pLight->OuterAngle.Get();
	cout << "Fog: ", pLight->Fog.Get();

	lightTypeStruct.spotCount++;
}

void LightHandler::Directional(FbxLight* pLight)
{
	cout << "Spotlight Values: " << endl;
	FbxDouble3 c = pLight->Color.Get();
	FbxColor lColor(c[0], c[1], c[2]);
	cout << "Color: ", lColor;
	cout << "Intensity: ", pLight->Intensity.Get();
	cout << "Outer Angle: ", pLight->OuterAngle.Get();
	cout << "Fog: ", pLight->Fog.Get();

	lightTypeStruct.directionalCount;

}

void LightHandler::PointLight(FbxLight* pLight)
{
	cout << "Spotlight Values: " << endl;
	FbxDouble3 c = pLight->Color.Get();
	FbxColor lColor(c[0], c[1], c[2]);
	cout << "Color: ", lColor;
	cout << "Intensity: ", pLight->Intensity.Get();
	cout << "Outer Angle: ", pLight->OuterAngle.Get();
	cout << "Fog: ", pLight->Fog.Get();

	lightTypeStruct.pointCount++;
}

