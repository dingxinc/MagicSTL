#include "../string.h"
#include <iostream>

namespace mstl = magicstl;

int main() {
    mstl::string s1("Hello, world!");
    s1 << " This is a test string.";
    s1 << " This is another test string.";
    std::cout << s1.data() << std::endl;
    size_t pos = s1.find("orld");
    std::cout << "Found world at position " << pos << std::endl;
    s1.resize(100);
    std::cout << "Resized to " << s1.size() << " characters" << "capacity = " << s1.capacity() << std::endl;

    mstl::string s2("hahahahahahahahaha");
    size_t count = s2.count("haha", 2, 4);
    std::cout << "count = " << count << std::endl;


    // mstl::string s2 = "Goodbye, world!";
    return 0;
}