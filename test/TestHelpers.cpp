#include <vector>
#include <string>
#include "Helpers.hpp"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(Helpers_)

	using namespace std;
	using namespace Chess::Helpers;

	BOOST_AUTO_TEST_SUITE(Helpers_trimmed)

		struct HelpersTrimmedTestFixture
		{
			vector<string> testStrings;
			HelpersTrimmedTestFixture(string base)
			{
				vector<string> appendages = { "", "   ", "\t\t\t", "\n\n\n", "\r\r\r", "     \r\n\t\t" };
				for (auto prefix : appendages)
					for (auto suffix : appendages)
						testStrings.push_back(prefix + base + suffix);
			}
		};

		BOOST_AUTO_TEST_CASE(AllSpaces)
		{
			BOOST_CHECK_EQUAL(trimmed(""), "");
			BOOST_CHECK_EQUAL(trimmed("                 "), "");
			BOOST_CHECK_EQUAL(trimmed("                                                      "), "");
		}

		BOOST_AUTO_TEST_CASE(trimmed_OneWord_Success)
		{
			string testString = "foo bar";
			HelpersTrimmedTestFixture fixture(testString);
			for (auto itr : fixture.testStrings)
				BOOST_CHECK_EQUAL(trimmed(itr), testString);
		}

		BOOST_AUTO_TEST_CASE(trimmed_MultipleWords_Success)
		{
			string testString = "foo bar";
			HelpersTrimmedTestFixture fixture(testString);
			for (auto itr : fixture.testStrings)
				BOOST_CHECK_EQUAL(trimmed(itr), testString);
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(Helpers_lower)

		BOOST_AUTO_TEST_CASE(lower_EnglishSentence_Success)
		{
			BOOST_CHECK_EQUAL(lower("The QUicK bRown fox JUMPED oVeR TheLazy DOGS! 01234567890*934"), "the quick brown fox jumped over thelazy dogs! 01234567890*934");
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(sprint_)

		BOOST_AUTO_TEST_CASE(ConcatenatesStrings)
		{
			BOOST_CHECK_EQUAL(sprint("one word"), "one word");
			BOOST_CHECK_EQUAL(sprint("simple", "concat"), "simpleconcat");
			BOOST_CHECK_EQUAL(sprint("simple", "three param", "concat"), "simplethree paramconcat");
			BOOST_CHECK_EQUAL(sprint("simple", "three param", "concat"), "simplethree paramconcat");
			BOOST_CHECK_EQUAL(sprint(234), "234");
			BOOST_CHECK_EQUAL(sprint(234, "concat"), "234concat");
			BOOST_CHECK_EQUAL(sprint("simple", 19285, "concat"), "simple19285concat");
			BOOST_CHECK_EQUAL(sprint('a', 'b', 'c', 0.125), "abc0.125");
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(split_)

		BOOST_AUTO_TEST_CASE(Spaces_ReturnsEmptyVector)
		{
			auto splitCheck = split("");
			BOOST_CHECK_EQUAL(splitCheck.size(), 0);
			splitCheck = split("     ");
			BOOST_CHECK_EQUAL(splitCheck.size(), 0);
			splitCheck = split("\n\n\r\t    \t\t\n");
			BOOST_CHECK_EQUAL(splitCheck.size(), 0);
		}

		BOOST_AUTO_TEST_CASE(NonSpaceString_Success)
		{
			auto splitCheck = split("   one  ");
			BOOST_CHECK_EQUAL(splitCheck.size(), 1);
			BOOST_CHECK_EQUAL(splitCheck[0], "one");
			splitCheck = split("\r\n\t\tone\n");
			BOOST_CHECK_EQUAL(splitCheck.size(), 1);
			BOOST_CHECK_EQUAL(splitCheck[0], "one");
			splitCheck = split("\t   one\ttwo\tthree\r\n");
			BOOST_CHECK_EQUAL(splitCheck.size(), 3);
			BOOST_CHECK_EQUAL(splitCheck[0], "one");
			BOOST_CHECK_EQUAL(splitCheck[1], "two");
			BOOST_CHECK_EQUAL(splitCheck[2], "three");
			splitCheck = split("\na\nb\nc\n\td");
			BOOST_CHECK_EQUAL(splitCheck.size(), 4);
			BOOST_CHECK_EQUAL(splitCheck[0], "a");
			BOOST_CHECK_EQUAL(splitCheck[1], "b");
			BOOST_CHECK_EQUAL(splitCheck[2], "c");
			BOOST_CHECK_EQUAL(splitCheck[3], "d");
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()