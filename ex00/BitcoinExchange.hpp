/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 11:02:41 by tjorge-l          #+#    #+#             */
/*   Updated: 2026/01/12 11:02:41 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOIN_EXCHANGE_HPP
# define BITCOIN_EXCHANGE_HPP
#include <list>
#include <string>
#include <utility>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstdlib>

class BitcoinExchange
{
	private:
		std::string									_inputFilename;
		std::list<std::pair<std::string, float> >	_database;

		void	_loadDatabase();
		void	_processInput() const;
		bool	_isValidDate(const std::string &date) const;
		bool	_isValidValue(const std::string & valueStr, float & value) const;
		float	_findClosestPrice(const std::string & targetDate) const;
		static	std::string _trim(const std::string &str);

		BitcoinExchange &operator=(const BitcoinExchange & rhs);
	
	public:
		BitcoinExchange();
		explicit BitcoinExchange(const std::string & inputFilename);
		BitcoinExchange(const BitcoinExchange & rhs);
		~BitcoinExchange();

		void	run() const;
};

#endif