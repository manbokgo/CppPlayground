struct XMFLOAT4
{
    float data[4];
};
struct XMFLOAT3
{
    float data[3];
};
struct XMFLOAT2
{
    float data;
    float data2;
};

#pragma pack(4)
struct Foo
{
    char a;
    int b;
    char c;
    double d;
};

#include <iostream>

int main()
{
    Foo x, y, z;
    std::cout
        << "sizeof(Foo) = " << sizeof(Foo) << '\n'
        << "alignof(Foo) = " << alignof(Foo) << '\n'
        << std::hex << std::showbase
        << "&x: " << &x << '\n'
        << "&y: " << &y << '\n'
        << "&z: " << &z << '\n'
        << std::dec << std::showbase
        << "&diff: " << (int)&z - (int)&y << '\n'
        << "&z a: " << offsetof(Foo, a) << '\n'
        << "&z b: " << offsetof(Foo, b) << '\n'
        << "&z c: " << offsetof(Foo, c) << '\n'
        << "&z d: " << offsetof(Foo, d) << '\n';
}
