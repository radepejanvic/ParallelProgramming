#pragma once
#include "Computer.h"
#include "Record.h"
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <chrono>

class Comparator {

	std::map<int, std::vector<float>> rounds;
	Calculator<float> calculator;

public: 
	Comparator();
	~Comparator();

	void loadRounds(std::string filename);
	void runSerial();
	void runParallel();
};

void serialize(int round, double duration, std::string filename);

void filterSlow(const std::vector<float>& numbers, float result, std::string filename);