#include <cassert>
#include <iomanip>
#include <iostream>
#include <string>
#include <string_view>
 
void print_compare_result(std::string_view str1,
                          std::string_view str2,
                          int compare_result)
{
    if (compare_result < 0)
        std::cout << std::quoted(str1) << " comes before "
                  << std::quoted(str2) << ".\n";
    else if (compare_result > 0)
        std::cout << std::quoted(str2) << " comes before "
                  << std::quoted(str1) << ".\n";
    else
        std::cout << std::quoted(str1) << " and "
                  << std::quoted(str2) << " are the same.\n";
}
 
int main()
{
    std::string batman{"Batman"};
    std::string superman{"Superman"};
    int compare_result{0};
 
    // 1) Compare with other string
    compare_result = batman.compare(superman);
    std::cout << "1) ";
    print_compare_result("Batman", "Superman", compare_result);
 
    // 2) Compare substring with other string
    compare_result = batman.compare(3, 3, superman);
    std::cout << "2) ";
    print_compare_result("man", "Superman", compare_result);
 
    // 3) Compare substring with other substring
    compare_result = batman.compare(3, 3, superman, 5, 3);
    std::cout << "3) ";
    print_compare_result("man", "man", compare_result);
 
    // Compare substring with other substring
    // defaulting to end of other string
    assert(compare_result == batman.compare(3, 3, superman, 5));
 
    // 4) Compare with char pointer
    compare_result = batman.compare("Superman");
    std::cout << "4) ";
    print_compare_result("Batman", "Superman", compare_result);
 
    // 5) Compare substring with char pointer
    compare_result = batman.compare(3, 3, "Superman");
    std::cout << "5) ";
    print_compare_result("man", "Superman", compare_result);
 
    // 6) Compare substring with char pointer substring
    compare_result = batman.compare(0, 3, "Superman", 5);
    std::cout << "6) ";
    print_compare_result("Bat", "Super", compare_result);
}