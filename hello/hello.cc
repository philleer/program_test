#include <iostream>
#include <string>
#include <iterator>
#include <fstream>
#include <numeric>
#include <vector>
#include <future>
#include <exception>
#include "printtest.h"
#include "libs/searchtest.h"

int main(int argc, const char** argv)
{
	// arguments
	if(argc < 2) {
		std::cout << "No arguments input!" << std::endl;
	}
	else {
		for (signed int i = 0; i < argc; i++) {
			std::cout << argv[i] << " ";
		}
		std::cout << std::endl;
	}

	// headers including problem
	printtest num(1, 2);
	num.add();
	
	// iterator test
	std::ifstream myInt("data");
	std::istream_iterator<int> iter(myInt);
	std::istream_iterator<int> eos;

	std::cout << "Sum of the data is "
		   	  << accumulate(iter, eos, 0)
			  << std::endl;

	std::vector<int> vectest{ 1, 2 , 3, 0};
	for (size_t x : vectest) {
			std::cout << x << " ";
	}
	std::cout << std::endl;
	bool boolvalue = lastGreaterThanFirst( vectest );
	std::cout << "The bool value of boolvalue " << boolvalue << std::endl;

	int arr[] = {1, 3, 5, 7, 9};
	std::vector<int> v(arr, arr + sizeof(arr)/sizeof(arr[0]));
	std::cout << "Elements: ";
	for ( auto it:v ) {
			std::cout << it << " ";
	}
	std::cout << std::endl;
	square(v.begin(), v.end());

	// template test
	fun1();
	fun2();

	// thistest
	thistest _name("wonder");
	std::cout << "class Name: " << _name.getname() << std::endl;

	// consttest
	Date date(2018, 10, 18);
	printDate(date);

	// header files search for makefile
	searchtest stest("Nothing new here");
	stest.printtest();

	// output prime number less than or equal to n
	isprime(1000, 20);
/*
#pragma omp parallel for schedule(dynamic)
	for (int i = 0; i < 1000; ++i)
	{
#pragma omp critical
		std::cout << "print to screen: " << i << "\t" << std::flush;
#pragma omp critical
		for (char j = 65; j < 97; ++j)
				std::cout << "char out: " << j << "\t "<< std::flush;
		std::cout << std::endl;
	}
*/
	return 0;
}

