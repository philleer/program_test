#include <iostream>
#include <string>
#include "printtest.h"

int main(int argc, const char *argv[])
{
	if(argc < 2) {
		std::cout << "No arguments input!" << std::endl;
	}
	else {
		for (signed int i = 0; i < argc; i++) {
			std::cout << argv[i] << std::endl;
		}
	}

	std::cout << "Hello world!" << std::endl;

	printtest num(1, 1);
	num.add();

	return 0;
}
