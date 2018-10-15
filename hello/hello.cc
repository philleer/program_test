#include <iostream>
#include <string>
#include <iterator>
#include <fstream>
#include <numeric>
#include <vector>
#include "printtest.h"

template<typename ForwardIterator> void square(ForwardIterator first, ForwardIterator last);

int main(int argc, const char *argv[])
{
	if(argc < 2) {
		std::cout << "No arguments input!" << std::endl;
	}
	else {
		for (signed int i = 0; i < argc; i++) {
			std::cout << argv[i] << " ";
		}
		std::cout << std::endl;
	}

	printtest num(1, 2);
	num.add();
	
	std::ifstream myInt("data");
	std::istream_iterator<int> iter(myInt);
	std::istream_iterator<int> eos;

	std::cout << "Sum of the data is "
		   	  << accumulate(iter, eos, 0)
			  << std::endl;

	int arr[] = {1, 3, 5, 7, 9};
	std::vector<int> v(arr, arr + sizeof(arr)/sizeof(arr[0]));
	std::cout << "Elements: ";
	for ( auto it:v ) {
			std::cout << it << " ";
	}
	std::cout << std::endl;
	square(v.begin(), v.end());

	return 0;
}

template<typename ForwardIterator>
void square(ForwardIterator first, ForwardIterator last) {
		std::cout << "  Square: ";
		for(; first != last; first++) {
				*first = (*first) * (*first);
				std::cout << *first << " ";
		}
		std::cout << std::endl;
}

