#pragma once

// small diagram and explaination at https://www.lucidchart.com/invitations/accept/8d8e6ef6-e78a-4314-8d85-2d14ea5f3da4

#include "fbxSDK.h"
#include "BRFImporterStructs.h"
#include "BrfExporter.h"



struct BlendVertexHeader
{
	double pos[3];
	double normal[3];
	double tangent[2];
	double biTangent[2];
	

};
#pragma region structs for handling the import and conversion
struct BlendFrame
{
	unsigned int			  frameTime;
	std::vector<unsigned int> meshIDs;
	std::vector<float>	      influence;

};

struct BlendAnimation
{
	unsigned int			 animationTime = 0;
	std::vector<BlendFrame>  frames;

};

struct BlendMesh
{
	std::vector<BlendVertexHeader> vertices;
};
#pragma endregion

#pragma region Structs that will be used for the output. Might be moved to the brf exporter class later

struct OutPutShape
{
	unsigned int frameNumber;
	float normalizedFrameTime; // from 0.0 to 1.0
	std::vector<BlendVertexHeader> vertices;

	void NormalizeFrameTime(unsigned int animationTime)
	{
		normalizedFrameTime = frameNumber / animationTime;
	}
};
struct OutPutAnimation
{
	std::vector<OutPutShape>  shapes;
	unsigned int			  animationTime; //in frames. This is the last frame number, NOT the amount of frames we have.

};

#pragma endregion

class MorphAnimation
{
private:
	std::map<int, BlendMesh*> blendShapeMap;
	// a mesh ID is connected to the index in an array

	std::vector<BlendMesh*> blendMeshes;
	MeshExport* sourceMesh = nullptr;

	std::vector<BlendAnimation*> animations;

	bool isATargetMesh(const char* name);


	void ExtractSourceMesh(FbxNode* pNode);
	BlendMesh* ExtractTargetMesh(FbxNode* pNode);
	void ExtractAllMeshesInAnimation(FbxNode* pNode);


	void GetVertPositions(FbxMesh* pMesh, int index, double* targetPos);
	void GetVertNormals(fbxsdk::FbxGeometryElementNormal* pNElement, int index, double* targetNormal);
	void GetVertBiNormals(fbxsdk::FbxGeometryElementBinormal* pBNElement, int index, double* targetBiNormal);
	void GetVertTangents(fbxsdk::FbxGeometryElementTangent* pTElement, int index, double* targetTangent);
	void GetVertTextureUV(fbxsdk::FbxGeometryElementUV* uvElement, int index, double* targetUV);
	void GetPolygonNormals(double * targetNormal, FbxVector4 * sourceNormals);
public:
	void GetMorphAnimation(FbxNode * pNode);
	MorphAnimation();
	~MorphAnimation();
};

