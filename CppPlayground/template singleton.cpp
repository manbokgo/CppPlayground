#include <iostream>
#include <mutex>

template <typename T>
class Singleton
{
public:
    template <typename... Args>
    static void CreateInstance(Args&&...args)
    {
        struct AbstractSingleton : T
        {
            using T::T;
            void injectAbstraction() override {}
        };

        static std::once_flag flag;
        std::call_once(flag,
                       [](auto&&...args)
                       {
                           m_Instance = std::make_unique<AbstractSingleton>(std::forward<Args>(args)...);
                       },
                       std::forward<Args>(args)...);
    }

    static T& Instance()
    {
        return *m_Instance;
    }

    Singleton(const Singleton&)            = delete;
    Singleton(Singleton&&)                 = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton& operator=(Singleton&&)      = delete;

protected:
    Singleton()  = default;
    ~Singleton() = default;

private:
    virtual void injectAbstraction() = 0;

private:
    static inline std::unique_ptr<T> m_Instance = nullptr;
};

// example
class Foo : public Singleton<Foo>
{
public:
    Foo(int value)
        : m_Value(value)
    {
        std::cout << "Init " << m_Value << std::endl;
    }

    ~Foo() {}

private:
    int m_Value;
};

int main()
{
    std::cout << "Entering main()" << std::endl;

    Foo::CreateInstance(42);
    const auto& t = Foo::Instance();

    std::cout << "Leaving main()" << std::endl;
}
