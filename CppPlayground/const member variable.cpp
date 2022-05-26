
#include <functional>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>


void print(auto comment, auto const& seq, char term = ' ') {
    for (std::cout << comment << '\n'; auto const& elem : seq)
        std::cout << elem << term;
    std::cout << '\n';
}


template <typename T>
class const_wrapper {
    T val_;
public:
    constexpr const_wrapper(const T& val) : val_{ val } {}
    constexpr const_wrapper(T&& val) : val_{ std::move(val) } {}

    [[nodiscard]] constexpr auto get() const -> const T& { return val_; }
    [[nodiscard]] constexpr operator T() const { return val_; }
};

struct Point {
    int x = 0;
    int y = 0;

    template<class Os> friend
        Os& operator<< (Os& os, Point const& p) {
        return os << std::left << std::setw(8) << p.x << " : " << p.y << ' ';
    }
};

struct ImmutablePoint {
    const_wrapper<int> x = 0;
    const_wrapper<int> y = 0;

    template<class Os> friend
        Os& operator<< (Os& os, ImmutablePoint const& p) {
        return os << std::left << std::setw(8) << p.x << " : " << p.y << ' ';
    }
};

struct ImmutableTriangle {
    std::reference_wrapper<const ImmutablePoint> a;
    std::reference_wrapper<const ImmutablePoint> b;
    std::reference_wrapper<const ImmutablePoint> c;
};

int main() {
    std::vector<ImmutablePoint> points;
    points.emplace_back(1, 3);
    points.emplace_back(4, 3);
    points.emplace_back(2, 3);
    
    std::ranges::sort(points, {}, &ImmutablePoint::x); // Ok
    print("\nSort by name using a projection", points, '\n');
    
    // std::vector<const Point&> triangles1; // Error
    std::vector<std::reference_wrapper<const Point>> triangles2;
    Point q{ 3,2 };
    triangles2.emplace_back(q);
    triangles2[0].get();
    
    std::ranges::sort(triangles2, {}, &Point::x);
    print("\nSort by name using a projection", triangles2, '\n');
}