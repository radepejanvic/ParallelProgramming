#pragma once
#include <vector>
#include <deque>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cmath>
#define MINUS 'M'
#define PLUS 'P'
#define MULTIPLY 'X'
#define DEVIDE 'I'
#define CAST 100000
#define ERROR 64420562
 
template <typename T>class Calculator { 
	std::deque<T> deque;
public: 
	Calculator();
	~Calculator();
	void initDeque(const std::vector<T> &expression);
	// calc koji racuna sumu steka
	T calc(const std::vector<T> &expression, int solution);

	T calc(const std::vector<T> &calculate);
	// calc koji racuna sumu elemenata steka dok ne naidje na operaciju <= prioriteta kao sto je prosledjena
	T calc(int priority);
	// vraca 0,1,2,3,4,-1 u zavisnosti od prioriteta
	int isOperation(T op);

	void clear();
};

#include "Calculator.tpp"