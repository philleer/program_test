#include <iostream>
#include "printtest.h"

void printtest::add(){
	size_t tmp = x + y;
	std::cout << "x = " << x << std::endl;
	std::cout << "y = " << y << std::endl;
	std::cout << "x + y = " << tmp << std::endl;
}
