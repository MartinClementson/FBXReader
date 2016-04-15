#pragma once
#include <fbxsdk.h>
#include <iostream>
#include <vector>
#include <DirectXMath.h>
#include <map>
#include <string>
struct SceneMap
{
	std::map<std::string, unsigned int> sceneHash;
	std::map<std::string, unsigned int> materialHash;
	unsigned int sceneObjectId = 1;
	unsigned int materialID = 0;

};


struct dummyStructClass
{

};

