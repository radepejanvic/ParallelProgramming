#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include "Calculator.h"
class Record {

public:
	int round;
	std::vector<float> numbers;
	float result;
	float player1;
	float player2;
	float diff1;
	float diff2;
	std::vector<float> solution1;
	std::vector<float> solution2;
	char winner;
	std::vector<float> solution;
 
	Record();
	Record(int rnd, std::vector<float> nums, float res);
	~Record();

	friend std::ostream& operator<<(std::ostream& os, const Record& record);
};
std::string toString(std::vector<float> expression);