#ifndef PRINTTEST_H
#define PRINTTEST_H

#include <iostream>
#include <string>

class printtest
{
public:
	printtest(size_t xi, size_t yi):x(xi), y(yi){};
	virtual ~printtest(){
			std::cout << "Deconstruct!" << std::endl;
	};
	void add();

private:
	size_t x;
	size_t y;
};

#endif /* ifndef PRINTTEST_H */
