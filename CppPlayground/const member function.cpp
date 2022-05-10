#include <iostream>

class Test
{
private:
	int* p = nullptr;

public:
	// 기본 생성자 생략

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
	Test bar = Test(&i);
	// const Test bar = Test(&i); // const 객체
	
	std::cout << i << std::endl; // OUT: 1

	bar.Foo();
	std::cout << i << std::endl; // OUT: 5

	return 0;
}