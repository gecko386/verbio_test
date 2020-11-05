/*
 * NumericParser.hpp
 *
 *  Created on: 3 nov. 2020
 *      Author: ruben
 */

#pragma once
#include "Token.hpp"
#include <string>
#include <list>
#include <stack>

class NumericParser
{
public:
	NumericParser(){};

	std::string parse(const std::string& str) const;

private:

	int parseUnits(std::stack<Token>& tokens) const;
	int parseOneToNinetyNine(std::stack<Token>& tokens) const;
	int parseOneToNineHundredAndNinetyNine(std::stack<Token>& tokens) const;
	int parseHundreds(std::stack<Token>& tokens) const;
	int parseThousands(std::stack<Token>& tokens) const;
	int parseMillions(std::stack<Token>& tokens) const;
	int parseBillion(std::stack<Token>& tokens) const;

	std::stack<Token> tokenize(const std::string& str, const std::string& delim=", ") const;
	std::list<Token> parse(std::stack<Token>& tokens) const;

};
