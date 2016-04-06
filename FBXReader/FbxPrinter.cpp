#include "FbxPrinter.h"



FbxPrinter::FbxPrinter()
{
}


FbxPrinter::~FbxPrinter()
{
}

void FbxPrinter::PrintNode(FbxNode * pNode)
{
	PrintTabs();

	const char* nodeName = pNode->GetName();
	FbxDouble3 translation = pNode->LclTranslation.Get();
	FbxDouble3 rotation = pNode->LclRotation.Get();
	FbxDouble3 scaling = pNode->LclScaling.Get();

	//print the contents


	std::cout << "Node name  : " << nodeName << std::endl;
	PrintTabs();
	std::cout << "Translation: (" << translation[0] << "," << translation[1] << "," << translation[2] << ")" << std::endl;
	PrintTabs();
	std::cout << "Rotation   : (" << rotation[0] << "," << rotation[1] << "," << rotation[2] << ")" << std::endl;
	PrintTabs();
	std::cout << "Scale      : (" << scaling[0] << "," << scaling[1] << "," << scaling[2] << ")\n" << std::endl;

	numTabs++;

	//print the attributes of the node

	for (int i = 0; i < pNode->GetNodeAttributeCount(); i++)
		PrintCustom(pNode->GetNodeAttributeByIndex(i));


	//Recursively print the children
	for (int j = 0; j < pNode->GetChildCount(); j++)
		PrintNode(pNode->GetChild(j));


	numTabs--;
	PrintTabs();

	std::cout << "</node>\n" << std::endl;

	//"Child Count: " << pNode->GetChildCount()<<std::endl;
}

FbxString FbxPrinter::GetAttributeTypeName(FbxNodeAttribute::EType type)
{
	switch (type)
	{
	case FbxNodeAttribute::eUnknown: return "unidentified";
	case FbxNodeAttribute::eNull: return "null";
	case FbxNodeAttribute::eMarker: return "marker";
	case FbxNodeAttribute::eSkeleton: return "skeleton";
	case FbxNodeAttribute::eMesh: return "mesh";
	case FbxNodeAttribute::eNurbs: return "nurbs";
	case FbxNodeAttribute::ePatch: return "patch";
	case FbxNodeAttribute::eCamera: return "camera";
	case FbxNodeAttribute::eCameraStereo: return "stereo";
	case FbxNodeAttribute::eCameraSwitcher: return "camera switcher";
	case FbxNodeAttribute::eLight: return "light";
	case FbxNodeAttribute::eOpticalReference: return "optical reference";
	case FbxNodeAttribute::eOpticalMarker: return "marker";
	case FbxNodeAttribute::eNurbsCurve: return "nurbs curve";
	case FbxNodeAttribute::eTrimNurbsSurface: return "trim nurbs surface";
	case FbxNodeAttribute::eBoundary: return "boundary";
	case FbxNodeAttribute::eNurbsSurface: return "nurbs surface";
	case FbxNodeAttribute::eShape: return "shape";
	case FbxNodeAttribute::eLODGroup: return "lodgroup";
	case FbxNodeAttribute::eSubDiv: return "subdiv";
	default: return "unknown";


	}
}

void FbxPrinter::PrintCustom(FbxNodeAttribute * pAttribute)
{
	if (!pAttribute) return;

	FbxProperty prop;
	prop = pAttribute->GetFirstProperty();
	while (prop != NULL)
	{
		std::cout << "\n" << prop.GetName();
		prop = pAttribute->GetNextProperty(prop);
	}

	FbxString attrName = pAttribute->GetName();
	// Note: to retrieve the character array of a FbxString, use its Buffer() method.


	std::cout << "Name: " << attrName.Buffer() << std::endl;
}

void FbxPrinter::PrintAttribute(FbxNodeAttribute * pAttribute)
{
	if (!pAttribute) return;
	FbxString typeName = GetAttributeTypeName(pAttribute->GetAttributeType());

	FbxString attrName = pAttribute->GetName();
	PrintTabs();
	// Note: to retrieve the character array of a FbxString, use its Buffer() method.

	std::cout << "Attribute Type: " << typeName.Buffer() << std::endl;
	PrintTabs();
	std::cout << "Name: " << attrName.Buffer() << std::endl;
}

void FbxPrinter::PrintTabs()
{
	for (int i = 0; i < numTabs; i++)
		printf("\t");
}
