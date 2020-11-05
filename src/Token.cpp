/*
 * Token.cpp
 *
 *  Created on: 3 nov. 2020
 *      Author: ruben
 */

#include "Token.hpp"
#include <algorithm>
#include <list>

std::string Token::ZERO("zero");
std::string Token::AND("and");
std::string Token::A("a");
std::string Token::COMMA(",");
std::string Token::SPACE(" ");

std::map<std::string, int> Token::units = {
		{"one",   1},
		{"two",   2},
		{"three",  3},
		{"four",  4},
		{"five",  5},
		{"six",   6},
		{"seven", 7},
		{"eight", 8},
		{"nine",  9},
};

std::map<std::string, int> Token::fromTenToNineteen = {
		{"ten",       10},
		{"eleven",    11},
		{"twelve",    12},
		{"thirteen",  13},
		{"fourteen",  14},
		{"fifteen",   15},
		{"sixteen",   16},
		{"seventeen", 17},
		{"eighteen",  18},
		{"nineteen",  19},
};

std::map<std::string, int> Token::fromTwentyToNinetyNine = {
		{"twenty",			20},
		{"twenty-one",		21},
		{"twenty-two",		22},
		{"twenty-three",	23},
		{"twenty-four",		24},
		{"twenty-five",		25},
		{"twenty-six",		26},
		{"twenty-seven",	27},
		{"twenty-eight",	28},
		{"twenty-nine",		29},

		{"thirty",			30},
		{"thirty-one",		31},
		{"thirty-two",		32},
		{"thirty-three",	33},
		{"thirty-four",		34},
		{"thirty-five",		35},
		{"thirty-six",		36},
		{"thirty-seven",	37},
		{"thirty-eight",	38},
		{"thirty-nine",		39},

		{"forty",			40},
		{"forty-one",		41},
		{"forty-two",		42},
		{"forty-three",		43},
		{"forty-four",		44},
		{"forty-five",		45},
		{"forty-six",		46},
		{"forty-seven",		47},
		{"forty-eight",		48},
		{"forty-nine",		49},

		{"fifty",			50},
		{"fifty-one",		51},
		{"fifty-two",		52},
		{"fifty-three",		53},
		{"fifty-four",		54},
		{"fifty-five",		55},
		{"fifty-six",		56},
		{"fifty-seven",		57},
		{"fifty-eight",		58},
		{"fifty-nine",		59},

		{"sixty",			60},
		{"sixty-one",		61},
		{"sixty-two",		62},
		{"sixty-three",		63},
		{"sixty-four",		64},
		{"sixty-five",		65},
		{"sixty-six",		66},
		{"sixty-seven",		67},
		{"sixty-eight",		68},
		{"sixty-nine",		69},

		{"seventy",			70},
		{"seventy-one",		71},
		{"seventy-two",		72},
		{"seventy-three",	73},
		{"seventy-four",	74},
		{"seventy-five",	75},
		{"seventy-six",		76},
		{"seventy-seven",	77},
		{"seventy-eight",	78},
		{"seventy-nine",	79},

		{"eighty",			80},
		{"eighty-one",		81},
		{"eighty-two",		82},
		{"eighty-three",	83},
		{"eighty-four",		84},
		{"eighty-five",		85},
		{"eighty-six",		86},
		{"eighty-seven",	87},
		{"eighty-eight",	88},
		{"eighty-nine",		89},

		{"ninety",			90},
		{"ninety-one",		91},
		{"ninety-two",		92},
		{"ninety-three",	93},
		{"ninety-four",		94},
		{"ninety-five",		95},
		{"ninety-six",		96},
		{"ninety-seven",	97},
		{"ninety-eight",	98},
		{"ninety-nine",		99},
};

std::map<std::string, int> Token::multipliers = {
		{"hundred",  100},
		{"thousand", 1000},
		{"million",  1000000},
		{"billion",  1000000000},
};

Token::Token(const std::string& word):
word(word)
{
	initialize();
}

Token::Token(unsigned int i):
word(std::to_string(i))
{
	initialize();
}

void Token::toLower(std::string& str) const
{
	std::for_each(str.begin(), str.end(), [](char & c) {
			c = ::tolower(c);
		});
}

