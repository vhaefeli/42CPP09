/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:57:21 by vhaefeli          #+#    #+#             */
/*   Updated: 2023/06/23 12:20:50 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <ctime>

double convertDateToDecimal(const std::tm &date)
{
	std::time_t time = std::mktime(const_cast<std::tm *>(&date));
	return static_cast<double>(time) / 86400.0; // Nombre de secondes par jour
}

BitcoinExchange::BitcoinExchange()
{
	// map creation

	std::ifstream file("data.csv"); // Open the file
	if (file)						// controle if open
	{
		std::string line;
		double rate;
		double decimalDate;
		while (std::getline(file, line))
		{
			// std::cout << YEL << "btc line " << line << NOC << std::endl;
			if (line.substr(0, 2) == "20")
			{

				std::string str = line.substr(0, 4);
				std::istringstream issY(str);
				double num;
				if (!(issY >> num))
				{
					std::cout << YEL << "Error : data.cvs bad input => " << line << NOC << std::endl;
					_bcExchangeRate.insert(std::pair<double, double>(0, 0));
					break;
				}
				str = line.substr(5, 6);
				std::istringstream issM(str);
				if (!issM >> num || !(num >= 1 && num <= 12))
				{
					std::cout << YEL << "Error : data.cvs bad input => " << line << NOC << std::endl;
					_bcExchangeRate.insert(std::pair<double, double>(0, 0));
					break;
				}
				str = line.substr(8, 9);
				std::istringstream issD(str);
				if (issD >> num && (num >= 1 && num <= 31))
				{
					// number of days in the month
					if (date.tm_mon == 1)
					{
						if (num >= 29 && (num > 28 && ((date.tm_year + 1900) % 4) != 0))
						{
							std::cout << YEL << "Error : data.cvs bad input => " << line << NOC << std::endl;
							_bcExchangeRate.insert(std::pair<double, double>(0, 0));
							break;
						}
					}
					else if (num == 31 && ((date.tm_mon == 3 || date.tm_mon == 5 || date.tm_mon == 8 || date.tm_mon == 10)))
					{
						std::cout << YEL << "Error : data.cvs bad input => " << line << NOC << std::endl;
						_bcExchangeRate.insert(std::pair<double, double>(0, 0));
						break;
					}
					else
						date.tm_mday = num;
				}
				else
				{
					std::cout << YEL << "Error : data.cvs bad input => " << line << NOC << std::endl;
					_bcExchangeRate.insert(std::pair<double, double>(0, 0));
					break;
				}
				// check the rate
				str = line.substr(11);
				// std::cout << BLU << "text rate " << str << NOC << std::endl;
				std::istringstream iss(str);
				if (iss >> num && (num > 0 || num < INT_MAX))
				{
					rate = num;
				}
				else
				{
					std::cout << YEL << "Error : data.cvs bad input => " << line << NOC << std::endl;
					_bcExchangeRate.insert(std::pair<double, double>(0, 0));
					break;
				}
				// std::cout << BLU << "rate " << rate << NOC << std::endl;
				_bcExchangeRate.insert(std::pair<double, double>(decimalDate, rate));
			}
		}
		file.close();
	}
	else
	{
		std::cout << RED << "Error: cannot open file data.csv with bitcoin Exchage rates" << NOC << std::endl;
		_bcExchangeRate.insert(std::pair<double, double>(0, 0));
	}
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src)
{
	*this = src;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &rhs)
{
	if (this != &rhs)
	{
		this->_bcExchangeRate = rhs._bcExchangeRate;
	}
	return (*this);
}

BitcoinExchange::~BitcoinExchange()
{
}

double convertDate(std::string strdate)
{
	// date in decimal number
	double decimalDate;
	std::tm date = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	std::string str = strdate.substr(0, 4);
	std::istringstream issY(str);
	double num;
	if (issY >> num)
	{
		if (num > 2000 && num < 2040)
			date.tm_year = num - 1900;
	}
	else
	{
		return (-1);
	}
	str = strdate.substr(5, 6);
	// std::cout << BLU << "mois " << str << NOC << std::endl;
	std::istringstream issM(str);
	if (issM >> num && (num >= 1 && num <= 12))
	{
		// std::cout << BLU << "mois num " << num << NOC << std::endl;
		date.tm_mon = num - 1;
	}
	else
	{
		return (-1);
	}
	str = strdate.substr(8, 9);
	// std::cout << BLU << "jour " << str << NOC << std::endl;
	std::istringstream issD(str);
	if (issD >> num && (num >= 1 && num <= 31))
	{
		// number of days in the month
		if (date.tm_mon == 1)
		{
			if (num >= 29 && (num > 28 && ((date.tm_year + 1900) % 4) != 0))
				return (-1);
		}
		else if (num == 31 && ((date.tm_mon == 3 || date.tm_mon == 5 || date.tm_mon == 8 || date.tm_mon == 10)))
			return (-1);
		else
			date.tm_mday = num;
	}
	else
	{
		return (-1);
	}
	decimalDate = convertDateToDecimal(date);
	return (decimalDate);
}

double BitcoinExchange::getExchangeRate(std::string strdate)
{
	std::map<double, double>::iterator it;
	if (strdate == "0")
	{
		it = this->_bcExchangeRate.find(0);
		if (it == _bcExchangeRate.end())
		{
			return (1);
		}
		return (0);
	}
	// date in decimal number
	double decimalDate;
	decimalDate = convertDate(strdate);
	std::cout << YEL << "decimal date" << decimalDate << NOC << std::endl;
	if (decimalDate < 14246)
		return (-42) ;
	if (decimalDate > 19080)
		decimalDate = convertDate("2022-03-29");
	std::cout << YEL << "decimal date" << decimalDate << NOC << std::endl;
	it = this->_bcExchangeRate.find(decimalDate);
	std::cout << BLU << " it" << it->second << NOC << std::endl;
	if (it == _bcExchangeRate.end())
	{
		std::cout << YEL << " it decimal date" << decimalDate << NOC << std::endl;
		int i = 0;
		while (it == _bcExchangeRate.end() && i < 30)
		{
			std::cout << YEL << "decimal date" << decimalDate << NOC << std::endl;
			decimalDate--;
			i++;
			it = this->_bcExchangeRate.find(decimalDate);
		}
		// std::cout << YEL << "nearest decimal date" << decimalDate << NOC << std::endl;
	}
	// if (it == _bcExchangeRate.end())
	// {
	// 	_bcExchangeRate.erase(it);
	// 	return (-1);
	// }
	return (_bcExchangeRate.find(decimalDate)->second);
}
