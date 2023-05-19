#include "Record.h"

Record::Record(): round(0), numbers(0), result(0), player1(0), player2(0), diff1(0), diff2(0), solution1(0), solution2(0), winner(0), solution(0){

}

Record::Record(int rnd, std::vector<float> nums, float res): round(rnd), numbers(nums), result(res), player1(0), player2(0), diff1(0), diff2(0), solution1(0), solution2(0), winner(' '), solution(0) {
}

Record::~Record()
{
}



std::ostream& operator<<(std::ostream& os, const Record& record)
{
	os << record.round << '|' << toString(record.numbers) << '|' << record.result << '|' << record.player1 << '|' << record.player2 << '|' << record.diff1 << '|' << record.diff2 << '|' << toString(record.solution1) << '|' << toString(record.solution2) << '|' << record.winner << '|' << toString(record.solution);
	return os;
}

std::string toString(std::vector<float> expression) {
    Calculator<float> C;
    std::string out = "";
    char op;
    for (auto i = expression.begin(); i != expression.end(); i++) {
        if (C.isOperation(*i) != -1) {
            op = ((int)*i - CAST);
            out += ' ';
            out += op;
            continue;
        }
        out += ' ';
        out += std::to_string((int)*i);
    }
    return out;
}
