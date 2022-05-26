#include <algorithm>


struct C
{
    const int i;
    C() : i{} {}
    C(int input) : i{input} {}
    C(C&& other) noexcept : i{ other.i } {}

    C& operator=(C&& other) noexcept
    {
        if (this == &other) return *this;
        this->~C(); //Ok only if ~C is trivial
        return *(new(this) C{ std::move(other) });
    }
};

int main()
{
    // test1
    struct X { const int i; };
    X* p = new X{ 0 };
    X* np = new (p) X{ 1 };

    const int i = p->i;
    const int i2 = np->i;

    // test2
    C a{4};
    C b{5};
    b = std::move(a);

    //Undefined behavior!
    const int test = b.i;

    return 0;
}