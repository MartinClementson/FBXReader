#include "MorphHandler.h"

#pragma region Init & Destruct

MorphHandler::MorphHandler()
{

}

MorphHandler::~MorphHandler()
{

}

#pragma endregion

void MorphHandler::GetMorphData(FbxNode* pNode)
{

	FbxGeometry* pGeo = pNode->GetGeometry();
	int morphAnimCount = pGeo->GetDeformerCount(FbxDeformer::eBlendShape);
	int morphChannelCount;
	int targetShapeCount;

	std::cout << "blendCount!!!!! " << morphAnimCount << "\n\n\n\n";
	FbxBlendShape* morphAnim;
	morphAnim = (FbxBlendShape*)pGeo->GetDeformer(0, FbxDeformer::eBlendShape);

	morphChannelCount = morphAnim->GetBlendShapeChannelCount();

	std::cout << "ChannelCount!!!!! " << morphChannelCount << "\n\n\n\n";
	FbxBlendShapeChannel* morphChannel;
	morphChannel = morphAnim->GetBlendShapeChannel(0);

	std::cout << "ChannelName!!!!! " << morphChannel->GetName() << "\n\n\n\n";

	targetShapeCount = morphChannel->GetTargetShapeCount();

	std::cout << "Target Shape Count!!!!! " << targetShapeCount << "\n\n\n\n";

	FbxShape* shape;
	shape = morphChannel->GetTargetShape(0);

	std::cout << "Shape name!!!!! " << shape->GetName() << "\n\n\n\n";


	int vertexCount = shape->GetControlPointsCount();
	FbxVector4* vertices = shape->GetControlPoints();

	

	for (int i = 0; i < vertexCount; i++)
	{
		std::cout<<"what? "<< (double*)shape->GetControlPointAt(i) << "\n\n";
	}
}

void MorphHandler::ProcessData(FbxGeometry* pGeo)
{

}