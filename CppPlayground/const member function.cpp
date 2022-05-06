#include <iostream>

class Test
{
private:
	int* p = nullptr;

public:
	Test(int* i) : p(i)
	{
	}
	void Foo() const
	{
		// p = nullptr; // Compile Error
		*p = 5;
	}
};

int main()
{
	int i = 1;
	const Test bar = Test(&i);

	std::cout << i << std::endl;
	bar.Foo();
	std::cout << i << std::endl;

	return 0;
}
