#include "printtest.h"

void printtest::add(){
	size_t tmp = x + y;
	std::cout << "x = " << x << std::endl;
	std::cout << "y = " << y << std::endl;
	std::cout << "x + y = " << tmp << std::endl;
}

/*
template<typename ForwardIterator>
void square(ForwardIterator first, ForwardIterator last) {
		std::cout << "  Square: ";
		for ( ; first != last; first++ ) {
				*first = (*first) * (*first);
				std::cout << *first << " ";
		}
		std::cout << std::endl;
}
*/
