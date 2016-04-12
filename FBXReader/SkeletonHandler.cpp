#include "SkeletonHandler.h"



SkeletonHandler::SkeletonHandler()
{
}


SkeletonHandler::~SkeletonHandler()
{
}

void SkeletonHandler::GetSkeletonData(FbxNode * pNode, std::vector<SkeletonExport*>* outputSkeletons)
{
	if (pNode->GetSkeleton())
	{
		SkeletonExport *tempSkeleton = new SkeletonExport;
		jointCount = 0;
		jointID = 0;
		std::cout << "skeleton name: " << pNode->GetName() << "\n";
		FbxSkeleton *skel = pNode->GetSkeleton();
		FbxSkin * pSkin = (FbxSkin*)((FbxMesh*)skel->GetDstObject())->GetDeformer(0, FbxDeformer::eSkin);
		if (pSkin != NULL)
			tempSkeleton->skeletonInfo.jointCount = pSkin->GetClusterCount();
		//tempSkeleton.skeletonInfo.animationCount
		//ProcessData(pNode, tempSkeleton);
		//outputSkeletons->resize(sizeof(SkeletonExport));
		ProcessData(pNode, *tempSkeleton);
		outputSkeletons->push_back(tempSkeleton);
	}
}

void SkeletonHandler::ProcessData(FbxNode * pNode, SkeletonExport &outputSkeleton)
{
	//a joint can have several things as children here we
	//are controlling the proccesserd node to see that it
	//is in fact a joint
	if (pNode->GetSkeleton())
	{
		JointHeader tempJoint;
		FbxSkeleton *skel = pNode->GetSkeleton();
		
		//Getting all of the joint information
		memcpy(tempJoint.jointName, pNode->GetName(), sizeof(char) * 256);
		ProcessPosition(pNode, tempJoint);
		ProcessJoints((FbxMesh*)skel->GetDstObject(),tempJoint);
		std::cout << "currentJointCount: " << jointCount << "\n";


		ProcessKeyFrames(pNode, outputSkeleton);

		//skel->GetSrcObject()
		/*ProcessPosition(pNode);
		FbxTimeSpan animTime;
		pNode->GetAnimationInterval(animTime);
		FbxAnimEvaluator *anim = pNode->GetAnimationEvaluator();
		FbxVector4 test = anim->GetNodeLocalTranslation(pNode, animTime.GetStart(), pNode->eSourcePivot, false, false);*/
		/*FbxScene* scene = pNode->GetScene();
		FbxAnimStack* lAnimstack = scene->GetSrcObject<FbxAnimStack>(0);
		for (int i = 0; i < lAnimstack->GetSrcObjectCount<FbxAnimLayer>(); i++)
		{
			FbxAnimLayer* pAnimLayer = lAnimstack->GetMember<FbxAnimLayer>(i);
			FbxAnimCurve *curve = pNode->LclTranslation.GetCurve(pAnimLayer, FBXSDK_CURVENODE_COMPONENT_X);
			ProcessCurve(curve);
		}*/

		//root node
		if (skel->IsSkeletonRoot())
		{
			std::cout << "\n it's the root!!! \n";
			tempJoint.ParentJointID = 0;
		}
		else
		{
			std::cout << "it's a child\n";

			//assign the parent system here later, we can now effectively get the parents
			FbxNode *parent = pNode->GetParent();
			std::cout << "This is the parent: " << parent->GetName() << "\n\n";
		}
		
		//When all of the infromation for the current joint is extracted
		//we plus the jointID with one, to be used for the next joint
		jointID += 1;
		outputSkeleton.joints->push_back(tempJoint);
		//Recursively checking itself
		for (int i = 0; i < pNode->GetChildCount(); i++)
			ProcessData(pNode->GetChild(i), outputSkeleton);
	}
	return;
}

void SkeletonHandler::ProcessPosition(FbxNode * pNode, JointHeader &skeletonJoint)
{
	FbxDouble3 translation = pNode->LclTranslation.Get();
	FbxDouble3 rotation = pNode->LclRotation.Get();

	//just a temporary print, store the positions here
	std::cout << "Translation: (" << translation[0] << "," << translation[1] << "," << translation[2] << ")" << "\n\t";
	skeletonJoint.pos[0] = translation[0];
	skeletonJoint.pos[1] = translation[1];
	skeletonJoint.pos[2] = translation[2];

	std::cout << "Rotation   : (" << rotation[0] << "," << rotation[1] << "," << rotation[2] << ")" << "\n\t";
	skeletonJoint.rotation[0] = rotation[0];
	skeletonJoint.rotation[1] = rotation[1];
	skeletonJoint.rotation[2] = rotation[2];
}

