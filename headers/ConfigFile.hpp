/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigFile.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:16:04 by mguerga           #+#    #+#             */
/*   Updated: 2024/04/09 11:06:43 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ConfigFile_hpp__
# define __ConfigFile_hpp__

# define CONFIG_FILE_MAX_SIZE 100

# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <map>
# include <vector>
//# include <algorithm>
# include "ParsingException.hpp"

typedef struct S_erver
{
	int prtn;
	std::string root;
	std::string home;
	int lcbs;
} t_server;

class ConfigFile
{
	private:

		std::string file_name;

		ConfigFile(const ConfigFile& o);
		ConfigFile& operator=(const ConfigFile& o);

	public:
		std::vector<int> prt_vec;
		std::map<std::string, t_server> _map;

		ConfigFile(const std::string);
		~ConfigFile();
		
		bool vec_contains(int);
		std::string prt_vec_print();
		//void checker() const;
		//const char* getMap(std::string);		

};

#endif
