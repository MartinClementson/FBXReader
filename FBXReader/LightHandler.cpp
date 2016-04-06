
#include "LightHandler.h"

LightHandler::LightHandler()
{

}

LightHandler::~LightHandler()
{

}

void LightHandler::DisplayLight(FbxNode* pNode, double* position)
{
	if (pNode->GetLight())
	{
		std::cout << "Light Data :" << std::endl;
		FbxLight* lLight = (FbxLight*)pNode->GetNodeAttribute();

		std::cout << "Light Name: ", (char *)pNode->GetName();

		char* lLightTypes[] = { "Point","Directional","Spot" };

		std::cout << "Light Type: ", lLightTypes[lLight->LightType.Get()];

		if ((char*)lLight->LightType.Get() == "Point")
		{
			GetLightPos(pNode, spot.pos);
			GetLightRotation(pNode, spot.rot);
			GetLightScaling(pNode, spot.scale);
			PointLight(lLight);
		}
		if ((char*)lLight->LightType.Get() == "Directional")
		{
			GetLightPos(pNode, spot.pos);
			GetLightRotation(pNode, spot.rot);
			GetLightScaling(pNode, spot.scale);
			Directional(lLight);
		}
		if ((char*)lLight->LightType.Get() == "Spot")
		{
			GetLightPos(pNode, point.pos);
			GetLightRotation(pNode, point.rot);
			GetLightScaling(pNode, point.scale);
			SpotLight(lLight);
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

void LightHandler::SpotLight(FbxLight* pLight)
{
	std::cout << "Spotlight Values: " << std::endl;
	FbxDouble3 c = pLight->Color.Get();
	FbxColor lColor(c[0], c[1], c[2]);
	std::cout << "Color: ", lColor;
	std::cout << "Intensity: ", pLight->Intensity.Get();
	std::cout << "Outer Angle: ", pLight->OuterAngle.Get();
	std::cout << "Fog: ", pLight->Fog.Get();

	lightTypeStruct.spotCount++;
}

void LightHandler::Directional(FbxLight* pLight)
{
	std::cout << "Directional Values: " << std::endl;
	std::cout << "Directional ID:", pLight->GetClassId();

	FbxDouble3 c = pLight->Color.Get();	
	FbxColor lColor(c[0], c[1], c[2]);
	std::cout << "Color: ", lColor;
	std::cout << "Intensity: ", pLight->Intensity.Get();

	lightTypeStruct.directionalCount;

}

void LightHandler::PointLight(FbxLight* pLight)
{
	std::cout << "PointLight Values: " << std::endl;
	FbxDouble3 c = pLight->Color.Get();
	FbxColor lColor(c[0], c[1], c[2]);
	std::cout << "Color: ", lColor;
	std::cout << "Intensity: ", pLight->Intensity.Get();

	lightTypeStruct.pointCount++;
}
