#include "printtest.h"

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
	s->push("hello");
	s->push("world");
	std::cout << "strings in the quene are: " \
		      << s->pop() << " " \
			  << s->pop() << std::endl;
	delete s;
}

