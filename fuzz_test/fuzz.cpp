#include "../src/parse.hpp"
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
    if (size < 2) {
        return 0;
    }

    char* str = new char[size + 1];
    std::memcpy(str, data, size);
    str[size] = 0;

    std::string input{ str };
    format_time_string(str);

    delete[] str;
    return 0; // Non-zero return values are reserved for future use.
}
