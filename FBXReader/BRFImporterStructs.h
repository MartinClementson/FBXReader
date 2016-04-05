#pragma once
namespace BRFImporter
{
//STRUCTS WITH #PRAGMA REGION IN ORDER: 1. STATIC 2. DYNAMICS OF THAT STATIC, REPEAT
#pragma region Mainheader
	struct MainHeader
	{
		bool lights;

		unsigned int meshAmount;
		unsigned int materialAmount;
		unsigned int cameraAmount;
		unsigned int skeletonAmount;
		unsigned int morphAnimAmount;
		unsigned int groupAmount;
		unsigned int attributeAmount;
	};
#pragma endregion
#pragma region MeshHeader
	struct MeshHeader
	{
		char meshName[256];
		unsigned int objectID;
		unsigned int parentID;		// 0 = Default

		unsigned int vertexCount;
		unsigned int indexCount;
		unsigned int materialID;

		unsigned int attrCount;		// 0 = Default

		bool boundingBox;

		double translation[3];
		double rotation[3];
		double scale[3];
	};
#pragma endregion
	#pragma region MeshHeader Dynamics
	struct OOBBHeader
	{
		float extents[3];
		float orientation[4];

	};
	struct IndexHeader
	{
		unsigned int vertIndex;
	};
	struct VertexHeader
	{
		double pos[3];
		double normal[3];
		double uv[2];
		double tangent[2];
		double biTangent[2];
		unsigned int weightAmmount;
	};
	struct WeigthsHeader
	{
		double influence;
		unsigned int jointID;
	};
	#pragma endregion
#pragma region MaterialHeader
	struct MaterialHeader
	{
		unsigned int materialID;

		//float diffuseR,diffuseG,diffuseB
		//float specR,specG,specB
		//float norR,norB,norG
		//TO BE CONTINUED
	};
#pragma endregion
#pragma region SkeletonHeader
	struct SkeletonHeader
	{
		unsigned int jointCount;
		unsigned int animationCount;
	};
#pragma endregion
	#pragma region SkeletonHeader Dynamics
	struct JointHeader
	{
		char jointName[256];
		unsigned int jointID;
		unsigned int ParentJointID;		// 0 = Default;

		double pos[3];
		double rotation[3];
	};
	struct AnimationHeader
	{
		char animationName[256];
		unsigned int frameCount;
	};
	struct JointCountHeader
	{
		unsigned int jointCount;
	};
	struct FrameHeader
	{
		unsigned int jointID;
		unsigned int frameID;

		double time;
		double pos[3];
		double rotation[3];
	};
	#pragma endregion
#pragma region CameraHeader
	struct CameraHeader
	{
		unsigned int objectID;
		unsigned int parentID;		// 0 = Default

		double translation[3];
		double rotation[3];
		double viewDir[3];
	};
#pragma endregion
#pragma region LightHeader
	struct LightHeader
	{
		unsigned int spotCount;
		unsigned int ambientCount;
		unsigned int directionalCount;
		unsigned int areaCount;
		unsigned int pointCount;
	};
#pragma endregion
	#pragma region LightHeader Dynamics
	struct SpotLightHeader
	{
		unsigned int objectID;
		unsigned int parentID;		// 0 = Default
		double pos[3];
		double rotation[3];
		double outerAngle;
		float color[3];
		float intensity;
	};
	struct AmbLightHeader
	{
		unsigned int objectID;
		unsigned int parentID;		// 0 = Default
		float color[3];
		float intensity;
	};
	struct AreaLightHeader
	{
		unsigned int objectID;
		unsigned int parentID;		// 0 = Default
		double pos[3];
		double rotation[3];
		double width;
		double height;
		float color[3];
		float intensity;
	};
	struct PointLightHeader
	{
		unsigned int objectID;
		unsigned int parentID;		// 0 = Default
		double pos[3];
		float color[3];
		float intensity;
	};
	struct DirLightHeader
	{
		unsigned int objectID;
		unsigned int parentID;		// 0 = Default
		double pos[3];
		double rotation[3];
		float color[3];
		float intensity;
	};
	#pragma endregion
#pragma region GroupHeader
	struct GroupHeader
	{
		char groupName[256];
		unsigned int objectID;		// 0 = Default	
		unsigned int parentID;		// 0 = Default

		double translation[3];
		double rotation[3];
		double scale[3];
	};
#pragma endregion
#pragma region MorphAnimHeader
	struct MorphAnimHeader
	{
		unsigned int vertices;
		unsigned int shapeID;
	};
#pragma endregion
	#pragma region MorphAnimHeader Dynamics
	struct MorphVertexHeader
	{
		double pos[3];
		unsigned int vertIndex;
	};
	#pragma endregion
#pragma region AttributeHeader
	struct AtributeHeader
	{

		unsigned int floatAmount;
		unsigned int intAmount;
		unsigned int boolAmount;
		unsigned int stringAmount;
		unsigned int vectorAmount;
	};
#pragma endregion
	#pragma region AttributeHeader Dynamics
	struct VectorAttrHeader
	{
		char attrName[256];

		float value[3];


	};

	struct StringAttrHeader
	{
		char attrName[256];
		char value[256];

	};

	struct FloatAttrHeader
	{
		char attrName[256];
		float value;
		float min;
		float max;

	};

	struct BoolAttrHeader
	{
		char attrName[256];
		bool value;
	};

	struct IntAttrHeader
	{
		char attrName[256];

		unsigned int value;

		unsigned int min;
		unsigned int max;
	};
	#pragma endregion
}