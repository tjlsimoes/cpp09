// #include "BitcoinExchange.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <string>
void	valid_arg(int argc)
{
	if (argc != 2)
	{
		std::cerr << "Invalid number of arguments" << std::endl;
		std::exit(1);
	}
}

void	file_readable(std::fstream & user_file, char *file_path)
{
	user_file.open(file_path, std::ios::in);
	if (user_file.fail())
	{
		std::cerr << "Unable to open file: " << file_path << std::endl;
		std::exit(1);
	}
}

bool	invalid_date(std::vector<int> &date)
{
	if (date[1] > 12
		|| date[2] > 31
		|| (date[1] == 2 && date[2] > 29)
		|| (date[1] == 4 && date[2] > 30)
		|| (date[1] == 6 && date[2] > 30)
		|| (date[1] == 9 && date[2] > 30)
		|| (date[1] == 11 && date[2] > 30))
		return true;
	return false;
}


bool	validate_date(std::string &date)
{
	std::vector<int>	date_int;
	std::string			nbr_str;
	std::stringstream	s(date);

	while (std::getline(s, nbr_str, '-'))
	{
		date_int.push_back(std::atoi(nbr_str.c_str()));
		nbr_str.clear();
	}
	if (date_int.empty() || date_int.size() != 3 || invalid_date(date_int))
	{
		std::cerr
		<< "Error: bad input =>"
		<< date
		<< std::endl;
		return (false);
	}
	return (true);
}

bool	validate_price(std::string &price)
{
	long long price_long = std::atof(price.c_str());
	if (price_long < 0)
	{
		std::cerr
		<< "Error: not a positive number."
		<< std::endl;
		return (false);
	}
	else if (price_long > 1000)
	{
		std::cerr
		<< "Error: too large a number."
		<< std::endl;
		return (false);
	}
	return (true);
}


float	get_price(std::vector<std::vector<std::string> > db, std::string &date)
{
	for (size_t i = 0; i < db.size(); i++)
	{
		if (db[i][0].substr(0, 7) == date.substr(0, 7))
		{
			while (true)
			{
				if (atoi(db[i][0].substr(8, 2).c_str()) == atoi(date.substr(8, 2).c_str()))
					return (std::atof(db[i][1].c_str()));
				else if (i + 1 == db.size())
					return (std::atof(db[i][1].c_str()));
				else if (atoi(db[i + 1][0].substr(8, 2).c_str()) > atoi(date.substr(8, 2).c_str()))
					return (std::atof(db[i][1].c_str()));
				i++;
			}
		}
	}
	return (-1.0);
}

void	read_line(std::vector<std::vector<std::string> > db, std::fstream & user_file)
{
	std::vector<std::string>	row;
	std::string					temp;
	std::string					word;

	std::getline(user_file, temp);

	while (std::getline(user_file, temp))
	{
		row.clear();
		std::cout << temp << std::endl; ///

		std::stringstream	s(temp);

		while (std::getline(s, word, '|'))
			row.push_back(word);

		// std::cout << "|" << row[0] << "|" << std::endl;
		if (row.size() != 2 || row[0].size() < 10)		// Check this again
		{
			std::cerr << "Error: bad input => " << row[0] <<std::endl;
			continue ;
		}
		if (!validate_date(row[0]) || !validate_price(row[1]))
			continue ;
		
		std::cout << row[0] << " => " << row[1] << " = "
		<< get_price(db, row[0]) * std::atof(row[1].c_str())
		<< std::endl;
		
		// for (size_t i = 0; i < row.size(); i++)
		// {
		// 	std::cout << "i: " << i << " "  << row[i] << std::endl;
		// }
		// std::cout << std::endl;
	}
}

std::vector<std::vector<std::string> > gen_db(std::fstream & data)
{
	std::vector<std::vector<std::string> > db;
	std::vector<std::string>	row;
	std::string					temp;
	std::string					word;

	std::getline(data, temp);

	while (std::getline(data, temp))
	{
		row.clear();
		// std::cout << temp << std::endl; ///

		std::stringstream	s(temp);

		while (std::getline(s, word, ','))
			row.push_back(word);
		db.push_back(row);
	}
	return (db);
}

int	main(int argc, char **argv)
{
	std::fstream							user_file;
	std::fstream							data;
	std::vector<std::vector<std::string> >	db;

	valid_arg(argc);
	file_readable(data, (char *)"data.csv");
	file_readable(user_file, argv[1]);
	db = gen_db(data);
	read_line(db, user_file);

	// for (size_t i = 0; i < db.size(); i++)
	// {
	// 	for (size_t j = 0; j < db[i].size(); j++)
	// 	{
	// 		std::cout << "i: " << i << " "  << db[i][j] << std::endl;
	// 	}
		
	// 	std::cout << std::endl;
	// }
	// 	std::cout << std::endl;

	// while (user_file >> temp)
	// {
	// 	row.clear();

	// 	std::getline(user_file, line);

	// 	std::stringstream	s(line);

	// 	while (std::getline(s, word, '|'))
	// 		row.push_back(word);
	// }

	user_file.close();
	return (0);
}

// Check input file is valid:
	// Exists
// Check line is valid:
	// Skip first line that my equal "date | value"
	// Check that it contains |
	// Check that date has two - with digits before, in the middle and after
	// Check value to the right of | is positive and in between 0 and 1000

// For each line of the input file
	// Search matching date or the one most close to it, before
	// Multiply the associated values
