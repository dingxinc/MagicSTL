#include "../string.h"
#include <iostream>

namespace mstl = magicstl;

int main() {
	mstl::string s1;
	mstl::string s2("hello world");
	std::cout << s2.data() << " " << s2.size() << " " << s2.capacity() << '\n';

	s2.erase(2, 3);
	std::cout << s2.data() << " " << s2.size() << " " << s2.capacity() << '\n';


	mstl::string s3(s2);
	std::cout << s3.data() << " " << s3.size() << " " << s3.capacity() << '\n';
	
	s3.recapacity(20);
	std::cout << s3.data() << " " << s3.size() << " " << s3.capacity() << '\n';

	s3.clear();
	std::cout << s3.size() << " " << s3.capacity() << '\n';

	s2.push_back('c');
	std::cout << s2.data() << " " << s2.size() << " " << s2.capacity() << '\n';

	s2.pop_back();
	std::cout << s2.data() << " " << s2.size() << " " << s2.capacity() << '\n';

	s2.pop_front();
	std::cout << s2.data() << " " << s2.size() << " " << s2.capacity() << '\n';
	
	std::cout << s2[2] << s2[3] << std::endl;

	s2.erase(3);
	std::cout << s2.data() << " " << s2.size() << " " << s2.capacity() << '\n';

	return 0;
}