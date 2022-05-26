// 최적화가 되는지 모르겠네

#include <iostream>

#ifdef NDEBUG
# define ASSERT(e)    ( __assume(e) )
#else
# include <cassert>
# define ASSERT(e)    ( assert(e) )
#endif


enum class my_enum
{
	a,
	b,
	c,
};


int func1(my_enum i)
{
	switch (i)
	{
	case my_enum::a:
		return 11;
	case my_enum::b:
		return 12;
	case my_enum::c:
		return 13;
	default:
		ASSERT(false);
		return 0;
	// __assume(0);
	// This tells the optimizer that the default
	// cannot be reached. As so, it does not have to generate
	// the extra code to check that 'p' has a value
	// not represented by a case arm. This makes the switch
	// run faster.
	}
}

int main(int p)
{
	my_enum a      = my_enum::b;
	int     result = func1(a);
	std::cout << result << std::endl;
	return 0;
}
