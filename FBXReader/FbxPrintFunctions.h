#pragma once
#include "fbxSDK.h"

void PrintNode(FbxNode* pNode);
FbxString GetAttributeTypeName(FbxNodeAttribute::EType type);
void PrintAttribute(FbxNodeAttribute* pAttribute);
void PrintTabs();