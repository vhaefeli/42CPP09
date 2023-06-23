/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 08:23:48 by vhaefeli          #+#    #+#             */
/*   Updated: 2023/06/23 01:03:50 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << RED << "Error: missing file as parameter." << NOC << std::endl;
		return (1);
	}
	std::ifstream file(argv[1]); // Open the file
	if (file)					 // controle if open
	{
		BitcoinExchange btc;

		// error with data.csv
		if (btc.getExchangeRate("0") == 0)
		{
			file.close();
			return (1);
		}
		std::string line;
		double rate;
		while (std::getline(file, line))
		{
			// std::cout << YEL << "line " << line << NOC << std::endl;
			if (line != "date | value")
			{
				rate = btc.getExchangeRate(line.substr(0, 10));
				if (rate == -1)
					std::cout << YEL << "Error : bad date input => " << line << NOC << std::endl;
				else
				{
					std::string str = line.substr(13);
					std::istringstream iss(str);
					double num;
					if (iss >> num)
					{
						if (num < 0)
							std::cout << YEL << "Error : not a positive number." << NOC << std::endl;
						else if (num > INT_MAX)
							std::cout << YEL << "Error : too large a number" << NOC << std::endl;
						else
						{
							std::cout << line.substr(0, 10) << " => " << num << " = " << num * rate << std::endl;
						}
					}
					else
					{
						std::cout << YEL << "Error : bad input => " << line << NOC << std::endl;
					}
					// std::cout << BLU << "rate " << rate << "quantity " << num << NOC << std::endl;
				}
			}
		}
		file.close();
	}
	else
	{
		std::cout << RED << "Error: Cannot open file" << argv[2] << NOC << std::endl;
		return (1);
	}
}
