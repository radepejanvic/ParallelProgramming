#pragma once
#include "Computer.h"
#include "Record.h"
#include <map>
#include <fstream>
#include <sstream>

class Game {
	int round;
	std::map<int, std::vector<float>> rounds;
	std::string ifile;
	std::string ofile;
	Calculator<float> C;
	std::vector<Record> records;
public: 
	Game();
	Game(std::string iF);
	~Game();

	void loadRounds();
	void printRounds();
	void printRound(int rnd);
	void printStart();
	void readExpression(std::vector<float> &expression);
	void computerSolution(std::vector<float> &solution);
	float playerTurn(char player, std::vector<float> &expression);
	bool continuePlaying();
	void getWinner(Record &R);

	void play();
	std::vector<float> check(std::string line);

	void writeRecords();
};

std::vector<std::string> split(const std::string &str, char delimiter);
float operation(std::string str);
std::vector<float> convertToBrackets(const std::vector<float> &expression);
float specToBasic(float spec);


