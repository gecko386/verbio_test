/*
 * NumericParser.cpp
 *
 *  Created on: 3 nov. 2020
 *      Author: ruben
 *
 *
 * This class implements a parser to convert word numbers in numeric format following:
 *
 *		https://www.gymglish.com/en/gymglish/english-grammar/big-numbers
 * 		https://englishlessonsbrighton.co.uk/saying-large-numbers-english/
 */

#include "NumericParser.hpp"
#include <sstream>
#include <iostream>


std::stack<Token> NumericParser::tokenize(const std::string& str, const std::string& delim) const
{

	std::stack<Token> tokens;

	std::string::size_type lastPos = 0;


	// Find first delimiter".
	std::string::size_type pos = str.find_first_of(delim, 0);

	while (pos != std::string::npos || lastPos != std::string::npos)
	{
		// Found a token, add it to the stack

		if(pos != lastPos)
		{
			std::string t(str.substr(lastPos, pos - lastPos));
			tokens.emplace(t);
		}

		// add delimiter if not ending
		if(pos == std::string::npos)
		{
			lastPos = pos;
			break;
		}
		const std::string delimChar(1, str.at(pos));
		Token d(delimChar);
		if(d.isComma())
		{
			tokens.push(d);
		}

		lastPos = pos+1;
		// Find next delimiter
		pos = str.find_first_of(delim, lastPos);
	}
	//adding the ending part


	if(lastPos != std::string::npos)
	{
		std::string t(str.substr(lastPos, str.size()));
		tokens.emplace(t);
	}

	return tokens;
}


int NumericParser::parseUnits(std::stack<Token>& tokens) const
{
	int res = 0;

	if (!tokens.empty() && tokens.top().isUnit())
	{
		res = tokens.top().getValue();
		tokens.pop();
	}

	return res;
}

int NumericParser::parseOneToNinetyNine(std::stack<Token>& tokens) const
{
	int units = parseUnits(tokens);

	//Not a unit, check value between 10-19
	if(units == 0)
	{
		if (!tokens.empty() && tokens.top().isFromTenToNineteen())
		{
			units = tokens.top().getValue();
			tokens.pop();
		}
	}

	//Not a value between 10-19, check value between 20-99
	if(units == 0)
	{
		if (!tokens.empty() && tokens.top().isFromTwentyToNinetyNine())
		{
			units = tokens.top().getValue();
			tokens.pop();
		}
	}

	return units;
}

int NumericParser::parseHundreds(std::stack<Token>& tokens) const
{
	int res = 0;

	if(!tokens.empty())
	{
		Token topMult(tokens.top());
		tokens.pop();

		if (topMult.isMultiplier() && topMult.getValue() == 100)
		{
			res = parseUnits(tokens);
		}
		else
		{
			tokens.push(topMult);
		}
	}

	return res*100;
}

int NumericParser::parseOneToNineHundredAndNinetyNine(std::stack<Token>& tokens) const
{
	int res = 0;
	int parsed = 0;
	Token andToken("");

	parsed = parseOneToNinetyNine(tokens);

	res += parsed;

	if(parsed !=0 && !tokens.empty())
	{
		if(tokens.top().isAnd())
		{
			andToken = tokens.top();
			tokens.pop();
		}

		// check for hundreds part
		parsed = parseHundreds(tokens);
		res += parsed;

		//No thousand part, restore 'AND' token
		if(parsed == 0 and andToken.isAnd())
		{
			tokens.push(andToken);
		}
	}

	return res;
}

int NumericParser::parseThousands(std::stack<Token>& tokens) const
{
	int res = 0;

	if(!tokens.empty())
	{
		Token topMult(tokens.top());
		tokens.pop();

		if (topMult.isMultiplier() && topMult.getValue() == 1000)
		{
			res = parseOneToNineHundredAndNinetyNine(tokens);
		}
		else
		{
			tokens.push(topMult);
		}
	}

	return res*1000;
}

