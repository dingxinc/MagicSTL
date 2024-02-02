#include "../string.h"
#include <iostream>

namespace mstl = magicstl;

int main() {
    mstl::string s1("Hello, world!");
    size_t pos = s1.find("world", 3);
    std::cout << "Found world at position " << pos << std::endl;
    // mstl::string s2 = "Goodbye, world!";
    return 0;
}