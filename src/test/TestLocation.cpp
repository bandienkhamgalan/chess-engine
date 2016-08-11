#include "Location.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(LocationTest)

using namespace std;
using namespace Chess;

BOOST_AUTO_TEST_CASE(fromString_CleanLowerCaseInput_Success)
{
   BOOST_CHECK_EQUAL((int)Location("a4"), (int)algebraicLocation::a4);
   BOOST_CHECK_EQUAL((int) Location("e1"), (int) algebraicLocation::e1);
   BOOST_CHECK_EQUAL((int) Location("h7"), (int) algebraicLocation::h7);
}

BOOST_AUTO_TEST_CASE(fromString_CleanUpperCaseInput_Success)
{
   BOOST_CHECK_EQUAL((int) Location("A4"), (int) algebraicLocation::a4);
   BOOST_CHECK_EQUAL((int) Location("E1"), (int) algebraicLocation::e1);
   BOOST_CHECK_EQUAL((int) Location("H7"), (int) algebraicLocation::h7);
}

BOOST_AUTO_TEST_CASE(fromString_NonTrimmedInput_Success)
{
   BOOST_CHECK_EQUAL((int) Location("     A4 "), (int) algebraicLocation::a4);
   BOOST_CHECK_EQUAL((int) Location("   \ne1\t   "), (int) algebraicLocation::e1);
   BOOST_CHECK_EQUAL((int) Location("\n\t\tH7\t\n   "), (int) algebraicLocation::h7);
}

BOOST_AUTO_TEST_SUITE_END() 