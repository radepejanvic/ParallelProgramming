#include "Calculator.h"

// kada ovo pocne da se brise znas da si dosao do kraja undo-a

template <typename T>Calculator<T>::Calculator(): deque(0) {
}

template <typename T>Calculator<T>::~Calculator() {
}

template <typename T> void Calculator<T>::initDeque(const std::vector<T>& expression){
	std::vector<T> calculate;
	T result;
	T top;
	int priority;
	deque.clear();
	for (auto c = expression.cbegin(); c != expression.cend(); c++) {
		if (isOperation(*c) == -1 || deque.size() < 3)  {
			deque.push_back(*c);
		}
		else {
			// top je u ovom trenutku poslednji operand
			// deque_pop da bi se doslo do poslednje operacije
			T top = deque.back();
			deque.pop_back();
			priority = isOperation(*c);
			if (isOperation(deque.back()) > isOperation(*c)) {
				// povlaci poslednja 3 elementa sa steka racuna izraz i vraca ga nazad na stek
				deque.push_back(top);
				try {
					result = calc(isOperation(*c));
					if (result == (T)ERROR) {
						throw std::invalid_argument("Neispravna vrednost");
					}
					// vracanje izracunatog izraza na stek i dodavanje naredno ucitanog elementa(operacije)
					deque.push_back(*c);
				} catch (const std::invalid_argument& e) {
					deque.clear();
					return;
				}
			}
			else {
				// vracanje prethodno skinutog elementa radi poredjenja 
				deque.push_back(top);
				deque.push_back(*c);
			}
		}
	}
	return;
}
// -1 -> za neispravan izraz
template <typename T> T Calculator<T>::calc(const std::vector<T> &calculate)
{
	T num1 = calculate[2];
	int op = (int)calculate[1];
	T num2 = calculate[0];
	// |deque|num1|op|num2| -> posto se elementi ucitavaju u obrnutom redosledu
	// pretpostavka je da su num1 i num2 pozitivni celi brojevi
	switch (op - CAST) {
	case '+': case PLUS:
		return num1 + num2;
	case '-': case MINUS:
		return num2 - num1;
	case '*': case MULTIPLY:
		return num1 * num2;
	case '/': case DEVIDE:
		return num2 / num1;
	default: 
		return (T)ERROR;
	}
}

template <typename T> int Calculator<T>::isOperation(T op)
{
	// / 100 -> jer su operatori reprezentovani kao ascii(op)*100
	switch ((int)op-CAST) {
	case '+': case '-': 
		return 0;
	case '*':case '/':
		return 1;
	// sabiranje i oduzimanje sa zagradama -> najveceg prioriteta
	case MINUS: case PLUS:
		return 2;
	case MULTIPLY: case DEVIDE:
		return 3;
	case '(': case ')':
		return -2;
	default:
		return -1;
	}
	return -1;
}

template <typename T> void Calculator<T>::clear() {
	deque.clear();
}

// calc ali u nazad
template <typename T> T Calculator<T>::calc(const std::vector<T>& expression, int solution)
{
	// poziva initdeque -> kako bi formirao deque
	// racuna izraz tako sto povlaci element po element sa steka 
	initDeque(expression);
	calc(0);
	if (!deque.empty()) {
		return deque.back();
	}
	return (T)ERROR;
}


// EKSPERIMENTALNI -> treba da radi isto sto i ovaj calc koji poziva initdeque u sebi
template <typename T> T Calculator<T>::calc(int priority)
{
	// poziva initdeque -> kako bi formirao deque
	// racuna izraz tako sto povlaci element po element sa steka 

	std::vector<T> calculate;
	T result;
	T top;
	// dok na steku ne ostane jedan element -> taj element je resenje izraza
	while (!deque.empty()) {
		try {
			if (deque.size() == 1) {
				return deque.back();
			}
			top = deque.back();
			deque.pop_back();
			if (isOperation(deque.back()) < priority) {
				deque.push_back(top);
				return top;
			}
			deque.push_back(top);

			for (int i = 0; i < 3; i++) {
				calculate.push_back(deque.back());
				deque.pop_back();
			}
			result = calc(calculate);
			if (result == (T)ERROR) {
				deque.clear();
				throw std::invalid_argument("Neispravna vrednost");
			}
			deque.push_back(result);
			calculate.clear();
		}
		catch (const std::invalid_argument& e) {
			//std::cout << "Neispravan izraz: " << e.what() << std::endl;
			return (T)ERROR;
		}
	}
	return (T)ERROR;
}