/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:30:23 by vhaefeli          #+#    #+#             */
/*   Updated: 2023/06/24 00:22:12 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#define RED "\033[31;1m"
#define GRE "\033[32;1m"
#define YEL "\033[33;1m"
#define BLU "\033[34;1m"
#define NOC "\033[0m"

#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <limits>
#include <utility>
#include <cstdlib>
#include <algorithm>
#include <ctime>

class PmergeMe
{
private:
	PmergeMe();
	PmergeMe(const PmergeMe &src);
	PmergeMe &operator=(const PmergeMe &rhs);

	std::vector<int> _vectorUnsorted;
	std::vector<std::pair<int, int> > _vectorPairs;
	std::vector<int> _vectorSorted;
	std::list<int> _listUnsorted;
	std::list<std::pair<int, int> > _listPairs;
	std::list<int> _listSorted;

public:
	PmergeMe(char **argv);
	~PmergeMe();
	double vectorPmergeMe();
	double listPmergeMe();
	void printAfter();
};

#endif
