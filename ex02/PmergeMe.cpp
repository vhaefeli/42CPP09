#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe(char **argv)
{
	std::cout << "Before";
	for (int i = 1; argv[i]; i++)
	{
		int number;
		if (std::istringstream(argv[i]) >> number && number >= 0)
		{
			_vectorUnsorted.push_back(number);
			_listUnsorted.push_back(number);
			std::cout << " " << number;
		}
		else
		{
			std::cout << "..." << std::endl;
			throw "Wrong arguments, all the arguments must be positive intergers";
		}
	}
	std::cout << std::endl;
}

PmergeMe::PmergeMe(const PmergeMe &src)
{
	*this = src;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &rhs)
{
	if (this != &rhs)
	{
		this->_vectorUnsorted = rhs._vectorUnsorted;
	}
	return (*this);
}

PmergeMe::~PmergeMe()
{
}

double PmergeMe::vectorPmergeMe()
{
	// start timer
	clock_t Start = clock();

	// create pairs
	for (size_t i = 0; i < _vectorUnsorted.size(); i++)
	{
		if (i == 0 && _vectorUnsorted.size() % 2)
			_vectorPairs.push_back(std::make_pair(-1, _vectorUnsorted[i]));
		else
		{
			_vectorPairs.push_back(std::make_pair(_vectorUnsorted[i], _vectorUnsorted[i + 1]));
			i = i + 1;
		}
	}

	// swap pairs
	for (std::vector<std::pair<int, int> >::iterator it = _vectorPairs.begin(); it != _vectorPairs.end(); ++it)
	{
		if ((*it).first > (*it).second)
			std::swap((*it).first, (*it).second);
	}

	// sort the pairs regarding the first element
	for (std::vector<std::pair<int, int> >::iterator it = _vectorPairs.begin() + 1; it != _vectorPairs.end(); ++it)
	{
		std::vector<std::pair<int, int> >::iterator actual = it;
		std::vector<std::pair<int, int> >::iterator prev = it - 1;
		while ((*actual).first < (*prev).first)
		{
			std::swap(*actual, *prev);
			if (prev != _vectorPairs.begin())
			{
				actual = prev;
				prev = actual - 1;
			}
		}
	}

	// push sorted first elem in the sorted vector
	for (std::vector<std::pair<int, int> >::iterator it = _vectorPairs.begin(); it != _vectorPairs.end(); ++it)
	{
		if ((*it).first != -1)
			_vectorSorted.push_back((*it).first);
	}

	// insert second elem in the sorted vector
	for (std::vector<std::pair<int, int> >::iterator it = _vectorPairs.begin(); it != _vectorPairs.end(); ++it)
	{
		std::vector<int>::iterator itSorted;

		itSorted = std::lower_bound(_vectorSorted.begin(), _vectorSorted.end(), (*it).second);
		_vectorSorted.insert(itSorted, (*it).second);
	}

	// stop timer
	return ((clock() - Start) * 1000000 / CLOCKS_PER_SEC);
}

double PmergeMe::listPmergeMe()
{
		// start timer
	clock_t Start = clock();
	// create pairs
	for (std::list<int>::iterator it = _listUnsorted.begin(); it != _listUnsorted.end(); ++it)
	{
		if (it == _listUnsorted.begin() && _listUnsorted.size() % 2)
			_listPairs.push_back(std::make_pair(-1, *it));
		else
		{
			std::list<int>::iterator next = it;
			next++;
			_listPairs.push_back(std::make_pair(*it, *next));
			++it;
		}
	}

	// swap pairs
	for (std::list<std::pair<int, int> >::iterator it = _listPairs.begin(); it != _listPairs.end(); ++it)
	{
		if ((*it).first > (*it).second)
			std::swap((*it).first, (*it).second);
	}

	// sort the pairs regarding the first element
	for (std::list<std::pair<int, int> >::iterator it = std::next(_listPairs.begin()); it != _listPairs.end(); ++it)
	{
		std::list<std::pair<int, int> >::iterator actual = it;
		std::list<std::pair<int, int> >::iterator prev = std::prev(it);
		while ((*actual).first < (*prev).first)
		{
			std::swap(*actual, *prev);
			if (prev != _listPairs.begin())
			{
				actual = prev;
				prev = std::prev(actual);
			}
		}
	}

	// push sorted first elem in the sorted list
	for (std::list<std::pair<int, int> >::iterator it = _listPairs.begin(); it != _listPairs.end(); ++it)
	{
		if ((*it).first != -1)
			_listSorted.push_back((*it).first);
	}

	// insert second elem in the sorted list
	for (std::list<std::pair<int, int> >::iterator it = _listPairs.begin(); it != _listPairs.end(); ++it)
	{
		std::list<int>::iterator itSorted = std::lower_bound(_listSorted.begin(), _listSorted.end(), (*it).second);
		_listSorted.insert(itSorted, (*it).second);
	}

	// stop timer
	return ((clock() - Start) * 1000000 / CLOCKS_PER_SEC);
}

void PmergeMe::printAfter()
{
	if (_listSorted.size() == _listUnsorted.size())
	{
		std::cout << "After";
		for (std::list<int>::iterator it = _listSorted.begin(); it != _listSorted.end(); ++it)
		{
			std::cout << " " << *it;
		}
		std::cout << std::endl;
	}
	else if (_vectorSorted.size() == _vectorUnsorted.size())
	{
		std::cout << "After";
		for (std::vector<int>::iterator it = _vectorSorted.begin(); it != _vectorSorted.end(); ++it)
		{
			std::cout << " " << *it;
		}
		std::cout << std::endl;
	}
	else
		throw "No sorting has been done";
}
