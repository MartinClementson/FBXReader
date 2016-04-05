#ifndef MATERIALSTRUCT_H
#define MATERIALSTRUCT_H


struct MaterialStruct
{
	unsigned int Id;  	float ambientVal[3]; 	float diffuseVal[3]; 	float specularVal[3];  	char diffMap[256]; 	char specMap[256]; 	char normalMap[256]; 	char glossMap[256]; 	char glowMap[256];
};

#endif // !MATERIALSTRUCT_H

