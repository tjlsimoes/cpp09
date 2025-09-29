#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}
BitcoinExchange::BitcoinExchange( const BitcoinExchange &obj ) { (void)obj; }
BitcoinExchange& BitcoinExchange::operator = ( const BitcoinExchange &obj ) { (void)obj; return *this; }
BitcoinExchange::~BitcoinExchange() {}

const char *CannotOpenFile::what() const throw () {
	return "Error: Cannot open file!";
}

const char *InvalidFile::what() const throw () {
	return "Error: File contents aren't valid!";
}

BitcoinExchange::BitcoinExchange( const std::string &inFile ) : _inFile(inFile) {

	const std::string _dbFile = "data.csv";
	if (_inFile.empty() || _inFile == _dbFile)
		throw InvalidFile();
	try 
	{
		std::cout << std::endl << "======================" << std::endl << std::endl;
		mapInit(_dbFile);
		mapInit(_inFile);
		std::cout << std::endl << "======================" << std::endl << std::endl;

		run();
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		exit(1);
	}
}

void BitcoinExchange::mapInit(const std::string &filePath) {

	std::ifstream database(filePath.c_str());
	std::string line;//, date;
	//double value;
	std::map<std::string, double> db_map;

	if (!database.is_open())
		throw CannotOpenFile();

	// First line
	std::getline(database, line);
	if (!headerCheck(line))
		throw InvalidFile();
	while (std::getline(database, line))
	{
		if (line.empty() || !parseLine(line))
			std::cout << "Error: BAD INPUT => " << line << std::endl;
	}
}

std::string trim(const std::string& str) {

	size_t start = 0;
	while (start < str.size() && std::isspace(str[start])) ++start;
	
	size_t end = str.size();
	while (end > start && std::isspace(str[end - 1])) --end;
	
	return str.substr(start, end - start);
}

bool BitcoinExchange::headerCheck(const std::string &line) {

    std::string trimmedInput = trim(line);
    size_t pipePos = trimmedInput.find('|');
    size_t commaPos = trimmedInput.find(',');

    if (pipePos != std::string::npos) {
        // "date | value" format
        std::string leftPart = trim(trimmedInput.substr(0, pipePos));
        std::string rightPart = trim(trimmedInput.substr(pipePos + 1));
		if (leftPart == "date" && rightPart == "value") {
            return true;
        }
    } else if (commaPos != std::string::npos) {
        // "date, exchange rate" format
        std::string leftPart = trim(trimmedInput.substr(0, commaPos));
        std::string rightPart = trim(trimmedInput.substr(commaPos + 1));
        if (leftPart == "date" && rightPart == "exchange_rate") {
            return true;
        }
    }
    
    return false;
}

bool BitcoinExchange::parseLine(const std::string &line) {

	size_t delimPos = line.find('|');
	if (delimPos == std::string::npos)
		delimPos = line.find(',');
	if (delimPos == std::string::npos)
		return false;

	std::string dateStr = trim(line.substr(0, delimPos));
	std::string valueStr = trim(line.substr(delimPos + 1));
	if (dateStr.empty() || valueStr.empty())
		return false;
	if (!isValidContent(dateStr, valueStr, line[delimPos]))
		return false;
	return true;
}

bool BitcoinExchange::isValidContent(const std::string &dateStr, const std::string &valueStr, char delim) {

	int year, month, day;
	char dash1, dash2;
	std::stringstream ss(dateStr);

	if (!(ss >> year >> dash1 >> month >> dash2 >> day) || dash1 != '-' || dash2 != '-')
		return false;

	if (year < 2009 || month < 1 || month > 12)
		return false;

	int daysInMonth;
	switch (month) {
		case 2:
			daysInMonth = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 29 : 28;
			break;
		case 4: case 6: case 9: case 11:
			daysInMonth = 30;
			break;
		default:
			daysInMonth = 31;
			break;
	}

	if (day < 1 || day > daysInMonth)
		return false;

	if ( delim == '|' && year == 2009 && month == 1 && day < 3)
		return false;

	double value = std::strtod(valueStr.c_str(), NULL);
	if (delim == '|' && (value < 0.0 || value > 1000.0))
		return false;
	
	if (delim == ',')
		_dbMap.insert(std::pair<Date, double>(Date(year, month, day), value));
	else
		_inMap.insert(std::pair<Date, double>(Date(year, month, day), value));	
	return true;
}

void BitcoinExchange::printDbMap() {

	std::map<Date, double>::iterator it = _dbMap.begin();
	while (it != _dbMap.end())
	{
		std::cout << it->first.date.tm_year + 1900 << "-" << it->first.date.tm_mon + 1 << "-" << it->first.date.tm_mday << " | " << it->second << std::endl;
		it++;
	}
}

void BitcoinExchange::printInMap() {

	std::map<Date, double>::iterator it = _inMap.begin();
	while (it != _inMap.end())
	{
		std::cout << it->first.date.tm_year + 1900 << "-" << it->first.date.tm_mon + 1 << "-" << it->first.date.tm_mday << " | " << it->second << std::endl;
		it++;
	}
}

void BitcoinExchange::run() {

	std::map<Date, double>::iterator db_it = _dbMap.begin();
	std::map<Date, double>::iterator in_it = _inMap.begin();


	for (; in_it != _inMap.end(); ++in_it) {

        while (db_it != _dbMap.end() && db_it->first < in_it->first) {++db_it;}
		if (db_it == _dbMap.end())
			db_it = --_dbMap.end();
		std::cout 	<< in_it->first.date.tm_year + 1900 << "-" 
					<< in_it->first.date.tm_mon + 1 << "-" 
					<< in_it->first.date.tm_mday << " => " 
					<< in_it->second << " = " 
					<< std::fixed << std::setprecision(2) 
					<< in_it->second * db_it->second 
					<< std::endl;
	}

		//std::cout << "INPUT: " << in_it->first << " VALUE: " << in_it->second << " CLOSEST: " << db_it->first << " VALUE: " << db_it->second << " ==> " << in_it->second * db_it->second << std::endl;
}