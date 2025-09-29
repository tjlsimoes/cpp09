#include <RPN.hpp>

int main(int ac, char **av)
{
	if (ac != 2) {
		std::cerr << "Error: Invalid usage\nCorrect usage: ./RPN \"<Reverse polish notation expression>\"" << std::endl;
		return 1;
	}

	std::string input = av[1];
	if (input.empty()) {
		std::cerr << "Error: Input is empty!" << std::endl;
		return 1;
	}

	try {
		RPN app(input);
	} catch (RPN::WrongInput &e) {
		std::cout << e.what() << std::endl;
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}