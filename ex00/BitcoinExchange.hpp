#ifndef BITCOIN_EXCHANGE_HPP
# define BITCOIN_EXCHANGE_HPP
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <string>

class BitcoinExchange
{
	private:
		std::fstream							user_file;
		std::fstream							data;
		std::vector<std::vector<std::string> >	db;

		void	file_readable(std::fstream & user_file, char *file_path);
		bool	invalid_date(std::vector<int> &date);
		bool	validate_date(std::string &date);
		bool	validate_price(std::string &price);
		float	get_price(std::vector<std::vector<std::string> > db, std::string &date);
		std::vector<std::vector<std::string> > gen_db(std::fstream & data);
		
	public:
		BitcoinExchange();
		BitcoinExchange(char *file_path);
		~BitcoinExchange();
		void	read_line();


};

#endif