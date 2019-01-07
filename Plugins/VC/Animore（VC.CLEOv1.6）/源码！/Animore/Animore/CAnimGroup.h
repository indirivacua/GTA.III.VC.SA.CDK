//不是我的TAT
#pragma once
#include <cstdint>

#pragma pack(push, 1)

struct AnimIndece
{
	int32_t ID;
	int32_t flags;
};

class CAnimGroup
{
public:
	char *groupName;
	char *ifpName;
	int32_t testModel;
	int32_t animsCount;
	char **animsNamesList;
	AnimIndece *animsIndeces;
};

#pragma pack(pop)