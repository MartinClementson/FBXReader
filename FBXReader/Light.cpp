#include "LightHandler.h"

void LightHandler::DisplayLight(FbxNode* pNode)
{
	FbxLight* lLight = (FbxLight*)pNode->GetNodeAttribute();

	cout << "Light Name: ", (char *)pNode->GetName();

	//char* lLightTypes[] = { "Point", "Spot", "Directional" };

	//cout << "Light Type: ", lLightTypes[lLight->LightType.Get()];

	//cout << " Cast Light: ", lLight->CastLight.Get();

	//if (!(lLight->FileName.Get().IsEmpty()))
	//{
	//	cout << "    Filename:", lLight->FileName.Get().Buffer(), "";
	//	cout << "    Ground projection" ; 
	//}
}

void LightHandler::DisplayDefaultValues(FbxLight* pLight)
{
	cout << " Animation values: ";

	FbxDouble3 c = pLight->Color.Get();
	FbxColor lColor(c[0], c[1], c[2]);
	cout << "       Color: ", lColor;
	cout << "       Default intensity: ", pLight->Intensity.Get();
	cout << "       Default outer angle: ", pLight->OuterAngle.Get();
	cout << "       Default fog: ", pLight->Fog.Get();

}