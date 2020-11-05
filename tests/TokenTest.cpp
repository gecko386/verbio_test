/*
 * testToken.cpp
 *
 *  Created on: 4 nov. 2020
 *      Author: ruben
 */

#include <gtest/gtest.h>
#include "../src/Token.hpp"

//special cases

TEST(TokenTest, BuildTokenWithWord)
{
	std::string word("HEEELLLOOOO");
	Token sutToken(word);

	EXPECT_EQ(sutToken.getWord(), word);
	EXPECT_EQ(sutToken.getValue(), -1);
}

TEST(TokenTest, TokenParseZero)
{
	std::string word("zero");
	Token sutToken(word);

	EXPECT_EQ(sutToken.getWord(), word);
	EXPECT_TRUE(sutToken.isZero());
	EXPECT_TRUE(sutToken.isNumber());
	EXPECT_EQ(sutToken.getValue(), 0);
}

TEST(TokenTest, TokenParseZeroUpperCase)
{
	std::string word("ZERO");
	Token sutToken(word);

	EXPECT_EQ(sutToken.getWord(), word);
	EXPECT_TRUE(sutToken.isZero());
	EXPECT_TRUE(sutToken.isNumber());
	EXPECT_EQ(sutToken.getValue(), 0);
}

TEST(TokenTest, TokenParseAnd)
{
	std::string word("and");
	Token sutToken(word);

	EXPECT_EQ(sutToken.getWord(), word);
	EXPECT_TRUE(sutToken.isAnd());
	EXPECT_FALSE(sutToken.isNumber());
	EXPECT_EQ(sutToken.getValue(), -1);
}

TEST(TokenTest, TokenParseAndUpperCase)
{
	std::string word("AND");
	Token sutToken(word);

	EXPECT_EQ(sutToken.getWord(), word);
	EXPECT_TRUE(sutToken.isAnd());
	EXPECT_FALSE(sutToken.isNumber());
	EXPECT_EQ(sutToken.getValue(), -1);
}

TEST(TokenTest, TokenParseA)
{
	std::string word("a");
	Token sutToken(word);

	EXPECT_EQ(sutToken.getWord(), word);
	EXPECT_TRUE(sutToken.isA());
	EXPECT_FALSE(sutToken.isNumber());
	EXPECT_EQ(sutToken.getValue(), 1);
}

TEST(TokenTest, TokenParseAUpperCase)
{
	std::string word("A");
	Token sutToken(word);

	EXPECT_EQ(sutToken.getWord(), word);
	EXPECT_TRUE(sutToken.isA());
	EXPECT_FALSE(sutToken.isNumber());
	EXPECT_EQ(sutToken.getValue(), 1);
}

TEST(TokenTest, TokenParseComma)
{
	std::string word(",");
	Token sutToken(word);

	EXPECT_EQ(sutToken.getWord(), word);
	EXPECT_TRUE(sutToken.isComma());
	EXPECT_FALSE(sutToken.isNumber());
	EXPECT_EQ(sutToken.getValue(), -1);
}

TEST(TokenTest, TokenParseSpace)
{
	std::string word(" ");
	Token sutToken(word);

	EXPECT_EQ(sutToken.getWord(), word);
	EXPECT_TRUE(sutToken.isSpace());
	EXPECT_FALSE(sutToken.isNumber());
	EXPECT_EQ(sutToken.getValue(), -1);
}

TEST(TokenTest, TokenParseToNumericFormat)
{
	std::string word("twenty-five");
	Token sutToken(word);

	Token t=sutToken.toNumericFormat();
	EXPECT_EQ(t.getWord(), "25");
	EXPECT_TRUE(t.isNumber());
	EXPECT_EQ(t.getValue(), 25);
}

TEST(TokenTest, TokenParseFromNumericFormat)
{
	std::string word("158");
	Token sutToken(word);

	EXPECT_EQ(sutToken.getWord(), "158");
	EXPECT_TRUE(sutToken.isNumber());
	EXPECT_EQ(sutToken.getValue(), 158);
}

//units

class TokenTestUnitsTestFixture:public ::testing::TestWithParam<std::pair<std::string, int> > {

};

TEST_P(TokenTestUnitsTestFixture, TokenParseUnits)
{


	std::string word(GetParam().first);
	Token sutToken(word);

	EXPECT_EQ(sutToken.getWord(), word);
	EXPECT_TRUE(sutToken.isUnit());
	EXPECT_EQ(sutToken.getValue(), GetParam().second);
}


