#pragma once
#include "Computer.h"
#include "Record.h"
#include <map>
#include <fstream>
#include <sstream>

#define INPUT_FILE "expressions.txt"
#define SERIAL_FILE "serial.csv"
#define PARALLEL_FILE "parallel.csv"

class Comparator {

	std::map<int, std::vector<float>> rounds;
	Calculator<float> calculator;

public: 
	Comparator();
	~Comparator();

	void loadRounds();
	void runSerial();
	void runParallel();
};

void serialize(int time);