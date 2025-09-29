#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <map>
#include <exception>
#include <limits>
#include <cstdlib>
#include <ctime>

class CannotOpenFile : public std::exception {
	public:
		const char *what() const throw();
};

class InvalidFile : public std::exception {
public:
	const char *what() const throw();
};
	

class Date;
class BitcoinExchange
{
	public:
		BitcoinExchange( const std::string &inFile );
	  	~BitcoinExchange();

		void	run( void );
		void 	printDbMap();
		void 	printInMap();

	private:
		std::string	_dbFile;
		std::string _inFile;
		std::multimap<Date, double> _dbMap;
		std::multimap<Date, double> _inMap;


		void 	mapInit(const std::string &filePath);
		bool 	headerCheck(const std::string &line);
		bool 	parseLine(const std::string &line);
		bool 	isValidContent(const std::string &dateStr, const std::string &valueStr, char delim);



		BitcoinExchange();
		BitcoinExchange( const BitcoinExchange &obj );
		BitcoinExchange& operator = ( const BitcoinExchange &obj );
};

class Date
{
	private:
		Date();
		Date& operator = ( const Date &obj );

	public:
		std::tm date;

		~Date() {};
   		Date(const Date& other) {
        date.tm_year = other.date.tm_year;
        date.tm_mon = other.date.tm_mon;
        date.tm_mday = other.date.tm_mday;
    }
		Date(int year, int month, int day) {
        date.tm_year = year - 1900;  // tm_year is years since 1900
        date.tm_mon = month - 1;     // tm_mon is months since January, so 0 = January
        date.tm_mday = day;          // tm_mday is the day of the month

        date.tm_hour = 0;
        date.tm_min = 0;
        date.tm_sec = 0;
    }

    bool operator<(const Date& other) const {
        if (date.tm_year != other.date.tm_year)
            return date.tm_year < other.date.tm_year;
        if (date.tm_mon != other.date.tm_mon)
            return date.tm_mon < other.date.tm_mon;
        return date.tm_mday < other.date.tm_mday;
    }

	bool operator != (const Date &date) const {
		return (date.date.tm_year != this->date.tm_year || date.date.tm_mon != this->date.tm_mon || date.date.tm_mday != this->date.tm_mday);
	}


};

inline std::ostream& operator << (std::ostream &os, const Date &date) {
	os << date.date.tm_year + 1900 << "-" << date.date.tm_mon + 1 << "-" << date.date.tm_mday;
	return os;
}
