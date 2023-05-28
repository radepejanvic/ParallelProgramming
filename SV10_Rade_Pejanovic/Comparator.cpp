#include "Comparator.h"

Comparator::Comparator(): rounds(), calculator()
{
}

Comparator::~Comparator()
{
}

void Comparator::loadRounds(std::string filename)
{
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open the file: " << filename << std::endl;
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
    float calculated;
    std::chrono::duration<double> duration;

    for (int round = 0; round < rounds.size(); round++) {

        calculator.clear();
        expected = rounds[round].back();
        rounds[round].pop_back();

        Computer  computer(rounds[round], expected);

        auto start = std::chrono::high_resolution_clock::now();
        computer.combinations();
        auto end = std::chrono::high_resolution_clock::now();

        calculator.clear();
        calculated = calculator.calc(computer.solution, 0);
        std::cout << "Resenje runde " << round << " je: " << calculated << std::endl;

        duration = (end - start);
        serialize(round, duration.count(), "serial.csv");

        if (duration.count() > 20) {
            filterSlow(rounds[round], calculated, "slow.txt");
        }
    }
}

void Comparator::runParallel()
{
}

void serialize(int round, double duration, std::string filename)
{
    std::ofstream file(filename, std::ios::app);

    if (file.is_open()) {
        file << round << ',' << duration << std::endl;
        file.close();
    }
    else {
        std::cerr << "Failed to open the file." << std::endl;
    }
}

void filterSlow(const std::vector<float>& numbers, float result, std::string filename)
{
    std::ofstream outputFile(filename, std::ios::app);
    if (!outputFile) {
        std::cerr << "Failed to open the file: " << filename << std::endl;
        return;
    }

    for (const auto& number : numbers) {
        outputFile << number << ' ';
    }
    outputFile << result << std::endl;

    std::cout << "Spor: " << result << std::endl;

    outputFile.close();
}