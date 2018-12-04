#include "printtest.h"
#include <cmath>

void printDate(const Date& date) {
	std::cout << date.getYear() << "/"
			  << date.getMonth() << "/"
			  << date.getDay() << "/"
			  << std::endl;
}

std::string thistest::getname() {
		this->name = "iamhere";
		return this->name;
}

void printtest::add(){
	size_t tmp = x + y;
	std::cout << "x = " << x << std::endl;
	std::cout << "y = " << y << std::endl;
	std::cout << "x + y = " << tmp << std::endl;
}

void fun1(void) {
	Quene<int> *que = new Quene<int>();
	que->push(110);
	que->push(211);
	std::cout << "Values in the quene are: "\
			  << que->pop() << " "\
			  << que->pop() << std::endl;
	delete que;
}

void fun2(void) {
	Quene<std::string> *s = new Quene<std::string>();
	s->push("world");
	s->push("hello");
	std::cout << "strings in the quene are: " \
		      << s->pop() << " " \
			  << s->pop() << std::endl;
	delete s;
}

void isprime(int n, const int NUMBER_PER_LINE) {
		int count = 0;
		int number = 2;

		while (number <= n) {
			bool isPrime = true;
			int squareroot = (int) sqrt(number * 1.0);
			for (int divisor = 2; divisor <= squareroot; divisor++) {
				if (number % divisor == 0) {
						isPrime = false;
						break;
				}
			}
			if (isPrime) {
					count++;
					if (count % NUMBER_PER_LINE == 0) {
							std::cout << number << std::endl;
					}
					else {
							std::cout << number << " ";
					}
			}
			number++;
		}
		std::cout << "\n" << count << " number of primes <=" << n << std::endl;
}

