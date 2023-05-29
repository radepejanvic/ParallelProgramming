#include "Game.h"

Game::Game() : round(1), rounds(), ifile("Test.txt"), ofile("Rezultati.txt"), C(), records() {

}

Game::Game(std::string iF): round(1), rounds(), ifile(iF), ofile("Rezultati.txt"), C(), records() {
}

Game::~Game()
{
}

void Game::loadRounds() {
    std::ifstream file(ifile);

    // Check if the file was opened successfully
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }
    int round = 1;
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
    round = 1;
    file.close();
    return;
}

void Game::printRounds()
{
    for (auto i = rounds.begin(); i != rounds.end(); i++) {
        std::cout << "Runda: " << i->first << " -> ";
        for (auto j = i->second.begin(); j != i->second.end(); j++) {
            if (j == i->second.end() - 1) {
                std::cout << "\nTrazeno resenje: " << *j << std::endl;
                continue;
            }
            std::cout << *j << " ";
        }
    }
}

void Game::printRound(int rnd)
{   
    std::cout << "Runda: " << rnd << " -> ";
    for (auto i = rounds[rnd].begin(); i != rounds[rnd].end(); i++) {
        if (i == rounds[rnd].end() - 1) {
            std::cout << "\nTrazeno resenje: " << *i << std::endl;
            std::cout << "----------------------------" << std::endl;
            continue;
        }
        std::cout << *i << " ";
    }

}

void Game::printStart() {
    std::cout << "----------MOJ BROJ----------" << std::endl;
    std::cout << "| >>operacije:             |" << std::endl;
    std::cout << "| + -                      |" << std::endl;
    std::cout << "| * /                      |" << std::endl;
    std::cout << "| P -> 'a P b' = (a + b)   |" << std::endl;
    std::cout << "| M -> 'a M b' = (a - b)   |" << std::endl;
    std::cout << "| X -> 'a X b' = (a * b)   |" << std::endl;
    std::cout << "| I -> 'a I b' = (a / b)   |" << std::endl;
    std::cout << "----------------------------" << std::endl;
}

void Game::readExpression(std::vector<float>& expression)
{
    std::string line;
    while (true) {
        try {
            expression.clear();
            std::cout << "\t>> ";
            std::getline(std::cin, line);
            expression = check(line);
            break;
        }
        catch (const std::invalid_argument& e) {
            std::cout << e.what() << std::endl;
            std::cout << "Ponovite unos: " << std::endl;
        }
    }
    return;
}

void Game::computerSolution(std::vector<float>& solution){
    C.clear();
    float res = rounds[round].back();
    rounds[round].pop_back();
    int result;
    Computer comp(rounds[round], res);
    comp.combinations();
    std::cout << "Nase resenje: " << std::endl;
    std::cout << "\t>> ";
    result = C.calc(comp.solution, 0);
    std::reverse(comp.solution.begin(), comp.solution.end());
    solution = convertToBrackets(comp.solution);
    
    std::cout << toString(solution) << " = ";
    std::cout << result << std::endl;
    std::cout << "----------------------------" << std::endl;
    rounds[round].push_back(res);
}

float Game::playerTurn(char player, std::vector<float> &expression)
{
    float result;
    C.clear();
    std::cout << "Igrac " << player << " je na potezu:" << std::endl;
    readExpression(expression);
    result = C.calc(expression, 0);
    std::cout << "Vase resenje je: " << result << std::endl;
    return result;
}

bool Game::continuePlaying()
{   
    std::cout << " Da li zelite da nastavite sa igranjem? " << std::endl;
    std::cout << "\t 1) Da \t 2) Ne" << std::endl;
    std::cout << "\t >> ";
    int input;
    std::cin >> input;
    while (input != 1 && input != 2) {
        if (std::cin.fail()) {
            std::cin.clear();
            //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "-- neispravan unos --" << std::endl;
        std::cout << "\t >> ";
        std::cin >> input;
    }
    std::cout << "----------------------------" << std::endl;
    switch (input) {
    case 1:
        return true;
    case 2:
        return false;
    }
    return false;
}

void Game::getWinner(Record &R) {
    if (R.winner == ' ') {
        if (abs(R.diff1) <= abs(R.diff2)) {
            if (round % 2 == 0) {
                R.winner = 'B';
            }
            R.winner = 'A';
        }
        if (round % 2 == 0) {
            R.winner = 'A';
        }
        R.winner = 'B';
    }
}

void Game::writeRecords() {
    char winner; 
    int A = 0;
    int B = 0;
    std::ofstream outfile;

    // Open the file for writing
    outfile.open(ofile, std::ios_base::app);

    // Check if the file was successfully opened
    if (!outfile) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }

    for (auto i = records.begin(); i != records.end(); i++) {
        switch ((*i).winner) {
        case 'A':
            A++;
            break;
        case 'B':
            B++;
            break;
        }
        outfile << *i << std::endl;
    }
    if (A > B) {
        winner = 'A';
    }
    else if ( A < B) {
        winner = 'B';
    }
    else {
        winner = '/';
    }
    outfile << "------------------------------------------------------------------------------------------" << std::endl;
    outfile << "Takmicar A: " << std::to_string(A) << " Takmicar B: " << std::to_string(B) << " Pobednik: " << winner << std::endl;
    outfile << "------------------------------------------------------------------------------------------" << std::endl;


    outfile.close();

    return;
}

