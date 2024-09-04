#include <directxmath.h>
using namespace DirectX;

struct CMatrices
{
    XMFLOAT2 before;          // Offset: 0
    alignas(16) XMFLOAT3 _11; // Offset: 16
    alignas(16) XMFLOAT3 _21; // Offset: 32
    alignas(16) XMFLOAT3 _31; // Offset: 48
    float smol_mat;        // Offset: 60
};  // Size: 80  alignof: 16

#include <iostream>

int main()
{
    CMatrices x, y, z;
    std::cout
        << "sizeof = " << sizeof(CMatrices) << '\n'
        << "alignof = " << alignof(CMatrices) << '\n'
        // << std::hex << std::showbase
        // << "&x: " << &x << '\n'
        // << "&y: " << &y << '\n'
        // << "&z: " << &z << '\n'
        << std::dec << std::showbase
        // << "&diff: " << (int)&z - (int)&y << '\n'
        << "1: " << offsetof(CMatrices, before) << '\n'
        << "2: " << offsetof(CMatrices, _11) << '\n'
        << "2: " << offsetof(CMatrices, _21) << '\n'
        << "2: " << offsetof(CMatrices, _31) << '\n'
        << "4: " << offsetof(CMatrices, smol_mat) << '\n'
        // << "&z c: " << offsetof(Foo, c) << '\n'
        // << "&z d: " << offsetof(Foo, d) << '\n'
        ;
}
