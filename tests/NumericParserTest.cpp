/*
 * NumericParserTest.cpp
 *
 *  Created on: 5 nov. 2020
 *      Author: ruben
 */

#include <gtest/gtest.h>
#include "../src/NumericParser.hpp"

class NumericParserTestFixtureI:public ::testing::TestWithParam<std::pair<std::string, std::string> >
{
public:
	NumericParserTestFixtureI():
		sutNumericParser{}
	{}
protected:

	NumericParser sutNumericParser;
};

TEST_P(NumericParserTestFixtureI, ParseBasic)
{

	std::string input = GetParam().first;
	std::string expected = GetParam().second;

	std::string output = sutNumericParser.parse(input);

	EXPECT_EQ(expected, output);
}


INSTANTIATE_TEST_CASE_P(
		NumericParserTest,
		NumericParserTestFixtureI,
        ::testing::Values(
			std::pair<std::string, std::string>{"one",   		"1"},
			std::pair<std::string, std::string>{"two",   		"2"},
			std::pair<std::string, std::string>{"three", 		"3"},
			std::pair<std::string, std::string>{"four",  		"4"},
			std::pair<std::string, std::string>{"five",  		"5"},
			std::pair<std::string, std::string>{"six",   		"6"},
			std::pair<std::string, std::string>{"seven", 		"7"},
			std::pair<std::string, std::string>{"eight", 		"8"},
			std::pair<std::string, std::string>{"nine",  		"9"},
			std::pair<std::string, std::string>{"ten",   		"10"},
			std::pair<std::string, std::string>{"twelve",   	"12"},
			std::pair<std::string, std::string>{"twenty-two",   "22"},
			std::pair<std::string, std::string>{"sixty-four",   "64"},
			std::pair<std::string, std::string>{"ninety-nine",  "99"}
        ));

class NumericParserTestFixtureII:public ::testing::TestWithParam<std::pair<std::string, std::string> >
{
public:
	NumericParserTestFixtureII():
		sutNumericParser{}
	{}
protected:

	NumericParser sutNumericParser;
};

TEST_P(NumericParserTestFixtureII, ParseHundreds)
{

	std::string input = GetParam().first;
	std::string expected = GetParam().second;

	std::string output = sutNumericParser.parse(input);

	EXPECT_EQ(expected, output);
}

INSTANTIATE_TEST_CASE_P(
		NumericParserTest,
		NumericParserTestFixtureII,
        ::testing::Values(
			std::pair<std::string, std::string>{"one hundred and five",   				"105"},
			std::pair<std::string, std::string>{"six hundred and twelve",   			"612"},
			std::pair<std::string, std::string>{"five hundred and twenty-two",   		"522"},
			std::pair<std::string, std::string>{"eight hundred sixty-four",   			"864"}
        ));

class NumericParserTestFixtureIII:public ::testing::TestWithParam<std::pair<std::string, std::string> >
{
public:
	NumericParserTestFixtureIII():
		sutNumericParser{}
	{}
protected:

	NumericParser sutNumericParser;
};

TEST_P(NumericParserTestFixtureIII, ParseThousands)
{

	std::string input = GetParam().first;
	std::string expected = GetParam().second;

	std::string output = sutNumericParser.parse(input);

	EXPECT_EQ(expected, output);
}

INSTANTIATE_TEST_CASE_P(
		NumericParserTest,
		NumericParserTestFixtureIII,
        ::testing::Values(
			std::pair<std::string, std::string>{"one thousand and five",   							"1005"},
			std::pair<std::string, std::string>{"eight thousand, six hundred and twelve",   		"8612"},
			std::pair<std::string, std::string>{"four thousand, five hundred and sixty-seven",   	"4567"},
			std::pair<std::string, std::string>{"four hundred and seventy-two thousand, five hundred and sixty-seven",   	"472567"}
        ));

class NumericParserTestFixtureIV:public ::testing::TestWithParam<std::pair<std::string, std::string> >
{
public:
	NumericParserTestFixtureIV():
		sutNumericParser{}
	{}
protected:

	NumericParser sutNumericParser;
};

TEST_P(NumericParserTestFixtureIV, ParseMillions)
{

	std::string input = GetParam().first;
	std::string expected = GetParam().second;

	std::string output = sutNumericParser.parse(input);

	EXPECT_EQ(expected, output);
}

INSTANTIATE_TEST_CASE_P(
		NumericParserTest,
		NumericParserTestFixtureIV,
        ::testing::Values(
			std::pair<std::string, std::string>{"one million and five",   										"1000005"},
			std::pair<std::string, std::string>{"eight million, six hundred and twelve",   						"8000612"},
			std::pair<std::string, std::string>{"four million, five hundred and sixty-seven",   				"4000567"},
			std::pair<std::string, std::string>{"six hundred and five million, five hundred and sixty-seven",   "605000567"},
			std::pair<std::string, std::string>{"seven hundred and thirty-two million, one hundred and fifty thousand, five hundred and sixty-seven",   "732150567"}
        ));


class NumericParserTestFixtureV:public ::testing::TestWithParam<std::pair<std::string, std::string> >
{
public:
	NumericParserTestFixtureV():
		sutNumericParser{}
	{}
protected:

	NumericParser sutNumericParser;
};
TEST_P(NumericParserTestFixtureV, Billion)
{

	std::string input = GetParam().first;
	std::string expected = GetParam().second;

	std::string output = sutNumericParser.parse(input);

	EXPECT_EQ(expected, output);
}

INSTANTIATE_TEST_CASE_P(
		NumericParserTest,
		NumericParserTestFixtureV,
        ::testing::Values(
			std::pair<std::string, std::string>{"one billion",   										"1000000000"},
			std::pair<std::string, std::string>{"a billion",   											"1000000000"}
        ));


class NumericParserTestFixture:public ::testing::Test
{
public:
	NumericParserTestFixture():
		sutNumericParser{}
	{}
protected:

	NumericParser sutNumericParser;
};

TEST_F(NumericParserTestFixture, year)
{

	std::string input = "twenty twenty-four";
	std::string expected = "2024";

	std::string output = sutNumericParser.parse(input);

	EXPECT_EQ(expected, output);
}

TEST_F(NumericParserTestFixture, CommasAtBeginning)
{

	std::string input = ", seven hundred and thirty-two million, one hundred and fifty thousand, five hundred and sixty-seven";
	std::string expected = ", 732150567";

	std::string output = sutNumericParser.parse(input);

	EXPECT_EQ(expected, output);
}

TEST_F(NumericParserTestFixture, CommasAtEnd)
{

	std::string input = "seven hundred and thirty-two million, one hundred and fifty thousand, five hundred and sixty-seven,";
	std::string expected = "732150567 , ";

	std::string output = sutNumericParser.parse(input);

	EXPECT_EQ(expected, output);
}

TEST_F(NumericParserTestFixture, NumbersInSentence)
{
	std::string input = "I have two daughters and one cat";
	std::string expected = "I have 2 daughters and 1 cat";

	std::string output = sutNumericParser.parse(input);

	EXPECT_EQ(expected, output);
}

TEST_F(NumericParserTestFixture, NumbersInSentenceWithDelimitators)
{
	std::string input = "one, two and three are numbers";
	std::string expected = "1 , 2 and 3 are numbers";

	std::string output = sutNumericParser.parse(input);

	EXPECT_EQ(expected, output);
}
