#ifndef PRINTTEST_H
#define PRINTTEST_H

#include <iostream>
#include <vector>
#include <iterator>

#define TEST_NAMESPACE_BEGIN namespace test {
#define TEST_NAMESPACE_END }

class Date
{
public:
	Date(int year, int month, int day) {
		setDate(year, month, day);
	}

	void setDate(int year, int month, int day) {
		m_year = year;
		m_month = month;
		m_day = day;
	}

	int getYear() const { 
		return m_year;
	}
	int getMonth() const {
		return m_month;
	}
	int getDay() const {
		return m_day;
	}

private:
	int m_year;
	int m_month;
	int m_day;
};

class thistest
{
public:
	thistest(std::string str):name(str) {};
	~thistest() {
		std::cout << "thistest deconstruct!" << std::endl;
	};
	std::string getname();

private:
	std::string name;
};

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
void square(ForwardIterator first, ForwardIterator last) {
		std::cout << "  Square: ";
		for ( ; first != last; first++ ) {
				*first = (*first) * (*first);
				std::cout << *first << " ";
		}
		std::cout << std::endl;
}

// Quene -- Template declaration
template<typename T>
class Quene {
public:
	Quene();
	~Quene();
	void push(T e);
	T pop();

private:
	struct node {
		T data;
		node* next;
	};
	typedef node NODE;
	NODE* mHead;
};

// Quene -- Template definition
template<typename T>
Quene<T>::Quene() {
	mHead = NULL;
}

template<typename T>
Quene<T>::~Quene() {
	NODE* tmp;
	while (mHead) {
		tmp = mHead;
		mHead = mHead->next;
		delete tmp;
	}
}

template<typename T>
void Quene<T>::push(T e) {
	NODE *ptr = new node;
	ptr->data = e;
	ptr->next = NULL;
	if (mHead == NULL) {
		mHead = ptr;
		return;
	}
	NODE *cur = mHead;
	while (cur) {
		if (cur->next == NULL) {
			cur->next = ptr;
			return;
		}
		cur = cur->next;
	}
}

template<typename T>
T Quene<T>::pop() {
	if (mHead == NULL) {
		return NULL;
	}
	NODE *tmp = mHead;
	T d = mHead->data;
	mHead = mHead->next;
	delete tmp;
	return d;
}

void fun1();
void fun2();

void printDate(const Date& date);
#endif /* ifndef PRINTTEST_H */
