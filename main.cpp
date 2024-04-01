/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:03:13 by mguerga           #+#    #+#             */
/*   Updated: 2024/04/01 21:50:21 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigFile.hpp"
#include <iostream>

int	main(int ac, char** av)
{
	try
	{
		if (ac > 2)
			throw ParsingException(0);
		else if (ac == 2)
			ConfigFile conf(av[1]);
		else
			ConfigFile conf("Conf/default.conf");
	}
	catch (std::exception& e)
	{
		return (std::cout << e.what() << std::endl && 1);
	}
	return 0;
}

