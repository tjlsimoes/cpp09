#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
	try
	{
		file_readable(data, (char *)"data.csv");
		file_readable(user_file, (char *)"user_input.csv");
		db = gen_db(data);
	}
	catch(const std::exception& e)
	{
		throw std::exception();
	}
}

BitcoinExchange::BitcoinExchange(char *file_path)
{
	try
	{
		file_readable(data, (char *)"data.csv");
		file_readable(user_file, file_path);
		db = gen_db(data);
	}
	catch(const std::exception& e)
	{
		throw std::exception();
	}
}

BitcoinExchange::~BitcoinExchange()
{
	data.close();
	user_file.close();
}


void	BitcoinExchange::file_readable(std::fstream & user_file, char *file_path)
{
	user_file.open(file_path, std::ios::in);
	if (user_file.fail())
	{
		std::cerr << "Unable to open file: " << file_path << std::endl;
		throw std::exception();
	}
}

bool	BitcoinExchange::invalid_date(std::vector<int> &date)
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


bool	BitcoinExchange::validate_date(std::string &date)
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

bool	BitcoinExchange::validate_price(std::string &price)
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


float	BitcoinExchange::get_price(std::vector<std::vector<std::string> > db, std::string &date)
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

void	BitcoinExchange::read_line()
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
	}
}

std::vector<std::vector<std::string> > BitcoinExchange::gen_db(std::fstream & data)
{
	std::vector<std::vector<std::string> > db;
	std::vector<std::string>	row;
	std::string					temp;
	std::string					word;

	std::getline(data, temp);

	while (std::getline(data, temp))
	{
		row.clear();
		std::stringstream	s(temp);
		while (std::getline(s, word, ','))
			row.push_back(word);
		db.push_back(row);
	}
	return (db);
}