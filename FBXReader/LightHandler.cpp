
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
		std::cout << "Light Data :" << std::endl;
		FbxLight* lLight = (FbxLight*)pNode->GetNodeAttribute();

		std::cout << "Light Name: ";
		std::cout << pNode->GetName();

		char* lLightTypes[] = { "Point","Directional","Spot", "Ambient", "Area" };

		std::cout << "Light Type: ", lLightTypes[lLight->LightType.Get()];

		if ((char*)lLight->LightType.Get() == "Point")
		{
			GetLightPos(pNode, point.pos);

			PointLight(lLight, point.color, point.intensity, point.objectID);
		}
		if ((char*)lLight->LightType.Get() == "Directional")
		{
			GetLightPos(pNode, directional.pos);
			GetLightRotation(pNode, directional.rot);

			Directional(lLight, directional.color, directional.intensity, directional.objectID);
		}
		if ((char*)lLight->LightType.Get() == "Spot")
		{
			GetLightPos(pNode, spot.pos);
			GetLightRotation(pNode, spot.rot);
			GetLightScaling(pNode, spot.scale);

			SpotLight(lLight, spot.color, spot.outerAngle, spot.intensity, spot.objectID);
		}
		if ((char*)lLight->LightType.Get() == "Ambient")
		{
			GetLightPos(pNode, ambient.pos);

			AmbientLight(lLight, ambient.color, ambient.intensity, ambient.objectID);
		}
		if ((char*)lLight->LightType.Get() == "Area")
		{
			GetLightPos(pNode, area.pos);
			GetLightRotation(pNode, area.rot);
			GetLightScaling(pNode, area.scale);

			AreaLight(lLight, area.color,area.intensity, area.objectID);
		}

	}
}

void LightHandler::GetLightPos(FbxNode* pNode, double* lightPosition)
{
	FbxDouble3 Position = pNode->LclTranslation.Get();

	lightPosition[0] = (double)Position[0];
	std::cout << "x: " << lightPosition[0] << " ";

	lightPosition[1] = (double)Position[1];
	std::cout << "y: " << lightPosition[1] << " ";

	lightPosition[2] = (double)Position[2];
	std::cout << "z: " << lightPosition[2] << " ";
}

void LightHandler::GetLightRotation(FbxNode* pNode, double* lightRotation)
{
	FbxDouble3 Rotation = pNode->LclRotation.Get();

	lightRotation[0] = (double)Rotation[0];
	std::cout << "x: " << lightRotation[0] << " ";

	lightRotation[1] = (double)Rotation[1];
	std::cout << "y: " << lightRotation[1] << " ";

	lightRotation[2] = (double)Rotation[2];
	std::cout << "z: " << lightRotation[2] << " ";
}

void LightHandler::GetLightScaling(FbxNode* pNode, double* lightScaling)
{
	FbxDouble3 Scaling = pNode->LclScaling.Get();

	lightScaling[0] = (double)Scaling[0];
	std::cout << "x: " << lightScaling[0] << " ";

	lightScaling[1] = (double)Scaling[1];
	std::cout << "y: " << lightScaling[1] << " ";

	lightScaling[2] = (double)Scaling[2];
	std::cout << "z: " << lightScaling[2] << " ";
}

#pragma region LightValues
void LightHandler::SpotLight(
	FbxLight* pLight,
	float* lightColor,
	double outerAngle,
	float intensity,
	unsigned int iD)
{
	std::cout << "Spotlight Values: " << std::endl;

	unsigned int ID = pLight->GetUniqueID();
	iD = ID;
	std::cout << "Spotlight ID:", ID;

	FbxDouble3 lColor = pLight->Color.Get();
	lightColor[0] = (double)lColor[0];
	std::cout << "Color R: ", lColor;
	lightColor[1] = (double)lColor[1];
	std::cout << "Color G: ", lColor;
	lightColor[2] = (double)lColor[2];
	std::cout << "Color B: ", lColor;

	float lightIntensity = pLight->Intensity.Get();
	intensity = lightIntensity;
	std::cout << "Intensity: ", lightIntensity;

	double outerangle = pLight->OuterAngle.Get();
	outerAngle = outerangle;
	std::cout << "Outer Angle: ", outerangle;

	lightTypeStruct.spotCount++;
}

void LightHandler::Directional(
	FbxLight* pLight,
	float* lightColor,
	float intensity,
	unsigned int iD)
{
	std::cout << "Directional Values: " << std::endl;

	unsigned int ID = pLight->GetUniqueID();
	iD = ID;
	std::cout << "Directional ID:", ID;

	FbxDouble3 lColor = pLight->Color.Get();
	lightColor[0] = (double)lColor[0];
	std::cout << "Color R: ", lColor;
	lightColor[1] = (double)lColor[1];
	std::cout << "Color G: ", lColor;
	lightColor[2] = (double)lColor[2];
	std::cout << "Color B: ", lColor;

	float lightIntensity = pLight->Intensity.Get();
	intensity = lightIntensity;
	std::cout << "Intensity: ", lightIntensity;

	lightTypeStruct.directionalCount;

}

void LightHandler::PointLight(
	FbxLight* pLight,
	float* lightColor,
	float intensity,
	unsigned int iD)
{
	std::cout << "Point Values: " << std::endl;

	unsigned int ID = pLight->GetUniqueID();
	iD = ID;
	std::cout << "Point ID:", ID;

	FbxDouble3 lColor = pLight->Color.Get();
	lightColor[0] = (double)lColor[0];
	std::cout << "Color R: ", lColor;
	lightColor[1] = (double)lColor[1];
	std::cout << "Color G: ", lColor;
	lightColor[2] = (double)lColor[2];
	std::cout << "Color B: ", lColor;

	float lightIntensity = pLight->Intensity.Get();
	intensity = lightIntensity;
	std::cout << "Intensity: ", lightIntensity;

	lightTypeStruct.pointCount++;
}

void LightHandler::AreaLight(
	FbxLight* pLight,
	float* lightColor,
	float intensity,
	unsigned int iD)
{
	std::cout << "Area Values: " << std::endl;

	unsigned int ID = pLight->GetUniqueID();
	iD = ID;
	std::cout << "Area ID:", ID;

	FbxDouble3 lColor = pLight->Color.Get();
	lightColor[0] = (double)lColor[0];
	std::cout << "Color R: ", lColor;
	lightColor[1] = (double)lColor[1];
	std::cout << "Color G: ", lColor;
	lightColor[2] = (double)lColor[2];
	std::cout << "Color B: ", lColor;

	float lightIntensity = pLight->Intensity.Get();
	intensity = lightIntensity;
	std::cout << "Intensity: ", lightIntensity;

	lightTypeStruct.areaCount++;
}

void LightHandler::AmbientLight(
	FbxLight* pLight,
	float* lightColor,
	float intensity,
	unsigned int iD)
{
	std::cout << "Ambient Values: " << std::endl;

	unsigned int ID = pLight->GetUniqueID();
	iD = ID;
	std::cout << "Ambient ID:", ID;

	FbxDouble3 lColor = pLight->Color.Get();
	lightColor[0] = (double)lColor[0];
	std::cout << "Color R: ", lColor;
	lightColor[1] = (double)lColor[1];
	std::cout << "Color G: ", lColor;
	lightColor[2] = (double)lColor[2];
	std::cout << "Color B: ", lColor;

	float lightIntensity = pLight->Intensity.Get();
	intensity = lightIntensity;
	std::cout << "Intensity: ", lightIntensity;

	lightTypeStruct.ambientCount++;
}
#pragma endregion