void SkeletonHandler::ProcessKeyFrames(FbxNode * pNode, SkeletonExport &outputSkeleton)
{
	FbxScene * scene = pNode->GetScene();

	//Getting the number of animation stacks for this mesh
	//seeing as you can have different ones such as (running, walking...)
	int numAnimations = scene->GetSrcObjectCount<FbxAnimStack>();
	for (int animIndex = 0; animIndex < numAnimations; animIndex++)
	{
		//getting the current stack and evaluator
		FbxAnimStack *animStack = (FbxAnimStack*)scene->GetSrcObject<FbxAnimStack>(animIndex);
		FbxAnimEvaluator *animEval = scene->GetAnimationEvaluator();
		std::cout << animStack->GetName();
		//so far so good

		int numLayers = animStack->GetMemberCount();
		for (int layerIndex = 0; layerIndex < numLayers; layerIndex++)
		{
			FbxAnimLayer *animLayer = (FbxAnimLayer*)animStack->GetMember(layerIndex);
			std::cout << animLayer->GetName();

			FbxAnimCurve * translationCurve = pNode->LclTranslation.GetCurve(animLayer);
			FbxAnimCurve * rotationCurve = pNode->LclRotation.GetCurve(animLayer);
			FbxAnimCurve * scalingCurve = pNode->LclScaling.GetCurve(animLayer);

			if (translationCurve != NULL ||
				rotationCurve    != NULL ||
				scalingCurve     != NULL)
				jointCount += 1;

			//FbxTimeSpan animTime;
			//pNode->GetAnimationInterval(animTime, animStack);
			//FbxTime tid = animTime.GetStop();

			
			int max = 0;

			//can have three different matrices and in the end multiply them into the real one!
			std::vector<DirectX::XMMATRIX> scaleMatrix;
			std::vector<DirectX::XMMATRIX> rotationMatrix;
			std::vector<DirectX::XMMATRIX> translationMatrix;

			//temp
			std::vector<DirectX::XMMATRIX> frameMatrix;

			if (scalingCurve != NULL)
			{
				//getting the number of set key for this attrubute
				//for this joint, store this later for frameCount!
				int numKeys = scalingCurve->KeyGetCount();
				//double testKeys = scalingCurve->;
				FbxTimeSpan terra;
				scalingCurve->GetTimeInterval(terra);
				FbxTime test = terra.GetDuration();
				int bajs = test.GetFrameCount(FbxTime::eFrames24);
				//FbxDouble3 test = pNode->EvaluateLocalScaling(frameTime);
				//scalingCurve->GetTimeInterval(animTime);
				//std::cout << "\nstart: " << "to end: " ;
				for (int keyIndex = 0; keyIndex < numKeys; keyIndex++)
				{
					FbxTime frameTime = scalingCurve->KeyGetTime(keyIndex);
					FbxDouble3 scalingVector = pNode->EvaluateLocalScaling(frameTime);
					float x = (float)scalingVector[0];
					float y = (float)scalingVector[1];
					float z = (float)scalingVector[2];
					//for the worldMatrix of the frame
					scaleMatrix.push_back(DirectX::XMMatrixScaling(x, y, z));
					float frameSeconds = (float)frameTime.GetSecondDouble();
				}
			}
			if (rotationCurve != NULL)
			{
				//getting the number of set key for this attrubute
				//for this joint
				int numKeys = rotationCurve->KeyGetCount();
				for (int keyIndex = 0; keyIndex < numKeys; keyIndex++)
				{
					FbxTime frameTime = rotationCurve->KeyGetTime(keyIndex);
					FbxDouble3 rotationVector = pNode->EvaluateLocalRotation(frameTime);
					float x = (float)rotationVector[0];
					float y = (float)rotationVector[1];
					float z = (float)rotationVector[2];

					//for the worldmatrix of the frame
					DirectX::XMMATRIX tempRotation;
					DirectX::XMMATRIX rotationx = DirectX::XMMatrixRotationX(x);
					DirectX::XMMATRIX rotationy = DirectX::XMMatrixRotationY(y);
					DirectX::XMMATRIX rotationz = DirectX::XMMatrixRotationZ(z);
					
					tempRotation = rotationx*rotationy; tempRotation = tempRotation*rotationz;
					rotationMatrix.push_back(tempRotation);


					float frameSeconds = (float)frameTime.GetSecondDouble();
				}
			}
			if (translationCurve != NULL)
			{
				//getting the number of set key for this attrubute
				//for this joint
				int numKeys = translationCurve->KeyGetCount();
				for (int keyIndex = 0; keyIndex < numKeys; keyIndex++)
				{
					FbxTime frameTime = translationCurve->KeyGetTime(keyIndex);
					FbxDouble3 translationVector = pNode->EvaluateLocalTranslation(frameTime);
					float x = (float)translationVector[0];
					float y = (float)translationVector[1];
					float z = (float)translationVector[2];

					translationMatrix.push_back(DirectX::XMMatrixTranslation(x, y, z));

					float frameSeconds = (float)frameTime.GetSecondDouble();
				}
			}

			//getting the maximum value of keyframes
			//from the number of keyframes
			if (max < scaleMatrix.size())
				max = scaleMatrix.size();
			if (max < rotationMatrix.size())
				max = rotationMatrix.size();
			if (max < translationMatrix.size())
				max = translationMatrix.size();

			//add matrix here
			for (int i = 0; i < max; i++)
			{
				DirectX::XMMATRIX tempFrameMatrix;

				//checking if the size of the matrices are in the range of the max value
				//seeing as the rotationMatrix might have 3 stored values while the scale
				//Matris has only 1. This way we check the matrices and assign an identity
				//matrix as a base value and add the other values.
				if (scaleMatrix.size() >= i)
					tempFrameMatrix = DirectX::XMMatrixMultiply(scaleMatrix.at(i), DirectX::XMMatrixIdentity());

				//if the scaleMatrix doesnt exist, we assign it to an identity matrix so that we can
				//easily multiply the other values. This check is only performed here because if it doesnt
				//the matrix get the identity value, and if the rotation doesnt exist, the matrix would need
				//to be multiplied by an identity matrix which according the mathmagic is the same as the
				//matrix inserted. Hence, we do not need to assign another value.
				else
					tempFrameMatrix = DirectX::XMMatrixIdentity();
				if (rotationMatrix.size() >= i)
					tempFrameMatrix = DirectX::XMMatrixMultiply(rotationMatrix.at(i), tempFrameMatrix);
				if (translationMatrix.size() >= i)
					tempFrameMatrix = DirectX::XMMatrixMultiply(translationMatrix.at(i), tempFrameMatrix);

				//now that we have the combined matrix of the whole position, we store it here
				frameMatrix.push_back(tempFrameMatrix);
			}
		}
	}
}

