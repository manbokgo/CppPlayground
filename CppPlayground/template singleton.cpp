#include <iostream>

template <typename T>
class Singleton
{
public:
    static T& Instance()
    {
        static T instance{ token{} };
        return instance;
    }

    Singleton(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton& operator=(Singleton&&) = delete;

protected:
    Singleton() = default;
    ~Singleton() = default;

        struct token {};
};


// .cpp
#define	SINGLETON_CLASS(Type)     \
public:                           \
    Type() = delete;              \
    Type(token);                  \
    ~Type();

// example
class Foo : public Singleton<Foo>
{
public:
    Foo() = delete;

    explicit Foo(token)
    {
        std::cout << "Created" << std::endl;
    }
    ~Foo()
    {
        std::cout << "Destructed" << std::endl;
    }
};

int main()
{
    std::cout << "Entering main()" << std::endl;

    const auto& t = Foo::Instance();
    // Singleton<Foo> t3;

    std::cout << "Leaving main()" << std::endl;
}
