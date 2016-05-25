
#include "LightHandler.h"

LightHandler::LightHandler()
{

}

LightHandler::~LightHandler()
{

}

void LightHandler::GetLightData(FbxNode* pNode, LightExport* lights)
{
		//Recursively extract the children
		for (int j = 0; j < pNode->GetChildCount(); j++)
			GetLightData(pNode->GetChild(j), lights);

		if (pNode->GetLight())
	{
		if (lights == nullptr)
			lights = new LightExport;

		FbxLight* lLight = (FbxLight*)pNode->GetNodeAttribute();

		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << "Light Name: ";
		std::cout << pNode->GetName() << std::endl;

		std::cout << "Light Type: ";
		std::cout << lLight->LightType.Get() << std::endl;

		int num = lLight->LightType.Get();

		if (num == 0) //pointlight
		{
			PointLightHeader temp = PointLight(lLight);
			GetLightPos(pNode, temp.pos);



			
			lights->pointLights->push_back(temp);
		}
		if (num == 1) //directional light
		{
			DirLightHeader temp;
			temp = Directional(lLight);

			std::cout << "Directional:" << std::endl;
			GetLightPos(pNode, temp.pos);
			GetLightRotation(pNode, temp.rot);

			lights->dirLights->push_back(temp);

		}
		if (num == 2) //spotlight
		{
			SpotLightHeader temp;
			temp = SpotLight(lLight);
			GetLightPos(pNode, temp.pos);
			GetLightRotation(pNode, temp.rot);
			GetLightScaling(pNode, temp.scale);

			lights->spotLights->push_back( temp );
		}
	
		if (num == 3) //arealight
		{
			AreaLightHeader temp;

			temp = AreaLight(lLight);
			std::cout << "Arealight: " << std::endl;
			GetLightPos(pNode, temp.pos);
			GetLightRotation(pNode, temp.rot);
			GetLightScaling(pNode, temp.scale);

			lights->areaLights->push_back( temp );

		}

	}
}

void LightHandler::GetLightPos(FbxNode* pNode, double* lightPosition)
{
	FbxDouble3 Position = pNode->LclTranslation.Get();

	std::cout << "Position: ";
	lightPosition[0] = (double)Position[0];
	std::cout << "x: " << lightPosition[0] << " ";

	lightPosition[1] = (double)Position[1];
	std::cout << "y: " << lightPosition[1] << " ";

	lightPosition[2] = (double)Position[2];
	std::cout << "z: " << lightPosition[2] << " " << std::endl;
}

void LightHandler::GetLightRotation(FbxNode* pNode, double* lightRotation)
{
	FbxDouble3 Rotation = pNode->LclRotation.Get();

	std::cout << "Rotation: ";
	lightRotation[0] = (double)Rotation[0];
	std::cout << "x: " << lightRotation[0] << " ";

	lightRotation[1] = (double)Rotation[1];
	std::cout << "y: " << lightRotation[1] << " ";

	lightRotation[2] = (double)Rotation[2];
	std::cout << "z: " << lightRotation[2] << " " << std::endl;;
}

void LightHandler::GetLightScaling(FbxNode* pNode, double* lightScaling)
{
	FbxDouble3 Scaling = pNode->LclScaling.Get();

	std::cout << "Scale: ";
	lightScaling[0] = (double)Scaling[0];
	std::cout << "x: " << lightScaling[0] << " ";

	lightScaling[1] = (double)Scaling[1];
	std::cout << "y: " << lightScaling[1] << " ";

	lightScaling[2] = (double)Scaling[2];
	std::cout << "z: " << lightScaling[2] << " " << std::endl;
}