INSTANTIATE_TEST_CASE_P(
		TokenTest,
		TokenTestUnitsTestFixture,
        ::testing::Values(
			std::pair<std::string, int>{"one",   1},
			std::pair<std::string, int>{"two",   2},
			std::pair<std::string, int>{"three", 3},
			std::pair<std::string, int>{"four",  4},
			std::pair<std::string, int>{"five",  5},
			std::pair<std::string, int>{"six",   6},
			std::pair<std::string, int>{"seven", 7},
			std::pair<std::string, int>{"eight", 8},
			std::pair<std::string, int>{"nine",  9}
        ));

//10-19
class TokenTestFromtenToNineteenTestFixture:public ::testing::TestWithParam<std::pair<std::string, int> > {

};


TEST_P(TokenTestFromtenToNineteenTestFixture, TokenParseFromTenToNineTeen)
{
	std::string word(GetParam().first);
	Token sutToken(word);

	EXPECT_EQ(sutToken.getWord(), word);
	EXPECT_TRUE(sutToken.isFromTenToNineteen());
	EXPECT_EQ(sutToken.getValue(), GetParam().second);
}

INSTANTIATE_TEST_CASE_P(
		TokenTest,
		TokenTestFromtenToNineteenTestFixture,
        ::testing::Values(
        	std::pair<std::string, int>{"ten",       10},
			std::pair<std::string, int>{"eleven",    11},
			std::pair<std::string, int>{"twelve",    12},
			std::pair<std::string, int>{"thirteen",  13},
			std::pair<std::string, int>{"fourteen",  14},
			std::pair<std::string, int>{"fifteen",   15},
			std::pair<std::string, int>{"sixteen",   16},
			std::pair<std::string, int>{"seventeen", 17},
			std::pair<std::string, int>{"eighteen",  18},
			std::pair<std::string, int>{"nineteen",  19}
        ));


//20-99 Due to gtest limitations splitting this case is needed

//20-59
class TokenTestFromTwentyToNinetyNineTestFixture_I:public ::testing::TestWithParam<std::pair<std::string, int> > {

};

TEST_P(TokenTestFromTwentyToNinetyNineTestFixture_I, TokenParseFromTwentyToNinetyNine)
{
	std::string word(GetParam().first);
	Token sutToken(word);

	EXPECT_EQ(sutToken.getWord(), word);
	EXPECT_TRUE(sutToken.isFromTwentyToNinetyNine());
	EXPECT_EQ(sutToken.getValue(), GetParam().second);
}

INSTANTIATE_TEST_CASE_P(
		TokenTest,
		TokenTestFromTwentyToNinetyNineTestFixture_I,
        ::testing::Values(
			std::pair<std::string, int>{"twenty",			20},
			std::pair<std::string, int>{"twenty-one",		21},
			std::pair<std::string, int>{"twenty-two",		22},
			std::pair<std::string, int>{"twenty-three",		23},
			std::pair<std::string, int>{"twenty-four",		24},
			std::pair<std::string, int>{"twenty-five",		25},
			std::pair<std::string, int>{"twenty-six",		26},
			std::pair<std::string, int>{"twenty-seven",		27},
			std::pair<std::string, int>{"twenty-eight",		28},
			std::pair<std::string, int>{"twenty-nine",		29},
			std::pair<std::string, int>{"thirty",			30},
			std::pair<std::string, int>{"thirty-one",		31},
			std::pair<std::string, int>{"thirty-two",		32},
			std::pair<std::string, int>{"thirty-three",		33},
			std::pair<std::string, int>{"thirty-four",		34},
			std::pair<std::string, int>{"thirty-five",		35},
			std::pair<std::string, int>{"thirty-six",		36},
			std::pair<std::string, int>{"thirty-seven",		37},
			std::pair<std::string, int>{"thirty-eight",		38},
			std::pair<std::string, int>{"thirty-nine",		39},
			std::pair<std::string, int>{"forty",			40},
			std::pair<std::string, int>{"forty-one",		41},
			std::pair<std::string, int>{"forty-two",		42},
			std::pair<std::string, int>{"forty-three",		43},
			std::pair<std::string, int>{"forty-four",		44},
			std::pair<std::string, int>{"forty-five",		45},
			std::pair<std::string, int>{"forty-six",		46},
			std::pair<std::string, int>{"forty-seven",		47},
			std::pair<std::string, int>{"forty-eight",		48},
			std::pair<std::string, int>{"forty-nine",		49},
			std::pair<std::string, int>{"fifty",			50},
			std::pair<std::string, int>{"fifty-one",		51},
			std::pair<std::string, int>{"fifty-two",		52},
			std::pair<std::string, int>{"fifty-three",		53},
			std::pair<std::string, int>{"fifty-four",		54},
			std::pair<std::string, int>{"fifty-five",		55},
			std::pair<std::string, int>{"fifty-six",		56},
			std::pair<std::string, int>{"fifty-seven",		57},
			std::pair<std::string, int>{"fifty-eight",		58},
			std::pair<std::string, int>{"fifty-nine",		59}
        ));

