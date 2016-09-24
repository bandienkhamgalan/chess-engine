#include <vector>
#include <string>
#include "Helpers.hpp"
#include "gtest/gtest.h"

using namespace std;
using namespace Chess::Helpers;

vector<string> generateHelpersTrimmedTestStrings(string base, vector<string> appendages = { "", "   ", "\t\t\t", "\n\n\n", "\r\r\r", "     \r\n\t\t" })
{
	vector<string> testStrings;
	for (auto prefix : appendages)
		for (auto suffix : appendages)
			testStrings.push_back(prefix + base + suffix);
	return testStrings;
}

TEST(Helpers_trimmed, AllSpaces_Success)
{
	EXPECT_EQ(trimmed(""), "");
	EXPECT_EQ(trimmed("                 "), "");
	EXPECT_EQ(trimmed("                                                      "), "");
};

TEST(Helpers_trimmed, OneWord_Success)
{
	string testString = "foo";
	for (auto itr : generateHelpersTrimmedTestStrings(testString))
		EXPECT_EQ(trimmed(itr), testString);
};

TEST(Helpers_trimmed, MultipleWords_Success)
{
	string testString = "foo bar";
	for (auto itr : generateHelpersTrimmedTestStrings(testString))
		EXPECT_EQ(trimmed(itr), testString);
};

TEST(Helpers_lower, EnglishSentence_Success)
{
	EXPECT_EQ(lower("The QUicK bRown fox JUMPED oVeR TheLazy DOGS! 01234567890*934"), "the quick brown fox jumped over thelazy dogs! 01234567890*934");
};

TEST(Helpers_sprint, ConcatenatesStrings)
{
	EXPECT_EQ(sprint("one word"), "one word");
	EXPECT_EQ(sprint("simple", "concat"), "simpleconcat");
	EXPECT_EQ(sprint("simple", "three param", "concat"), "simplethree paramconcat");
	EXPECT_EQ(sprint("simple", "three param", "concat"), "simplethree paramconcat");
	EXPECT_EQ(sprint(234), "234");
	EXPECT_EQ(sprint(234, "concat"), "234concat");
	EXPECT_EQ(sprint("simple", 19285, "concat"), "simple19285concat");
	EXPECT_EQ(sprint('a', 'b', 'c', 0.125), "abc0.125");
};

TEST(Helpers_split, Spaces_ReturnsEmptyVector)
{
	auto splitCheck = split("");
	EXPECT_EQ(splitCheck.size(), 0);
	splitCheck = split("     ");
	EXPECT_EQ(splitCheck.size(), 0);
	splitCheck = split("\n\n\r\t    \t\t\n");
	EXPECT_EQ(splitCheck.size(), 0);
};

TEST(Helpers_split, NonSpaceString_Success)
{
	auto splitCheck = split("   one  ");
	EXPECT_EQ(splitCheck.size(), 1);
	EXPECT_EQ(splitCheck[0], "one");
	
	splitCheck = split("\r\n\t\tone\n");
	EXPECT_EQ(splitCheck.size(), 1);
	EXPECT_EQ(splitCheck[0], "one");

	splitCheck = split("\t   one\ttwo\tthree\r\n");
	EXPECT_EQ(splitCheck.size(), 3);
	EXPECT_EQ(splitCheck[0], "one");
	EXPECT_EQ(splitCheck[1], "two");
	EXPECT_EQ(splitCheck[2], "three");

	splitCheck = split("\na\nb\nc\n\td");
	EXPECT_EQ(splitCheck.size(), 4);
	EXPECT_EQ(splitCheck[0], "a");
	EXPECT_EQ(splitCheck[1], "b");
	EXPECT_EQ(splitCheck[2], "c");
	EXPECT_EQ(splitCheck[3], "d");
}