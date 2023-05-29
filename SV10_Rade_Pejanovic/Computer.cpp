#include "Computer.h"

Computer::Computer(): numbers(0), solution(0), result(0), difference(0) {
}

Computer::Computer(const std::vector<float>& nums, float res): numbers(nums), solution(0), result(res), difference(result) {
	std::sort(numbers.begin(), numbers.end());
}

Computer::~Computer()
{
}

void Computer::combinations() {
    std::vector<bool> v(numbers.size());
    std::vector<float> combination;

    for (int p = 1; p <= numbers.size(); p++) {
        std::fill(v.begin(), v.end(), false);
        std::fill(v.end() - p, v.end(), true);
        do {
            combination.clear();
            for (int i = 0; i < numbers.size(); ++i) {
                if (v[i]) {
                    combination.push_back(numbers[i]);
                    /*std::cout << numbers[i] << ' ';*/
                }
            }
            if (variations(combination) == result) {
                return;
            }
            /*std::cout << std::endl;*/
        } while (std::next_permutation(v.begin(), v.end()));
    }
}

void Computer::parallel_combinations() {
    tbb::task_group g;

    for (int p = 1; p <= numbers.size(); p++) {
        std::vector<bool> v(numbers.size());
        std::fill(v.begin(), v.end() - p, false);
        std::fill(v.end() - p, v.end(), true);

        g.run([&]() {
            std::vector<float> combination;

            do {
                combination.clear();
                for (int i = 0; i < numbers.size(); ++i) {
                    if (v[i]) {
                        combination.push_back(numbers[i]);
                    }
                }
                if (variations(combination) == result) {
                    g.cancel();
                }
            } while (std::next_permutation(v.begin(), v.end()));
            });
    }

    g.wait();
}


float Computer::variations(std::vector<float>& nums) {
    switch (nums.size()) {
    case 2: 
        return variations1(nums);
    case 3: 
        return variations2(nums);
    case 4:
        return variations3(nums);
    case 5:
        return variations4(nums);
    case 6:
        return variations5(nums);
    default:
        return -1;
    }
    return -1;
}

float Computer::variations1(std::vector<float>& nums) {
    std::vector<float> expression;
    // trenutni rezultat 
    float current;
    Calculator<float> C;
    do {
        for (auto i = operations.cbegin(); i != operations.cend(); i++) {
            expression.clear();
            expression = { nums[0], *i, nums[1] };
            try {
                C.clear();
                current = C.calc(expression, 0);
                if (current == ERROR) {
                    continue;
                }
                else if (current == result) {
                    //std::cout << "KRAAAAJ -> " << current << std::endl;
                    solution.assign(expression.begin(), expression.end());
                    return current;
                }
                else if (difference > abs(result - current)) {
                    if (std::fmod(current, 1) == 0) {
                        difference = abs(result - current);
                        solution.assign(expression.begin(), expression.end());
                    }
                }
            }
            catch (const std::invalid_argument& e) {
                continue;
            }
        }
    } while (std::next_permutation(nums.begin(), nums.end()));
    return -1;
}

float Computer::variations2(std::vector<float>& nums) {
    std::vector<float> expression;
    // trenutni rezultat 
    float current;
    Calculator<float> C;
    do {
        for (auto i = operations.cbegin(); i != operations.cend(); i++) {
            for (auto j = operations.cbegin(); j != operations.cend(); j++) {
                expression.clear();
                expression = { nums[0], *i, nums[1], *j, nums[2]};
                try {
                    C.clear();
                    current = C.calc(expression, 0);
                    if (current == ERROR) {
                        continue;
                    }
                    else if (current == result) {
                        //std::cout << "KRAAAAJ -> " << current << std::endl;
                        solution.assign(expression.begin(), expression.end());
                        return current;
                    }
                    else if (difference > abs(result - current)) {
                        if (std::fmod(current, 1) == 0) {
                            difference = abs(result - current);
                            solution.assign(expression.begin(), expression.end());
                        }
                    }
                }
                catch (const std::invalid_argument& e) {
                    continue;
                }
            }
        }
    } while (std::next_permutation(nums.begin(), nums.end()));
    return -1;
}

