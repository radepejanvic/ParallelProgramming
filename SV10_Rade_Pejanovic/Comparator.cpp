#include "Comparator.h"
#include <chrono>

Comparator::Comparator(): rounds(), calculator()
{
}

Comparator::~Comparator()
{
}

void Comparator::loadRounds()
{
    std::ifstream file(INPUT_FILE);

    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    int round = 0;
    float num;

    while (file >> num) {
        std::vector<float> numbers;
        numbers.push_back(num);
        for (int i = 1; i < 7; i++) {
            file >> num;
            numbers.push_back(num);
        }
        rounds.insert(std::pair<int, std::vector<float>>(round, numbers));
        round++;
    }

    file.close();
    return;
}

void Comparator::runSerial()
{
    float expected;
    std::chrono::duration<double> duration;

    for (int round = 0; round < rounds.size(); round++) {

        calculator.clear();
        expected = rounds[round].back();
        rounds[round].pop_back();

        Computer  computer(rounds[round], expected);

        auto start = std::chrono::high_resolution_clock::now();
        computer.combinations();
        auto end = std::chrono::high_resolution_clock::now();

        duration = (end - start);
        serialize(round, duration.count(), SERIAL_FILE);

        round++;
    }
}

void Comparator::runParallel()
{
}

void serialize(int round, int time, std::string filename)
{

}
