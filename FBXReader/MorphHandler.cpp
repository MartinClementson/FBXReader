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
	if (morphAnimCount > 0)
	{
		for (unsigned int i = 0; i < morphAnimCount; i++)
		{
			FbxBlendShape* morphAnim;
			morphAnim = (FbxBlendShape*)pGeo->GetDeformer(i, FbxDeformer::eBlendShape);

			morphChannelCount = morphAnim->GetBlendShapeChannelCount();
			std::cout << "ChannelCount!!!!! " << morphChannelCount << "\n\n\n\n";

			for (unsigned int j = 0; j < morphChannelCount; j++)
			{
				std::cout << "channel nr: " << j << "\n";

				FbxBlendShapeChannel* morphChannel;
				morphChannel = morphAnim->GetBlendShapeChannel(j);

				std::cout << "ChannelName!!!!! " << morphChannel->GetName() << "\n\n\n\n";

				targetShapeCount = morphChannel->GetTargetShapeCount();

				std::cout << "Target Shape Count!!!!! " << targetShapeCount << "\n\n\n\n";
				for (unsigned int k = 0; k < targetShapeCount; k++)
				{
					FbxShape* shape;
					shape = morphChannel->GetTargetShape(k);

					std::cout << "Shape name!!!!! " << shape->GetName() << "\n\n\n\n";


					int vertexCount = shape->GetControlPointsCount();
					FbxVector4* vertices = shape->GetControlPoints();

					for (int l = 0; l < vertexCount; l++)
					{
						std::cout << " x? " << ((double*)shape->GetControlPointAt(l))[0] << "";
						std::cout << " y? " << ((double*)shape->GetControlPointAt(l))[1] << "";
						std::cout << " z? " << ((double*)shape->GetControlPointAt(l))[2] << "\n\n";
					}
				}
			}
		}

	}
}

void MorphHandler::ProcessData(FbxGeometry* pGeo)
{

}