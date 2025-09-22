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

std::stack<char>	gen_stack(std::string user_input)
{
	std::stack<char>	stack;

	for (std::string::iterator it = user_input.begin(); it != user_input.end(); it++)
	{
		std::cout << *it << std::endl;
		if (!std::isspace(*it))
			stack.push(*it);
	}
	return (stack);
}

void	get_operands(char *left, char *right, char *oper, std::stack<char> &stack)
{
	*oper = stack.top();
	stack.pop();
	*right = stack.top();
	stack.pop();
	*left = stack.top();
	if (std::isdigit(*left))
		stack.pop();
}

int	calculate(std::stack<char> &stack)
{
	char	oper;
	char	left;
	char	right;

	get_operands(&left, &right, &oper, stack);
	std::cout
	<< "Left: " << left << "\n"
	<< "Right: " << right << "\n"
	<< "Oper: " << oper
	<< std::endl;
	if (!std::isdigit(left))
	{
		std::cout << "here" << std::endl;
		switch (oper)
		{
			case '+':
				return (calculate(stack) + (right - '0'));
			case '-':
				return (calculate(stack) - (right - '0'));
			case '*':
				return (calculate(stack) * (right - '0'));
			case '/':
				return (calculate(stack) / (right - '0'));
			default:
				throw std::exception();
		}
	}
	switch (oper)
	{
		case '+':
			return ((left - '0') + (right - '0'));
		case '-':
			return ((left - '0') - (right - '0'));
		case '*':
			return ((left - '0') * (right - '0'));
		case '/':
			return ((left - '0') / (right - '0'));
		default:
			throw std::exception();
	}
}

int	main(int argc, char **argv)
{
	std::stack<char> stack;
	if (argc != 2 || !valid_input(argv[1]))
		return (1);
	stack = gen_stack(argv[1]);
	std::cout << std::endl;
	std::cout << "Size: " << stack.size() << std::endl;
	std::cout << std::endl;
	// size_t i = 0;
	// size_t size = stack.size();
	// while (i < size)
	// {
	// 	std::cout << stack.top() << std::endl;
	// 	stack.pop();
	// 	i++;
	// }
	int result = calculate(stack);
	std::cout << "Result: " << result << std::endl;

	return (0);
}