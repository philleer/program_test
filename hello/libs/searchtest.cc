#include <iostream>
#include <string>
#include "searchtest.h"

searchtest::~searchtest() {
	std::cout << "This is test for header files search in makefile" << std::endl;
}

void searchtest::printtest() const {
	std::cout << "Print test?: " << str << std::endl;
}
