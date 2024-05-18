// https://stackoverflow.com/a/25245676
// non-deduced context 비-추론 문맥?
// 암시적으로 추론되지 않고, 명확하게 지정해야 추론되는 경우

template <typename>
struct Foo {};

template<>
struct Foo<float>
{
    Foo() = default;
    Foo(Foo<int> a) ;
};

template <typename T>
bool binary_function(Foo<T> lhs, Foo<T> rhs);


template <typename T>
struct type_identity {
    using type = T;
};

template <typename T>
bool binary_function(Foo<T> lhs, typename type_identity<Foo<T>>::type rhs)
{
    return binary_function(lhs, rhs);
}

int main()
{
    Foo<float> t{};
    Foo<int> u{};
    binary_function(t, u);
}