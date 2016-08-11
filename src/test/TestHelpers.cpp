#include <vector>
#include <string>
#include "Helpers.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(HelpersTest)

using namespace std;
using namespace Chess::Helpers;

struct HelpersTestFixture
{
	vector<string> testStrings;
	HelpersTestFixture(string base)
	{
		vector<string> appendages = { "", "   ", "\t\t\t", "\n\n\n", "\r\r\r", "     \r\n\t\t" };
		for (auto prefix = appendages.cbegin(); prefix != appendages.cend(); prefix++)
			for (auto suffix = appendages.cbegin(); suffix != appendages.cend(); suffix++)
				testStrings.push_back(*prefix + base + *suffix);
	}
};

BOOST_AUTO_TEST_CASE(trimmed_OneWord_Success)
{
	string testString = "foo bar";
	HelpersTestFixture fixture(testString);
	for (auto itr = fixture.testStrings.cbegin(); itr != fixture.testStrings.cend(); itr++)
		BOOST_CHECK_EQUAL(trimmed(*itr), testString);
}

BOOST_AUTO_TEST_CASE(trimmed_MultipleWords_Success)
{
	string testString = "foo bar";
	HelpersTestFixture fixture(testString);
	for (auto itr = fixture.testStrings.cbegin(); itr != fixture.testStrings.cend(); itr++)
		BOOST_CHECK_EQUAL(trimmed(*itr), testString);
}

BOOST_AUTO_TEST_SUITE_END()