//60-99
class TokenTestFromTwentyToNinetyNineTestFixture_II:public ::testing::TestWithParam<std::pair<std::string, int> > {

};

TEST_P(TokenTestFromTwentyToNinetyNineTestFixture_II, TokenParseFromTwentyToNinetyNine)
{
	std::string word(GetParam().first);
	Token sutToken(word);

	EXPECT_EQ(sutToken.getWord(), word);
	EXPECT_TRUE(sutToken.isFromTwentyToNinetyNine());
	EXPECT_EQ(sutToken.getValue(), GetParam().second);
}

INSTANTIATE_TEST_CASE_P(
		TokenTest,
		TokenTestFromTwentyToNinetyNineTestFixture_II,
        ::testing::Values(
			std::pair<std::string, int>{"sixty",			60},
			std::pair<std::string, int>{"sixty-one",		61},
			std::pair<std::string, int>{"sixty-two",		62},
			std::pair<std::string, int>{"sixty-three",		63},
			std::pair<std::string, int>{"sixty-four",		64},
			std::pair<std::string, int>{"sixty-five",		65},
			std::pair<std::string, int>{"sixty-six",		66},
			std::pair<std::string, int>{"sixty-seven",		67},
			std::pair<std::string, int>{"sixty-eight",		68},
			std::pair<std::string, int>{"sixty-nine",		69},
			std::pair<std::string, int>{"seventy",			70},
			std::pair<std::string, int>{"seventy-one",		71},
			std::pair<std::string, int>{"seventy-two",		72},
			std::pair<std::string, int>{"seventy-three",	73},
			std::pair<std::string, int>{"seventy-four",		74},
			std::pair<std::string, int>{"seventy-five",		75},
			std::pair<std::string, int>{"seventy-six",		76},
			std::pair<std::string, int>{"seventy-seven",	77},
			std::pair<std::string, int>{"seventy-eight",	78},
			std::pair<std::string, int>{"seventy-nine",		79},
			std::pair<std::string, int>{"eighty",			80},
			std::pair<std::string, int>{"eighty-one",		81},
			std::pair<std::string, int>{"eighty-two",		82},
			std::pair<std::string, int>{"eighty-three",		83},
			std::pair<std::string, int>{"eighty-four",		84},
			std::pair<std::string, int>{"eighty-five",		85},
			std::pair<std::string, int>{"eighty-six",		86},
			std::pair<std::string, int>{"eighty-seven",		87},
			std::pair<std::string, int>{"eighty-eight",		88},
			std::pair<std::string, int>{"eighty-nine",		89},
			std::pair<std::string, int>{"ninety",			90},
			std::pair<std::string, int>{"ninety-one",		91},
			std::pair<std::string, int>{"ninety-two",		92},
			std::pair<std::string, int>{"ninety-three",		93},
			std::pair<std::string, int>{"ninety-four",		94},
			std::pair<std::string, int>{"ninety-five",		95},
			std::pair<std::string, int>{"ninety-six",		96},
			std::pair<std::string, int>{"ninety-seven",		97},
			std::pair<std::string, int>{"ninety-eight",		98},
			std::pair<std::string, int>{"ninety-nine",		99}
        ));


//multipliers
class TokenTestMultiplierTestFixture:public ::testing::TestWithParam<std::pair<std::string, int> > {

};


TEST_P(TokenTestMultiplierTestFixture, TokenParseMultipliers)
{
	std::string word(GetParam().first);
	Token sutToken(word);

	EXPECT_EQ(sutToken.getWord(), word);
	EXPECT_TRUE(sutToken.isMultiplier());
	EXPECT_EQ(sutToken.getValue(), GetParam().second);
}

INSTANTIATE_TEST_CASE_P(
		TokenTest,
		TokenTestMultiplierTestFixture,
        ::testing::Values(
			std::pair<std::string, int>{"hundred",  100},
			std::pair<std::string, int>{"thousand", 1000},
			std::pair<std::string, int>{"million",  1000000},
			std::pair<std::string, int>{"billion",  1000000000}
        ));