void Game::play()
{   
    loadRounds();
    //printRounds();
    printStart();
    //std::cout<< "'a X b M c P d * e - f' = (a*b-c+d)*e-f" << std::endl;
    char player;
    float result1;
    float result2;
    std::vector<float> expression;
    std::vector<float> solution;
    for (auto rnd = rounds.begin(); rnd != rounds.end(); rnd++) {

        result1 = rounds[round].back();
        rounds[round].pop_back();
        Record R(round, rounds[round], result1);
        rounds[round].push_back(result1);
        
        if (rnd->first % 2 == 1) {
            player = 'A';
        }
        else {
            player = 'B';
        }
        printRound(rnd->first);
        
        result1 = playerTurn(player, expression);
        R.player1 = result1;
        R.diff1 = rounds[round].back() - result1;
        std::reverse(expression.begin(), expression.end());
        R.solution1 = convertToBrackets(expression);

        if (result1 == rounds[round].back()) {
            std::cout << "Pobdenik je igrac: " << player << std::endl;
            R.winner = player;
            // dodati upitnik da li zele da nastave sa igranjem
        }
        else {
            expression.clear();
            switch (player) {
            case 'A':
                player = 'B';
                break;
            case 'B': 
                player = 'A';
                break;
            }
            std::cout << "Protivnik nije uspeo da nadje tacno resenje" << std::endl;
            result2 = playerTurn(player, expression);

            R.player2 = result2;
            R.diff2 = rounds[round].back() - result2;
            std::reverse(expression.begin(), expression.end());
            R.solution2 = convertToBrackets(expression);

            if (result2 == rounds[round].back()) {
                std::cout << "Pobdenik je igrac: " << player << std::endl;
                R.winner = player;
                // dodati upitnik da li zele da nastave sa igranjem
            }
        }
        
        getWinner(R);

        computerSolution(solution);
        //std::reverse(solution.begin(), solution.end());
        R.solution = solution;

        round++;
        records.push_back(R);

        if (!continuePlaying()) {
            break;
        }
    }
    std::cout << "---------KRAJ IGRE----------" << std::endl;
    writeRecords();
    
}

std::vector<float> Game::check(std::string line)
{
    std::vector<float> expression;
    std::vector<std::string> elements = split(line, ' ');
    float num;
    float result = rounds[round].back();
    rounds[round].pop_back();

    if (elements.size() % 2 == 0 || elements.size() > 11) {
        rounds[round].push_back(result);
        throw std::invalid_argument("Unos nepotpun");
        expression.clear();
        return expression;
    } 

    for (int i = 0; i < elements.size(); i++) {
        if (i % 2 == 1) {
            if (operation(elements[i]) == -1) {
                rounds[round].push_back(result);
                throw std::invalid_argument("Nedostaje operacija");
                expression.clear();
                return expression;
            }
            expression.push_back(operation(elements[i]) + CAST);
            continue;
        }
        num = stof(elements[i]);
        if (std::find(rounds[round].begin(), rounds[round].end(), num) == rounds[round].end()) {
            rounds[round].push_back(result);
            throw std::invalid_argument("Broj se ne nalazi u ponudjenim");
            expression.clear();
            return expression;
        }
        if (std::find(expression.begin(), expression.end(), num) != expression.end()) {
            rounds[round].push_back(result);
            throw std::invalid_argument("Broj je vec upotrebljen");
            expression.clear();
            return expression;
        }

        expression.push_back(num);
        
    }
    rounds[round].push_back(result);
    std::reverse(expression.begin(), expression.end());
    return expression;
}

std::vector<std::string> split(const std::string &str, char delimiter)
{
    std::vector<std::string> elements;
    std::stringstream ss(str);
    std::string element;
    while (std::getline(ss, element, delimiter)) {
        elements.push_back(element);
    }
    return elements;
}

float operation(std::string str) {
    if (str.length() != 1) {
        return -1;
    }
    switch (str[0]) {
    case '+':
        return '+';
    case '-':
        return '-';
    case '*':
        return '*';
    case '/':
        return '/';
    case 'P':
        return 'P';
    case 'M':
        return 'M';
    case 'X':
        return 'X';
    case 'I':
        return 'I';
    default:
        return -1;
    }
    return -1;
}
std::vector<float> convertToBrackets(const std::vector<float>& expression)
{
    Calculator<float> C;
    bool open = false;
    std::vector<float> newExp;
    int index;
    for (auto i = expression.begin(); i != expression.end(); i++) {
        if (C.isOperation(*i) == -1) {
            newExp.push_back(*i);
        }
        else if (C.isOperation(*i) > 1) {
            if (!open) {
                index = newExp.size() - 1;
                newExp.insert(newExp.begin() + index, '(' + CAST);
                open = true;
            }
            newExp.push_back(specToBasic(*i));
        }
        else if (C.isOperation(*i) == 0 || C.isOperation(*i) == 1) {
            if (open) {
                index = newExp.size() - 1;
                newExp.push_back(')' + CAST);
                open = false;
            }
            newExp.push_back(*i);
        }
    }
    if (open) {
        newExp.push_back(')' + CAST);
    }
    return newExp;
}
float specToBasic(float spec)
{
    switch ((int)spec - CAST) {
    case 'P':
        return '+' + CAST;
    case 'M':
        return '-' + CAST;
    case 'X':
        return '*' + CAST;
    case 'I':
        return '/' + CAST;
    default: 
        return - 1;
    }
    return -1;
};
