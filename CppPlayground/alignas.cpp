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
    float data[2];
};

// Good
#pragma pack(16)
struct alignas(16) Foo
{
    XMFLOAT3 a; // 0
    XMFLOAT3 b; // 12
    bool     c; // 24
    float    d; // 25
}; // 이처럼 pack이 원래의 정렬보다 더 작다면 효과가 있다.

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
        << "&z b: " << offsetof(Foo, c) << '\n'
        << "&z b: " << offsetof(Foo, d) << '\n'
        // << "&z c: " << offsetof(Foo, c) << '\n'
        // << "&z d: " << offsetof(Foo, d) << '\n'
        ;
}