void SkeletonHandler::ProcessJoints(FbxMesh * pMesh, JointHeader &skeletonJoint)
{
	//send in a matrix here as well to store the
	//transformation matrix of the baseposition
	//int numDeformers = pMesh->GetDeformerCount();
	FbxSkin * pSkin = (FbxSkin*)pMesh->GetDeformer(0, FbxDeformer::eSkin);
	if (pSkin != NULL)
	{
		//bonecount can be number of joints
		//int boneCount = pSkin->GetClusterCount();
		//for (int boneIndex = 0; boneIndex < boneCount; boneIndex++)
		//{
		FbxCluster * pCluster = pSkin->GetCluster(jointID);
			//FbxNode* pBone = pCluster->GetLink();
			//std::cout << "\n\n" << pBone->GetName();

			//Getting the bindpose
		FbxAMatrix bindPose;
		pCluster->GetTransformLinkMatrix(bindPose);

		//setting the bindpose matrix
		skeletonJoint.bindPoseMatrix[0][0] = bindPose[0][0];
		skeletonJoint.bindPoseMatrix[0][1] = bindPose[0][1];
		skeletonJoint.bindPoseMatrix[0][2] = bindPose[0][2];
		skeletonJoint.bindPoseMatrix[0][3] = bindPose[0][3];

		skeletonJoint.bindPoseMatrix[1][0] = bindPose[1][0];
		skeletonJoint.bindPoseMatrix[1][1] = bindPose[1][1];
		skeletonJoint.bindPoseMatrix[1][2] = bindPose[1][2];
		skeletonJoint.bindPoseMatrix[1][3] = bindPose[1][3];

		skeletonJoint.bindPoseMatrix[2][0] = bindPose[2][0];
		skeletonJoint.bindPoseMatrix[2][1] = bindPose[2][1];
		skeletonJoint.bindPoseMatrix[2][2] = bindPose[2][2];
		skeletonJoint.bindPoseMatrix[2][3] = bindPose[2][3];

		skeletonJoint.bindPoseMatrix[3][0] = bindPose[3][0];
		skeletonJoint.bindPoseMatrix[3][1] = bindPose[3][1];
		skeletonJoint.bindPoseMatrix[3][2] = bindPose[3][2];
		skeletonJoint.bindPoseMatrix[3][3] = bindPose[3][3];
			//int * pBoneVertIndices = pCluster->GetControlPointIndices();
			//double * pBoneVertWeights = pCluster->GetControlPointWeights();

			//int numBoneVertIndices = pCluster->GetControlPointIndicesCount();
			//for (int boneVertIndex = 0; boneVertIndex < numBoneVertIndices; boneVertIndex++)
			//{
			//	//store the weights here in the mesh vertices
			//	int boneVertexIndex = pBoneVertIndices[boneVertIndex];
			//	double boneWeight = pBoneVertWeights[boneVertIndex];
			//}
		//}
	}
}

