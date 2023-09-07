#include "RPN.hpp"

double RPNcalculate(std::string arg)
{
	std::stack<double> rpn;
	int i = 0;

	while (arg[i])
	{
		double number;
		if (arg[i] > 47 && arg[i] < 58)
		{
			std::string sNum;
			while (arg[i] > 47 && arg[i] < 58)
			{
				sNum += arg[i];
				i++;
			}
			std::istringstream(sNum) >> number;
			rpn.push(number);
		}
		else if (arg[i] == ' ')
			i++;
		else if (arg[i] == '+' || arg[i] == '-' || arg[i] == '*' || arg[i] == '/')
		{
			double num1;
			double num2;
			double result;
			if (rpn.size() < 2)
				throw "Error";
			num2 = rpn.top();
			rpn.pop();
			num1 = rpn.top();
			rpn.pop();
			if (arg[i] == '+')
				result = num1 + num2;
			if (arg[i] == '-')
				result = num1 - num2;
			if (arg[i] == '*')
				result = num1 * num2;
			if (arg[i] == '/')
				result = num1 / num2;
			rpn.push(result);
			i++;
		}
		else
			throw "Error";
	}
	if (rpn.size() != 1)
		throw "Error";
	else
		return (rpn.top());
}
