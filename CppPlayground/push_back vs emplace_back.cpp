#include <vector>
#include <string>
#include <utility>

namespace {
    //*
    char const A[] = "Bob";
    char const B[] = "pizza";
    char const C[] = "Smith";
    /*/
    char const A[] = "Some long string that doesn't fit in SSO";
    char const B[] = "Some other long string that doesn't fit in SSO";
    char const C[] = "Yet another long string that doesn't fit in SSO";
    //*/
}

int main()
{
	{
		std::vector<std::string> vec;
		vec.reserve(1);
		vec.push_back(A);
	}

    {
        std::vector<std::string> vec;
        vec.reserve(1);
        vec.emplace_back(A);
    }

}

