#include <iostream>
#include <string>
#include <stack>
#include <cstdlib>
#include <exception>

bool	valid_input(std::string expr)
{
	for (std::string::iterator it = expr.begin(); it != expr.end(); it++)
	{
		if (!std::isdigit(*it) && !std::isspace(*it)
			&& *it != '-' && *it != '+'
			&& *it != '/' && *it != '*')
			{
				std::cerr << "Error" << std::endl;
				return (false);
			}
	}
	return (true);
}

std::stack<int>	calculate(std::string user_input)
{
	std::stack<int>	stack;
	int					left;
	int					right;

	for (std::string::iterator it = user_input.begin(); it != user_input.end(); it++)
	{
		// std::cout << *it << std::endl;
		if (!std::isspace(*it))
		{
			if (std::isdigit(*it))
				stack.push(*it - '0');
			else
			{
				// Check for errors here?
				right = stack.top();
				stack.pop();
				left = stack.top();
				stack.pop();
				// std::cout
				// << "Left: " << left << "\n"
				// << "Right: " << right
				// << std::endl;
				switch (*it)
				{
					case '+':
						stack.push(left + right);
						break ;
					case '-':
						stack.push(left - right);
						break ;
					case '*':
						stack.push(left * right);
						break ;
					case '/':
						if (right == 0)
							throw std::exception();
						stack.push(left / right);
						break ;
					default:
						throw std::exception();
				}
			}
		}
	}
	return stack;
}

int	main(int argc, char **argv)
{
	if (argc != 2 || !valid_input(argv[1]))
		return (1);
	valid_input(argv[1]);
	std::stack<int> stack;
	try
	{
		std::stack<int> stack;
		stack = calculate(argv[1]);

		if (stack.size() != 1)
			std::cerr << "Error" << std::endl;
		std::cout << "Result: " << stack.top() << std::endl;
	}
	catch(...)
	{
		std::cerr << "Error" << '\n';
	}

	return (0);
}
