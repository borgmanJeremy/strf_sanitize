#include "parse.hpp"
#include <iostream>

int main()
{
    std::string specifier;

    std::cout << "Enter String to Test.\nFor Example, %H_%M_%S\n:";
    std::cin >> specifier;
    auto result = format_time_string(specifier);

    std::cout << result;
}
