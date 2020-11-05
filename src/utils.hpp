/*
 * utils.hpp
 *
 *  Created on: 4 nov. 2020
 *      Author: ruben
 */

#pragma once
#include <list>
#include <string>
#include <bits/stdc++.h>
#include <sstream>

namespace stringutils
{



std::list<std::string> tokenize(const std::string& str, const char delim) const
{
	std::stringstream stream{str};
	std::string read;

	std::list<std::string> tokens;

	while(std::getline(stream, read, delim))
	{
		tokens.push_back(read);
	}

	return tokens;
}

}
