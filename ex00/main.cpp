#include "BitcoinExchange.hpp"

void	valid_arg(int argc)
{
	if (argc != 2)
	{
		std::cerr << "Invalid number of arguments" << std::endl;
		std::exit(1);
	}
}

int	main(int argc, char **argv)
{
	valid_arg(argc);

	try
	{
		BitcoinExchange program;
		(void )argv;
		program.read_line();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: Unable to generate db. Exiting." << '\n';
		return (1);
	}

	try
	{
		BitcoinExchange program_b((char *)"./user_input.csv");
		program_b.read_line();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: Unable to generate db. Exiting." << '\n';
		return (1);
	}
	return (0);
}
