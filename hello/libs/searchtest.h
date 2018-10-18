#ifndef _SEARCHTEST_H_
#define _SEARCHTEST_H_ 

#include <iostream>
#include <string>

class searchtest
{
public:
	searchtest(std::string _str): str(_str) {};
	virtual ~searchtest();
	void printtest() const;

private:
	std::string str;
};

#endif /* ifndef _SEARCHTEST_H_ */
