#include <vector>
#include <string>
#include "Helpers.hpp"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(Helpers_)

	BOOST_AUTO_TEST_SUITE(Helpers_trimmed)

		using namespace std;
		using namespace Chess::Helpers;

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

		using namespace std;
		using namespace Chess::Helpers;

		BOOST_AUTO_TEST_CASE(lower_EnglishSentence_Success)
		{
			BOOST_CHECK_EQUAL(lower("The QUicK bRown fox JUMPED oVeR TheLazy DOGS! 01234567890*934"), "the quick brown fox jumped over thelazy dogs! 01234567890*934");
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()