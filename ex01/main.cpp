#include "RPN.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << RED << "Error: missing arguments for calculation" << NOC << std::endl;
		return (1);
	}
	try
	{
		double result;
		std::string calc = argv[1];
		result = RPNcalculate(calc);
		std::cout << "result = " << result << std::endl;
	}
	catch (const char *e)
	{
		std::cerr << e << std::endl;
		return (1);
	}
	return (0);
}
