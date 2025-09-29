#pragma once

#include <iostream>
#include <sstream>
#include <exception>
#include <list>
#include <stack>
// RTFM: https://en.cppreference.com/w/cpp/container/stack

bool	isOperator(char c);
void	replaceWs(std::string &str);
double	run(const std::string &op, double a, double b);

class RPN
{
	typedef std::stack<double, std::list<double> > numberStack;

	public:
    	RPN(const std::string &_input);
    	~RPN();

		class WrongInput : public std::exception {
		public:
			const char *what() const throw();
		};

	private:
		RPN();
		RPN(const RPN &obj);
		RPN& operator = (const RPN &obj);

		numberStack 	numbers;
};