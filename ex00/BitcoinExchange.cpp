/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 11:02:29 by tjorge-l          #+#    #+#             */
/*   Updated: 2026/01/12 11:02:37 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() : _inputFilename("")
{}

BitcoinExchange::BitcoinExchange(const std::string & inputFilename) : _inputFilename(inputFilename)
{
	_loadDatabase();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange & other) : _inputFilename(other._inputFilename), _database(other._database)
{}

BitcoinExchange::~BitcoinExchange()
{}

void	BitcoinExchange::run() const
{
	if (_inputFilename.empty())
	{
		std::cerr << "Error: no input file provided." << std::endl;
		return ;
	}
	_processInput();
}

std::string	BitcoinExchange::_trim(const std::string &str)
{
	size_t	first = str.find_first_not_of(" \t");
	if (first == std::string::npos)
		return "";
	size_t last = str.find_last_not_of(" \t");
	return str.substr(first, last - first + 1);
}

void	BitcoinExchange::_loadDatabase()
{
	std::ifstream	file("data.csv");
	if (!file.is_open())
		throw std::runtime_error("could not open data.csv");

	std::string	line;
	std::getline(file, line); // skip header

	while(std::getline(file, line))
	{
		size_t commaPos = line.find(',');
		if (commaPos == std::string::npos)
			continue ;
		std::string date = _trim(line.substr(0, commaPos));
		std::string priceStr = _trim(line.substr(commaPos + 1));

		float price = static_cast<float>(std::atof(priceStr.c_str()));
		_database.push_back(std::make_pair(date, price));
	}
	file.close();
}

bool	BitcoinExchange::_isValidDate(const std::string &date) const
{
	std::stringstream ss(date);
	int year, month, day;
	char sep1, sep2;

	if (!(ss >> year >> sep1 >> month >> sep2 >> day) 
		|| sep1 != '-' || sep2 != '-' 
		|| !ss.eof())
		return false;

	if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
		return false;
	
	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
		return false;
	if (month == 2 && day > 29)
		return false;

	(void)year;
	return true;
}

bool	BitcoinExchange::_isValidValue(const std::string & valueStr, float &value) const
{
	char	*endptr;
	value = static_cast<float>(std::strtod(valueStr.c_str(), &endptr));

	if (endptr == valueStr.c_str() || *endptr != '\0')
	{
		std::cerr << "Error: not a valid number." << std::endl;
		return false;
	}
	if (value < 0)
	{
		std::cerr << "Error: not a positive number." << std::endl;
		return false;
	}
	if (value > 1000)
	{
		std::cerr << "Error: too large a number." << std::endl;
		return false;
	}
	return true;
}

float	BitcoinExchange::_findClosestPrice(const std::string & targetDate) const
{
	std::list<std::pair<std::string, float> >::const_iterator it;
	std::list<std::pair<std::string, float> >::const_iterator best = _database.end();

	for (it = _database.begin(); it != _database.end(); it++)
	{
		if (it->first > targetDate)
		{
			if (it == _database.begin())
				best = it;
			break ;
		}
		best = it;
	}
	return best->second;	
}

void	BitcoinExchange::_processInput() const
{
	std::ifstream	input(_inputFilename.c_str());
	if (!input.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return ;
	}

	std::string line;
	std::getline(input, line);	// Skip header

	while (std::getline(input, line))
	{
		size_t	pipePos = line.find('|');
		if (pipePos == std::string::npos)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue ;
		}

		std::string	dateStr = _trim(line.substr(0, pipePos));
		std::string valueStr = _trim(line.substr(pipePos + 1));
		if (dateStr.empty() || valueStr.empty())
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue ;
		}
		if (!_isValidDate(dateStr))
		{
			std::cerr << "Error: bad input => " << dateStr << std::endl;
			continue ;
		}

		float value;
		if (!_isValidValue(valueStr, value))
			continue ;

		float rate = _findClosestPrice(dateStr);
		std::cout << dateStr << " => " << value << " = " << (value * rate) << std::endl;
	}
	input.close();
}