float Computer::variations3(std::vector<float>& nums) {
    std::vector<float> expression;
    // trenutni rezultat 
    float current;
    Calculator<float> C;
    do {
        for (auto i = operations.cbegin(); i != operations.cend(); i++) {
            for (auto j = operations.cbegin(); j != operations.cend(); j++) {
                for (auto k = operations.cbegin(); k != operations.cend(); k++) {
                    expression.clear();
                    expression = { nums[0], *i, nums[1], *j, nums[2], *k, nums[3] };
                    try {
                        C.clear();
                        current = C.calc(expression, 0);
                        if (current == ERROR) {
                            continue;
                        }
                        else if (current == result) {
                            //std::cout << "KRAAAAJ -> " << current << std::endl;
                            solution.assign(expression.begin(), expression.end());
                            return current;
                        }
                        else if (difference > abs(result - current)) {
                            if (std::fmod(current, 1) == 0) {
                                difference = abs(result - current);
                                solution.assign(expression.begin(), expression.end());
                            }
                        }
                    }
                    catch (const std::invalid_argument& e) {
                        continue;
                    }
                }
            }
        }
    } while (std::next_permutation(nums.begin(), nums.end()));
    return -1;
}

float Computer::variations4(std::vector<float>& nums) {
    std::vector<float> expression;
    // trenutni rezultat 

    int number_of_iter = 0;

    float current;
    Calculator<float> C;
    do {
        for (auto i = operations.cbegin(); i != operations.cend(); i++) {
            for (auto j = operations.cbegin(); j != operations.cend(); j++) {
                for (auto k = operations.cbegin(); k != operations.cend(); k++) {
                    for (auto l = operations.cbegin(); l != operations.cend(); l++) {
                       
                        ++number_of_iter;

                        expression.clear();
                        expression = { nums[0], *i, nums[1], *j, nums[2], *k, nums[3], *l, nums[4] };
                        try {
                            C.clear();
                            current = C.calc(expression, 0);
                            if (current == ERROR) {
                                continue;
                            }
                            else if (current == result) {
                                std::cout << "BROJ ITERACIJA 4 -> " << number_of_iter << " RESENJE: " << current << std::endl;
                                solution.assign(expression.begin(), expression.end());
                                return current;
                            }
                            else if (difference > abs(result - current)) {
                                if (std::fmod(current, 1) == 0) {
                                    difference = abs(result - current);
                                    solution.assign(expression.begin(), expression.end());
                                }
                            }
                        }
                        catch (const std::invalid_argument& e) {
                            continue;
                        }
                    }
                }
            }
        }
    } while (std::next_permutation(nums.begin(), nums.end()));
    return -1;
}

float Computer::variations5(std::vector<float>& nums) {
    std::vector<float> expression;
    // trenutni rezultat 

    int number_of_iter = 0;

    float current;
    Calculator<float> C;
    do {
        for (auto i = operations.cbegin(); i != operations.cend(); i++) {
            for (auto j = operations.cbegin(); j != operations.cend(); j++) {
                for (auto k = operations.cbegin(); k != operations.cend(); k++) {
                    for (auto l = operations.cbegin(); l != operations.cend(); l++) {
                        for (auto m = operations.cbegin(); m != operations.cend(); m++) {
                            ++number_of_iter;
                            expression.clear();
                            expression = { nums[0], *i, nums[1], *j, nums[2], *k, nums[3], *l, nums[4], *m, nums[5] };
                            try {
                                C.clear();
                                current = C.calc(expression, 0);
                                if (current == ERROR) {
                                    continue;
                                }
                                else if (current == result) {
                                    std::cout << "BROJ ITERACIJA 5 -> " << number_of_iter << " RESENJE: " << current << std::endl;
                                    solution.assign(expression.begin(), expression.end());
                                    return current;
                                }
                                else if (difference > abs(result - current)) {
                                    if (std::fmod(current, 1) == 0) {
                                        difference = abs(result - current);
                                        solution.assign(expression.begin(), expression.end());
                                    }
                                }
                            }
                            catch (const std::invalid_argument& e) {
                                continue;
                            }
                        }
                    }
                }
            }
        }
    } while (std::next_permutation(nums.begin(), nums.end()));
    return -1;
}

void Computer::printSolution() {
    //std::reverse(solution.begin(), solution.end());
    for (auto a = solution.begin(); a != solution.end(); a++) {
        std::cout << *a << ' ';
    }
    std::cout << std::endl;
}
