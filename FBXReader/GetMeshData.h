#pragma once

#include "fbxsdk.h"
void ProcessData(FbxMesh* pMesh);
void GetMeshData(FbxNode* pNode);
void GetVertPositions(FbxMesh* pMesh, int index, float* targetPos /*insert struct to fill here*/);