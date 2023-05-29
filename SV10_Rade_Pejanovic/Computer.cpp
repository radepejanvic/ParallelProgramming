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
        std::vector<char> v(numbers.size());
        std::fill(v.begin(), v.end() - p, 0);
        std::fill(v.end() - p, v.end(), 1);

        
        std::vector<float> combination;

        do {
            combination.clear();
            for (int i = 0; i < numbers.size(); ++i) {
                if (v[i]) {
                    combination.push_back(numbers[i]);
                }
            }
            if (parallel_variations(combination) == result) {
            }
        } while (std::next_permutation(v.begin(), v.end()));
    }
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

float Computer::parallel_variations(std::vector<float>& nums)
{
    switch (nums.size()) {
    case 2:
        return variations1(nums);
    case 3:
        return variations2(nums);
    case 4:
        return variations3(nums);
    case 5:
        return parallel_variations4(nums);
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

float Computer::parallel_variations4(std::vector<float> nums) {

    tbb::task_group g;

    int current = 0;
    bool is_found = false;

    do {
        g.run([&] { task_variations4(nums, current, is_found); });

    } while (std::next_permutation(nums.begin(), nums.end()));

    g.wait();
    
    return (current == result) ? current : -1;
}



float Computer::parallel_variations5(std::vector<float> nums) {
    std::vector<float> expression;
    // trenutni rezultat 

    int number_of_iter = 0;

    float current;
    Calculator<float> C;

    tbb::task_group g;

    do {
        for (int i = 0; i < operations.size(); i++) {
            g.run([&, i]() {
                for (int j = 0; j < operations.size(); j++) {
                    for (int k = 0; k < operations.size(); k++) {
                        for (int l = 0; l < operations.size(); l++) {
                            for (int m = 0; m < operations.size(); m++) {
                                ++number_of_iter;
                                expression.clear();
                                expression = { nums[0], operations[i], nums[1], operations[j], nums[2], operations[k], nums[3], operations[l], nums[4], operations[m], nums[5] };
                                try {
                                    C.clear();
                                    current = C.calc(expression, 0);
                                    if (current == ERROR) {
                                        continue;
                                    }
                                    else if (current == result) {
                                        std::cout << "BROJ ITERACIJA 5 -> " << number_of_iter << " RESENJE: " << current << std::endl;
                                        solution.assign(expression.begin(), expression.end());
                                        g.cancel();
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
            });
        }
        g.wait();
    } while (std::next_permutation(nums.begin(), nums.end()));
    return -1;
}

void Computer::task_variations4(std::vector<float> nums, int& current, bool& is_found)
{
    int current_result = 0;
    std::vector<float> expression;
    Calculator<float> C;
    
    for (int i = 0; i < operations.size(); i++) {
        for (int j = 0; j < operations.size(); j++) {
            for (int k = 0; k < operations.size(); k++) {
                for (int l = 0; l < operations.size(); l++) {

                    expression.clear();
                    expression = { nums[0], operations[i], nums[1], operations[j], nums[2], operations[k], nums[3], operations[l], nums[4] };
                    try {

                        if (is_found) { return; }

                        C.clear();
                        current_result = C.calc(expression, 0);
                        if (current_result == ERROR) {
                            continue;
                        }
                        else if (current_result == result) {
                            //std::cout << "BROJ ITERACIJA 4 -> " << number_of_iter << " RESENJE: " << current << std::endl;
                            solution.assign(expression.begin(), expression.end());
                            is_found = true;
                            current = current_result;
                            return;
                        }
                        else if (difference > abs(result - current_result)) {
                            if (std::fmod(current_result, 1) == 0) {
                                difference = abs(result - current_result);
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

void Computer::printSolution() {
    //std::reverse(solution.begin(), solution.end());
    for (auto a = solution.begin(); a != solution.end(); a++) {
        std::cout << *a << ' ';
    }
    std::cout << std::endl;
}