void Token::initialize()
{
	std::string rawWord(word);
	toLower(rawWord);

	std::map<std::string,int>::iterator it;

	// Special tokens parsing
	if(rawWord == ZERO)
	{
		value = 0;
		_isZero = true;
	}

	else if(rawWord == AND)
	{
		_isAnd = true;
	}

	else if(rawWord == A)
	{
		_isA = true;
		value = 1;
	}

	else if(rawWord == COMMA)
	{
		_isComma = true;
	}

	else if(rawWord == SPACE)
	{
		_isSpace = true;
	}

	//Check for units
	else if ((it=units.find(rawWord)) != units.end())
	{
		value = it->second;
		_isUnit = true;
	}

	//Check for special values from 10 to 19
	else if ((it=fromTenToNineteen.find(rawWord)) != fromTenToNineteen.end())
	{
		value = it->second;
		_isFromTenToNineteen = true;
	}

	//Check for special values from 20 to 99
	else if ((it=fromTwentyToNinetyNine.find(rawWord)) != fromTwentyToNinetyNine.end())
	{
		value = it->second;
		_isFromTwentyToNinetyNine = true;
	}

	//Check for multipliers
	else if ((it=multipliers.find(rawWord)) != multipliers.end())
	{
		value = it->second;
		_isMultiplier = true;
	}

	//check if it is already in numeric format

	else
	{
		try
		{
			value = std::stoi(rawWord);
			_isNumericFormat = true;
		}
		catch (const std::invalid_argument& ia)
		{

		}
	}
}

Token::Token(const Token& t):
word(t.word),
value{t.value},
_isZero{t._isZero},
_isUnit{t._isUnit},
_isFromTenToNineteen{t._isFromTenToNineteen},
_isFromTwentyToNinetyNine{t._isFromTwentyToNinetyNine},
_isMultiplier{t._isMultiplier},
_isAnd{t._isAnd},
_isA{t._isA},
_isComma{t._isComma},
_isSpace{t._isSpace},
_isNumericFormat{t._isNumericFormat}
{
}

Token::Token(const Token&& t):
word(std::move(t.word)),
value{t.value},
_isZero{t._isZero},
_isUnit{t._isUnit},
_isFromTenToNineteen{t._isFromTenToNineteen},
_isFromTwentyToNinetyNine{t._isFromTwentyToNinetyNine},
_isMultiplier{t._isMultiplier},
_isAnd{t._isAnd},
_isA{t._isA},
_isComma{t._isComma},
_isSpace{t._isSpace},
_isNumericFormat{t._isNumericFormat}
{
}

Token& Token::operator=(const Token& t)
{
	word = t.word;
	value = t.value;
	_isZero = t._isZero;
	_isUnit = t._isUnit;
	_isFromTenToNineteen = t._isFromTenToNineteen;
	_isFromTwentyToNinetyNine = t._isFromTwentyToNinetyNine;
	_isMultiplier = t._isMultiplier;
	_isAnd = t._isAnd;
	_isA = t._isA;
	_isComma = t._isComma;
	_isSpace = t._isSpace;
	_isNumericFormat = t._isNumericFormat;

	return *this;
}

Token& Token::operator=(const Token&& t)
{
	word = std::move(t.word);
	value = t.value;
	_isZero = t._isZero;
	_isUnit = t._isUnit;
	_isFromTenToNineteen = t._isFromTenToNineteen;
	_isFromTwentyToNinetyNine = t._isFromTwentyToNinetyNine;
	_isMultiplier = t._isMultiplier;
	_isA = t._isA;
	_isComma = t._isComma;
	_isSpace = t._isSpace;
	_isNumericFormat = t._isNumericFormat;

	return *this;
}

Token Token::toNumericFormat() const
{
	if(isNumber())
	{
		return Token(std::to_string(value));
	}
	return *this;
}

int Token::getValue() const
{
	return value;
}

std::string Token::getWord() const
{
	return word;
}

bool Token::isZero() const
{
	return _isZero;
}

bool Token::isUnit() const
{
	return _isUnit;
}

bool Token::isFromTenToNineteen() const
{
	return _isFromTenToNineteen;
}

bool Token::isFromTwentyToNinetyNine() const
{
	return _isFromTwentyToNinetyNine;
}

bool Token::isMultiplier() const
{
	return _isMultiplier;
}

bool Token::isAnd() const
{
	return _isAnd;
}

bool Token::isA() const
{
	return _isA;
}

bool Token::isComma() const
{
	return _isComma;
}

bool Token::isSpace() const
{
	return _isSpace;
}

bool Token::isNumber() const
{
	return _isUnit
			|| _isZero
			|| _isFromTenToNineteen
			|| _isFromTwentyToNinetyNine
			|| _isNumericFormat;
}
