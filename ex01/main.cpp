/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 11:02:52 by tjorge-l          #+#    #+#             */
/*   Updated: 2026/01/12 11:02:52 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <stack>
#include <cstdlib>
#include <exception>
#include <sstream>

bool valid_input(const std::string& expr)
{
    for (std::string::const_iterator it = expr.begin(); it != expr.end(); ++it)
    {
        if (!std::isdigit(*it) && !std::isspace(*it) &&
            *it != '-' && *it != '+' && *it != '/' && *it != '*')
        {
            return false;
        }
    }
    return true;
}

std::stack<int> calculate(const std::string& user_input)
{
    std::stack<int> stk;
    std::istringstream iss(user_input);
    std::string token;

    while (iss >> token)
    {
        if (token == "+" || token == "-" || token == "*" || token == "/")
        {
            if (stk.size() < 2)
                throw std::exception();

            int right = stk.top(); stk.pop();
            int left = stk.top(); stk.pop();

            if (token == "+") stk.push(left + right);
            else if (token == "-") stk.push(left - right);
            else if (token == "*") stk.push(left * right);
            else if (token == "/")
            {
                if (right == 0)
                    throw std::exception();
                stk.push(left / right);
            }
        }
        else
        {
            char* end;
            long num = std::strtol(token.c_str(), &end, 10);

            if (end == token.c_str() || *end != '\0' || num > 9)
                throw std::exception(); // invalid number

            stk.push(static_cast<int>(num));
        }
    }
    return stk;
}

int	main(int argc, char **argv)
{
	if (argc != 2 || !valid_input(argv[1]))
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}
	valid_input(argv[1]);
	std::stack<int> stack;
	try
	{
		std::stack<int> stack;
		stack = calculate(argv[1]);

		if (stack.size() != 1)
		{
			std::cerr << "Error" << std::endl;
			return 1;
		}
		std::cout << "Result: " << stack.top() << std::endl;
	}
	catch(...)
	{
		std::cerr << "Error" << '\n';
	}

	return (0);
}