#pragma region LightValues
BRFImporter::SpotLightHeader LightHandler::SpotLight(FbxLight* pLight)
{
	SpotLightHeader temp;
	std::cout << "Spotlight Values: " << std::endl;

	unsigned int ID = pLight->GetUniqueID();
	//iD = ID;
	std::cout << "Spotlight ID:";
	std::cout << ID;
	temp.objectID = ID;
	std::cout << std::endl;


	FbxDouble3 lColor = pLight->Color.Get();
	temp.color[0] = (double)lColor[0];
	std::cout << "Color R: ";
	std::cout << temp.color[0] << " ";
	temp.color[1] = (double)lColor[1];
	std::cout << "Color G: ", lColor;
	std::cout << temp.color[1] << " ";
	temp.color[2] = (double)lColor[2];
	std::cout << "Color B: ", lColor;
	std::cout << temp.color[2] << " ";
	std::cout << std::endl;


	double lightIntensity = pLight->Intensity.Get();
	temp.intensity = lightIntensity;
	std::cout << "Intensity: ";
	std::cout << lightIntensity;
	std::cout << std::endl;


	double outerangle = pLight->OuterAngle.Get();
	temp.spotRadius = outerangle;
	std::cout << "Outer Angle: ";
	std::cout << outerangle;
	std::cout << std::endl;



	return temp;
}

BRFImporter::AreaLightHeader LightHandler::AreaLight(FbxLight* pLight)
{
	AreaLightHeader temp;
	std::cout << "Area Values: " << std::endl;

	unsigned int ID = pLight->GetUniqueID();
	//iD = ID;
	std::cout << "Area ID: ";
	std::cout << ID;
	temp.objectID = ID;
	std::cout << std::endl;


	FbxDouble3 lColor = pLight->Color.Get();
	temp.color[0] = (double)lColor[0];
	std::cout << "Color R: ";
	std::cout << temp.color[0] << " ";
	temp.color[1] = (double)lColor[1];
	std::cout << "Color G: ", lColor;
	std::cout << temp.color[1] << " ";
	temp.color[2] = (double)lColor[2];
	std::cout << "Color B: ", lColor;
	std::cout << temp.color[2] << " ";
	std::cout << std::endl;


	double lightIntensity = pLight->Intensity.Get();
	temp.intensity = lightIntensity;
	std::cout << "Intensity: ";
	std::cout << lightIntensity;
	std::cout << std::endl;

	return temp;
}

BRFImporter::PointLightHeader LightHandler::PointLight(FbxLight* pLight)
{
	PointLightHeader temp;
	std::cout << "Point Values: " << std::endl;

	unsigned int ID = pLight->GetUniqueID();
	//iD = ID;
	std::cout << "Point ID :";
	std::cout << ID;
	temp.objectID = ID;
	std::cout << std::endl;


	FbxDouble3 lColor = pLight->Color.Get();
	temp.color[0] = (double)lColor[0];
	std::cout << "Color R: ";
	std::cout << temp.color[0] << " ";
	temp.color[1] = (double)lColor[1];
	std::cout << "Color G: ", lColor;
	std::cout << temp.color[1] << " ";
	temp.color[2] = (double)lColor[2];
	std::cout << "Color B: ", lColor;
	std::cout << temp.color[2] << " ";
	std::cout << std::endl;


	double lightIntensity = pLight->Intensity.Get();
	temp.intensity = lightIntensity;
	std::cout << "Intensity: ";
	std::cout << lightIntensity;
	std::cout << std::endl;



	return temp;
}

BRFImporter::DirLightHeader LightHandler::Directional(FbxLight* pLight)
{
	DirLightHeader temp;
	std::cout << "Directional Values: " << std::endl;

	unsigned int ID = pLight->GetUniqueID();
	//iD = ID;
	std::cout << "Directional ID:";
	temp.objectID = ID;
	std::cout << ID;
	std::cout << std::endl;

	FbxDouble3 lColor = pLight->Color.Get();
	temp.color[0] = (double)lColor[0];
	std::cout << "Color R: ";
	std::cout << temp.color[0] << " ";
	temp.color[1] = (double)lColor[1];
	std::cout << "Color G: ", lColor;
	std::cout << temp.color[1] << " ";
	temp.color[2] = (double)lColor[2];
	std::cout << "Color B: ", lColor;
	std::cout << temp.color[2] << " ";
	std::cout << std::endl;

	double lightIntensity = pLight->Intensity.Get();
	temp.intensity = lightIntensity;
	std::cout << "Intensity: ";
	std::cout << lightIntensity << std::endl;

	return temp;

}

#pragma endregion
