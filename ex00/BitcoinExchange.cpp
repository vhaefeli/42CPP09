/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:57:21 by vhaefeli          #+#    #+#             */
/*   Updated: 2023/06/23 11:43:30 by vhaefeli         ###   ########.fr       */
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
				// date in decimal number
				std::tm date = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

				std::string str = line.substr(0, 4);
				std::istringstream issY(str);
				double num;
				if (issY >> num)
				{
					if (num > 2008 && num < 2040)
						date.tm_year = num - 1900;
				}
				else
				{
					std::cout << YEL << "Error : data.cvs bad input => " << line << NOC << std::endl;
					bcExchangeRate.insert(std::pair<double, double>(0, 0));
					break;
				}
				str = line.substr(5, 6);
				std::istringstream issM(str);
				if (issM >> num && (num >= 1 && num <= 12))
				{
					date.tm_mon = num - 1;
				}
				else
				{
					std::cout << YEL << "Error : data.cvs bad input => " << line << NOC << std::endl;
					bcExchangeRate.insert(std::pair<double, double>(0, 0));
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
							bcExchangeRate.insert(std::pair<double, double>(0, 0));
							break;
						}
					}
					else if (num == 31 && ((date.tm_mon == 3 || date.tm_mon == 5 || date.tm_mon == 8 || date.tm_mon == 10)))
					{
						std::cout << YEL << "Error : data.cvs bad input => " << line << NOC << std::endl;
						bcExchangeRate.insert(std::pair<double, double>(0, 0));
						break;
					}
					else
						date.tm_mday = num;
				}
				else
				{
					std::cout << YEL << "Error : data.cvs bad input => " << line << NOC << std::endl;
					bcExchangeRate.insert(std::pair<double, double>(0, 0));
					break;
				}
				decimalDate = convertDateToDecimal(date);
				// std::cout << YEL << "decimal date" << decimalDate << NOC << std::endl;
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
					bcExchangeRate.insert(std::pair<double, double>(0, 0));
					break;
				}
				// std::cout << BLU << "rate " << rate << NOC << std::endl;
				bcExchangeRate.insert(std::pair<double, double>(decimalDate, rate));
			}
		}
		file.close();
	}
	else
	{
		std::cout << RED << "Error: cannot open file data.csv with bitcoin Exchage rates" << NOC << std::endl;
		bcExchangeRate.insert(std::pair<double, double>(0, 0));
	}
}

BitcoinExchange::~BitcoinExchange()
{
}

double BitcoinExchange::getExchangeRate(std::string strdate)
{
	std::map<double, double>::iterator it;
	if (strdate == "0")
	{
		it = this->bcExchangeRate.find(0);
		if (it == bcExchangeRate.end())
		{
			return (1);
		}
		return (0);
	}
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
	// std::cout << YEL << "decimal date" << decimalDate << NOC << std::endl;

	it = this->bcExchangeRate.find(decimalDate);
	if (it == bcExchangeRate.end())
	{
		int i = 0;
		while (it == bcExchangeRate.end() && i < 30)
		{
			decimalDate--;
			i++;
			it = this->bcExchangeRate.find(decimalDate);
		}
		// std::cout << YEL << "nearest decimal date" << decimalDate << NOC << std::endl;
	}
	if (it == bcExchangeRate.end())
	{
		bcExchangeRate.erase(it);
		return (-1);
	}
	return (bcExchangeRate.find(decimalDate)->second);
}
