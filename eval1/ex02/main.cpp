#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cout << RED << "Error: missing arguments for calculation" << NOC << std::endl;
		return (1);
	}
	if (argc == 2)
	{
		std::cout << BLU << "Hum difficult sort to do... let's say ... => " << argv[1] << " ;-P" << NOC << std::endl;
		return (0);
	}
	try
	{
		// std::cout << BLU << "entering data" << NOC << std::endl;
		PmergeMe numbers(argv);
		// std::cout << BLU << "vector sort" << NOC << std::endl;
		double timeVector = numbers.vectorPmergeMe();
		// std::cout << BLU << "list sort" << NOC << std::endl;
		double timeList = numbers.listPmergeMe();
		numbers.printAfter();
		std::cout << YEL << "Time to process a range of " << argc - 1 << " elements with std::list => " << timeList << " microsec (us)" << std::endl;
		std::cout << YEL << "Time to process a range of " << argc - 1 << " elements with std::vector => " << timeVector << " microsec (us)" << std::endl;
	}
	catch (const char *e)
	{
		std::cerr << RED << e << NOC << std::endl;
		return (1);
	}
	return (0);
}
