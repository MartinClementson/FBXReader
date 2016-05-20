#pragma once
#include <fbxsdk.h>
#include <iostream>
#include <vector>
#include <DirectXMath.h>

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
struct dummyStructVert
{
	float position[3];
	
	float scale[3];
	float normal[3];
	float uv[2];
	float biNormal[2];
	float tangents[2];

};


struct dummyStructClass
{

};

