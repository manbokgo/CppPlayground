#include <cstdio>

// id(int), "name"(const char*), hp(int)
#define MONSTER_DATA					 	\
    MONSTER_ENTRY(0, "pope",	100)		\
    MONSTER_ENTRY(1, "big rat",	30)			\
    MONSTER_ENTRY(2, "mama",	255)		\
    MONSTER_ENTRY(3, "dragon",	300000)		\

int main(void)
{
	int ids[] = {
		#define MONSTER_ENTRY(id, name, hp) id,
		MONSTER_DATA
		#undef    MONSTER_ENTRY
	};

	const char* names[] = {
		#define MONSTER_ENTRY(id, name, hp) name,
		MONSTER_DATA
		#undef    MONSTER_ENTRY
	};

	for (size_t i = 0; i < sizeof(ids) / sizeof(int); ++i)
	{
		printf("%3d %s\n", ids[i], names[i]);
	}
};
