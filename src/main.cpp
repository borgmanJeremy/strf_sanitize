#include "parse.hpp"
#include <iostream>

int main()
{

    std::string specifier = "";
    std::cout << "Starting Specifier: " << specifier << std::endl;
    auto result = format_time_string(specifier);

    std::cout << result;
}
