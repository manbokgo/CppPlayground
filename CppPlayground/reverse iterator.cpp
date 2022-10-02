#include <iostream>
#include <iterator>
#include <vector>

int main()
{
    std::vector<int> v = { 0, 1, 2, 3, 4, 5 };

    using RevIt = std::reverse_iterator<std::vector<int>::iterator>;

    const auto it = v.begin() + 3;
    RevIt r_it{ it };

    std::cout << "*it == " << *it << '\n'
        << "*r_it == " << *r_it << '\n'
        << "*r_it.base() == " << *r_it.base() << '\n'
        << "*(r_it.base()-1) == " << *(r_it.base() - 1) << '\n';

    RevIt r_end{ v.begin() };
    RevIt r_begin{ v.end() };

    for (auto it = r_end.base(); it != r_begin.base(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << '\n';

    int a = 3;
    if (a = 4)
    {   
        
    }

    for (auto it = r_begin; it != r_end; ++it) {
        std::cout << *it << ' ';
    }
    std::cout << '\n';

    auto iter = v.rbegin();
    auto iterEnd = v.rend();

    for (; iter != iterEnd;)
    {
	    if (*iter == 3)
	    {
            iter = std::make_reverse_iterator(v.erase(std::next(iter).base()));
            // OR
            iter = decltype(iter)(v.erase(std::next(iter).base()));

            // 첫 요소 왼쪽을 가리키는 rend()는 변함이 없어 다음은 불필요함.
            // iterEnd = v.rend();
            continue;
	    }
        ++iter;
    }

}
