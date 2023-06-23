/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 08:26:29 by vhaefeli          #+#    #+#             */
/*   Updated: 2023/06/22 22:57:29 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#define RED "\033[31;1m"
#define GRE "\033[32;1m"
#define YEL "\033[33;1m"
#define BLU "\033[34;1m"
#define NOC "\033[0m"

#include <fstream>
#include <string>
#include <map>
#include <iostream>
#include <sstream>

class BitcoinExchange
{
private:
	std::map<double, double> bcExchangeRate;

public:
	BitcoinExchange();
	~BitcoinExchange();
	double getExchangeRate(std::string strdate);
};

#endif
