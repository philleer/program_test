#ifndef PRINTTEST_H
#define PRINTTEST_H

#include <iostream>
#include <vector>
#include <iterator>

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

template<typename ForwardIterator> 
void square(ForwardIterator first, ForwardIterator last);

#endif /* ifndef PRINTTEST_H */
