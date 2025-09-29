#include <cstdlib>
#include <RPN.hpp>

bool isOperator(char c) {
	return c == '+' || c == '*' || c == '-' || c == '/';
}

bool	isAlpha(const std::string &str) {
	for (std::string::const_iterator it = str.begin(); it != str.end(); it++) {
		if (!isdigit(*it) && !isOperator(*it) && *it != ' ') {
			return true;
		}
	}
	return false;
}

double	run(const std::string &op, double a, double b) {
	if (op == "+")
		return a + b;
	else if (op == "*")
		return a * b;
	else if (op == "/")
		return b / a;
	else if (op == "-")
		return b - a;
	else
		throw RPN::WrongInput();
}

void	replaceWhiteSpaces(std::string &str)
{
	std::string::iterator it = str.begin();

	while (it != str.end()) {
		if (std::isspace(*it)) {
			*it = ' ';
		}
		it++;
	}
}

RPN::RPN() {}

RPN::~RPN() {}

RPN::RPN(const RPN &obj) { (void)obj; }

RPN& RPN::operator=(const RPN &obj) {
	(void)obj;
	return *this;
}

RPN::RPN(const std::string &_input) {
	std::string input = _input;
	std::string temp;
	replaceWhiteSpaces(input); // replace all whitespace for space to avoid errors

	std::stringstream var(input);
	while (std::getline(var, temp, ' ')) {
		if (isAlpha(input))
			throw WrongInput();
		else if (isdigit(temp[0])) {
			double value = std::strtod(temp.c_str(), NULL);
			// check if the number is a single digit and if it is not the pnly character in the input
			if (temp.size() == 1 && input.length() != temp.length())
				this->numbers.push(value);
			else
				throw WrongInput();
		} else if (isOperator(temp[0])) {
			double a, b;
			//check if there are enough numbers to perform the operationv
			if (this->numbers.size() < 2 && input.length() != temp.length())
				throw WrongInput();
			a = this->numbers.top();
			this->numbers.pop();
			b = this->numbers.top();
			this->numbers.pop();
			double result = run(temp, a, b);
			this->numbers.push(result);
		}
		input.erase(0, temp.length());
	}

	if (this->numbers.size() == 1)
		std::cout << "The result of the operation is: " << this->numbers.top() << std::endl;
	else
	{
		throw WrongInput();
	}
}

const char	*RPN::WrongInput::what() const throw() {
	return "Error: Invalid input!";
}