int NumericParser::parseMillions(std::stack<Token>& tokens) const
{
	int res = 0;
	int parsed = 0;

	if(!tokens.empty())
	{
		Token topMult(tokens.top());
		tokens.pop();

		if (topMult.isMultiplier() && topMult.getValue() == 1000000)
		{
			parsed = parseThousands(tokens);
			if(parsed == 0)
			{
				parsed = parseHundreds(tokens);
			}
			if(parsed == 0)
			{
				parsed = parseOneToNineHundredAndNinetyNine(tokens);
			}
			if(parsed == 0)
			{
				tokens.push(topMult);
			}
			else
			{
				res = parsed;
			}
		}
		else
		{
			tokens.push(topMult);
		}
	}

	return res*1000000;
}

int NumericParser::parseBillion(std::stack<Token>& tokens) const
{
	int res = 0;

	if(!tokens.empty())
	{
		Token topMult(tokens.top());
		tokens.pop();

		if (topMult.isMultiplier() && topMult.getValue() == 1000000000)
		{
			//The only valid token is one or 'a'
			if(!tokens.empty() && tokens.top().getValue() == 1)
			{
				res = 1000000000;
				tokens.pop();
			}
		}
		else
		{
			tokens.push(topMult);
		}
	}

	return res;
}

std::list<Token> NumericParser::parse(std::stack<Token>& tokens) const
{
	std::list<Token> res;
	while(!tokens.empty())
	{
		int parsed, value=0;
		Token andToken("");
		Token commaToken("");
		//special cases: zero

		if (tokens.top().isZero())
		{
			res.push_front(tokens.top().getValue());
			tokens.pop();
			continue;
		}

		parsed = parseOneToNineHundredAndNinetyNine(tokens);
		value += parsed;

		parsed = parseHundreds(tokens);
		value += parsed;

		// if current value is less than 100 we can find a "AND" token


		if(value<100 && !tokens.empty() && tokens.top().isAnd())
		{
			andToken = tokens.top();
			tokens.pop();
		}
		//otherwise we should find a comma
		else if(value>100 && !tokens.empty() && tokens.top().isComma())
		{
			commaToken = tokens.top();
			tokens.pop();
		}
		//No comma nor AND: maybe a year
		else
		{
			if(value<100 and value>0)
			{
				parsed = parseOneToNinetyNine(tokens);
				if(parsed !=0)
				{
					//It's a year!
					value += parsed*100;

				}
			}
			//we cannot continue, put current value to output
			if(value>0)
			{
				res.push_front(Token(std::to_string(value)));
				value = 0;
			}
		}

		parsed = parseThousands(tokens);
		if(parsed>0 && commaToken.isComma())
		{
			//Comma consumed
			commaToken=Token("");
		}
		value += parsed;

		//if we got hundreds we have to find another comma
		if(parsed!=0 && !tokens.empty() && tokens.top().isComma())
		{
			commaToken = tokens.top();
			tokens.pop();
		}
		else if(parsed!=0)
		{
			//we cannot continue, put current value to output
			res.push_front(Token(std::to_string(value)));
			value = 0;
		}
		parsed = parseMillions(tokens);
		if(parsed>0 && commaToken.isComma())
		{
			//Comma consumed
			commaToken=Token("");
		}
		value += parsed;

		//if we got millions we have to find another comma
		if(parsed!=0 && !tokens.empty() && tokens.top().isComma())
		{
			commaToken = tokens.top();
			tokens.pop();
		}
		else if(parsed!=0)
		{
			//we cannot continue, put current value to output
			res.push_front(Token(std::to_string(value)));
			value = 0;
		}

		parsed = parseBillion(tokens);

		if(parsed>0 && commaToken.isComma())
		{
			//Comma consumed
			commaToken=Token("");
		}
		value += parsed;

		if(value != 0)
		{
			res.push_front(Token(std::to_string(value)));

			//in case that value <100 and we have an "AND" token send to output
			if(value <100 && andToken.isAnd())
			{
				res.push_front(andToken);
			}

		}
		else
		{
			if(!tokens.empty())
			{
				res.push_front(tokens.top());
				tokens.pop();
			}
		}
		if(commaToken.isComma())
		{
			res.push_front(commaToken);
		}
	}

	return res;
}

std::string NumericParser::parse(const std::string& str) const
{
	std::stack<Token> tokens(tokenize(str));

	std::list<Token> tokenList=parse(tokens);

	std::string res;

	for(auto it = tokenList.begin(); it!=tokenList.end(); ++it)
	{
		res +=it->getWord() +" ";
	}

	if(!res.empty())
	{
		res.pop_back();
	}

	return res;
}

