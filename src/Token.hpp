/*
 * Token.hpp
 *
 *  Created on: 3 nov. 2020
 *      Author: ruben
 */

#pragma once
#include <string>
#include <map>


class Token
{
public:
	Token(const std::string& word);
	Token(unsigned int i);
	Token(const Token& t);
	Token(const Token&& t);

	Token& operator=(const Token& t);
	Token& operator=(const Token&& t);

	Token toNumericFormat() const;

	int getValue() const;
	std::string getWord() const;
	bool isZero() const;
	bool isUnit() const;
	bool isMultiplier() const;
	bool isFromTenToNineteen() const;
	bool isFromTwentyToNinetyNine() const;
	bool isAnd() const;
	bool isA() const;
	bool isComma() const;
	bool isSpace() const;
	bool isNumber() const;

private:
	std::string word;
	int value = -1;
	bool _isZero = false;
	bool _isUnit = false;
	bool _isFromTenToNineteen = false;
	bool _isFromTwentyToNinetyNine = false;
	bool _isMultiplier = false;
	bool _isAnd = false;
	bool _isA = false;
	bool _isComma = false;
	bool _isSpace = false;
	bool _isNumericFormat = false;

	void toLower(std::string& str) const;
	void initialize();
	static std::map<std::string, int> units;
	static std::map<std::string, int> fromTenToNineteen;
	static std::map<std::string, int> fromTwentyToNinetyNine;
	static std::map<std::string, int> multipliers;
	static std::string ZERO;
	static std::string AND;
	static std::string A;
	static std::string COMMA;
	static std::string SPACE;
};
