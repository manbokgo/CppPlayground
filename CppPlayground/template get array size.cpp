template <typename T, size_t size>
[[nodiscard]] constexpr size_t GetArrLength(const T(&)[size]) { return size; }

struct Test
{
	int a[2];

	[[nodiscard]] constexpr size_t Foo() const
	{
		return GetArrLength(a);
	}
};


int main()
{
	int a[] = { 1,2,3,4 };
	GetArrLength(a);

	Test t{};
	size_t size = t.Foo();
}
