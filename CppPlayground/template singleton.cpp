#include <iostream>

template <typename T>
class Singleton
{
public:
	static T& Instance()
	{
		static T instance;
		return instance;
	}

	Singleton(const Singleton&)            = delete;
	Singleton& operator=(const Singleton&) = delete;

protected:
	Singleton() = default;
};

// example
class TestSingleton final : public Singleton<TestSingleton>
{
	friend class Singleton<TestSingleton>;
private:
	TestSingleton() { std::cout << "constructed" << std::endl; }

public:
	~TestSingleton() { std::cout << "destructed" << std::endl; }

	void use() const { std::cout << "in use" << std::endl; };
};

int main()
{
	// Test cannot_create; /* ERROR */
	std::cout << "Entering main()" << std::endl;
	{
		auto const& t = TestSingleton::Instance();
		t.use();
	}
	{
		auto const& t = TestSingleton::Instance();
		t.use();
	}
	std::cout << "Leaving main()" << std::endl;
}
