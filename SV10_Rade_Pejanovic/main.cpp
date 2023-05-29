//#include "Computer.h"
#include "Game.h"
#include "Comparator.h"
//#include "Calculator.h"

std::string pickInputFile() {	
	std::string filename;
	std::ifstream file;

	while (!file.is_open()) {
		std::cout << "Unesite putanju datoteke sa primerima: ";
		std::cin >> filename;
		if (filename.empty()) {
			return "Test.txt";
		}

		file.open(filename);
		if (!file.is_open()) {
			std::cout << "Neispravno ime fajla. Pokusajte ponovo." << std::endl;
		}
	}
	file.close();
	return filename;
}

int main() {
	/*std::string filename = pickInputFile();
	Game g(filename);
	g.play();*/

	Comparator comparator;
	comparator.loadRounds("tester.txt");
	//comparator.runSerial();
	comparator.runParallel();
}