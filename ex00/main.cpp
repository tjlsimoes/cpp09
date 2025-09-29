#include <BitcoinExchange.hpp>

int main(int ac, char **av) {
	if (ac != 2) {
		std::cerr << "Error: invalid usage!\nCorrect usage: ./btc <path_to_database>" << std::endl;
		return 1;
	}

	BitcoinExchange exchange(av[1]);
	//exchange.printInMap();
	//exchange.printDbMap();

	/* try {
		exchange.run();
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	} */

	return 0;
}