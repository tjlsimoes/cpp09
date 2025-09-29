#include <PmergeMe.hpp>

int main(int ac, char **av)
{
	if (ac < 3) {

		std::cerr << "Usage: " << "./PmergeMe <integers...>" << std::endl;
		return 1;
	}

	PmergeMe sorter(2);
	try {

		for (int i = 1; i < ac; i++) {
			for (size_t j = 0; j < std::strlen(av[i]); j++) {

				if (!std::isdigit(av[i][j]))
					throw std::invalid_argument("Invalid Argument: Not a Number");
				long int num = std::atof(av[i]);
				if (num > std::numeric_limits<int>::max())
					throw std::invalid_argument("Invalid Argument: Bigger than MAX_INT");
				sorter.push(num);
			}
		}

		if (!sorter.isSorted())
			sorter.sort();
		else
			throw std::invalid_argument("Already Sorted");
	}
	catch (const std::exception &e) {

		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
}