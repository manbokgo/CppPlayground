#include <algorithm>


// 이동 연산의 결과 상태가 바뀌는 예시. 수동으로 이동 연산을 구현. 
struct C
{
	const int i;

	C(int input)
		: i{input}
	{
	}

	C(C&& other) noexcept
		: i{other.i}
	{
	}

	C& operator=(C&& other) noexcept
	{
		if (this == &other) return *this;
		this->~C(); //Ok only if ~C is trivial
		return *(new(this) C{std::move(other)});
	}
};


int main()
{
	// Test 1
	struct X
	{
		const int i;
	};
	X* p  = new X{0};
	X* np = new(p) X{1};

	const int i  = np->i; // Ok
	const int i2 = p->i;  // Undefined Behavior

	// Test 2
	C a{4};
	C b{5};
	b = std::move(a);

	const int i3 = b.i; // Undefined Behavior

	// 컴파일러가 기대한 b.i는 불변 데이터이지만
	// 실제로는 데이터가 변경되었으므로 오류
	//
	// 만약 동일한 데이터였더라도
	// 컴파일러(타입 시스템)는 동일한 상태(데이터)라고 확신하지 못함
	// 따라서 디폴트 이동 연산자는 const 멤버 변수 대상으로 존재하지 않는다
	// 
	// 근데 사실 VS2022에서는 위 모두 크래쉬 안 뜸

	return 0;
}
