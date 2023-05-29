#pragma once
#include "Calculator.h"
#include <string>
#include <tbb/tbb.h>
#include <tbb/task_group.h>
#include <tbb/concurrent_vector.h>


class Computer {
public:
	std::vector<float> operations = { '+' + CAST, '-' + CAST, '*' + CAST, '/' + CAST, PLUS + CAST, MINUS + CAST, MULTIPLY + CAST, DEVIDE + CAST };
	//tbb::concurrent_vector<float> parallel_operations = { '+' + CAST, '-' + CAST, '*' + CAST, '/' + CAST, PLUS + CAST, MINUS + CAST, MULTIPLY + CAST, DEVIDE + CAST };
	std::vector<float> numbers;
	std::vector<float> solution;
	float result;
	float difference;

	Computer();
	Computer(const std::vector<float>& nums, float res);
	~Computer();
	
	// generisanje svih kombinacija bez ponavljanja nad skupom vrednosti
	// broj pozicija kombinacije -> p = {1,...,6}
	// pomocni vector v -> sadrzi bool vrednosti jer se skup brojeva bijektivno slika u skup {true, false}
	// prema principu bijekcije -> broj permutacija skupa {0,...0,1...1} = broju kombinacija sa ponavljanjem skupa brojeva
	// 0 -> predstavlja false, 1 -> predstavlja true u ovom zapisu, u kodu se koriste bool vrednosti
	void combinations();

	void parallel_combinations();

	// generisanje svih varijacija sa ponavljanjem skupa operacija na i = {1,...,5} pozicija
	// generisanje svih permutacija vektora nums u svakoj iteraciji generisanja pojedinacne varijacije operacija
	// racunanje vrednosti izraza -> ukoliko se naidje na tacan, odnosno na onaj koji je jednak 'result' promenljivoj
	// prekidaju se sve funckije i zapisuje se u promenljivu solution
	float variations(std::vector<float>& nums);

	float parallel_variations(std::vector<float>& nums);
	// generisanje varijacija sa ponavljanjem skupa operacija na 1 poziciji
	float variations1(std::vector<float>& nums);
	// generisanje varijacija sa ponavljanjem skupa operacija na 2 poziciji
	float variations2(std::vector<float>& nums);
	// generisanje varijacija sa ponavljanjem skupa operacija na 3 poziciji
	float variations3(std::vector<float>& nums);
	// generisanje varijacija sa ponavljanjem skupa operacija na 4 poziciji
	float variations4(std::vector<float>& nums);
	// generisanje varijacija sa ponavljanjem skupa operacija na 5 poziciji
	float variations5(std::vector<float>& nums);

	float parallel_variations1(std::vector<float> nums);

	void task_variations1(std::vector<float> nums, int& current, bool& is_found);

	float parallel_variations2(std::vector<float> nums);

	void task_variations2(std::vector<float> nums, int& current, bool& is_found);

	float parallel_variations4(std::vector<float> nums);

	float parallel_variations5(std::vector<float> nums);

	float task_variations4(std::vector<float> nums);


	void printSolution();

	//std::string toString();

};

//#include "Computer.cpp"