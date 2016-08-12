#include "Location.h"
#include <stdexcept>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(Location_)

	using namespace std;
	using namespace Chess;

	BOOST_AUTO_TEST_SUITE(Location_constructor)

		BOOST_AUTO_TEST_CASE(constructor_InRange_Success)
		{
			BOOST_CHECK_EQUAL((int) Location(algebraicLocation::a4), (int) algebraicLocation::a4);
			BOOST_CHECK_EQUAL((int) Location(algebraicLocation::b3), (int) algebraicLocation::b3);
			BOOST_CHECK_EQUAL((int) Location(algebraicLocation::e1), (int) algebraicLocation::e1);
			BOOST_CHECK_EQUAL((int) Location(algebraicLocation::f6), (int) algebraicLocation::f6);
			BOOST_CHECK_EQUAL((int) Location(algebraicLocation::g2), (int) algebraicLocation::g2);
			BOOST_CHECK_EQUAL((int) Location(algebraicLocation::h7), (int) algebraicLocation::h7);
		}

		BOOST_AUTO_TEST_CASE(constructor_OutOfRange_Exception)
		{
			BOOST_CHECK_THROW(new Location(algebraicLocation::UNDEFINED), out_of_range);
			BOOST_CHECK_THROW(new Location(algebraicLocation::MAX), out_of_range);
		}

	BOOST_AUTO_TEST_SUITE_END() 

	BOOST_AUTO_TEST_SUITE(Location_fromString)

		BOOST_AUTO_TEST_CASE(fromString_CleanLowerCaseInput_Success)
		{
			BOOST_CHECK_EQUAL((int) Location("a4"), (int) algebraicLocation::a4);
			BOOST_CHECK_EQUAL((int) Location("b3"), (int) algebraicLocation::b3);
			BOOST_CHECK_EQUAL((int) Location("e1"), (int) algebraicLocation::e1);
			BOOST_CHECK_EQUAL((int) Location("f6"), (int) algebraicLocation::f6);
			BOOST_CHECK_EQUAL((int) Location("g2"), (int) algebraicLocation::g2);
			BOOST_CHECK_EQUAL((int) Location("h7"), (int) algebraicLocation::h7);
		}

		BOOST_AUTO_TEST_CASE(fromString_CleanUpperCaseInput_Success)
		{
			BOOST_CHECK_EQUAL((int) Location("A4"), (int)algebraicLocation::a4);
			BOOST_CHECK_EQUAL((int) Location("B3"), (int) algebraicLocation::b3);
			BOOST_CHECK_EQUAL((int) Location("E1"), (int) algebraicLocation::e1);
			BOOST_CHECK_EQUAL((int) Location("F6"), (int) algebraicLocation::f6);
			BOOST_CHECK_EQUAL((int) Location("G2"), (int) algebraicLocation::g2);
			BOOST_CHECK_EQUAL((int) Location("H7"), (int) algebraicLocation::h7);
		}

		BOOST_AUTO_TEST_CASE(fromString_NonTrimmedVariCaseInput_Success)
		{
			BOOST_CHECK_EQUAL((int) Location("     a4 "), (int) algebraicLocation::a4);
			BOOST_CHECK_EQUAL((int) Location("   \nE1\t   "), (int) algebraicLocation::e1);
			BOOST_CHECK_EQUAL((int) Location("\n\t\th7\t\n   "), (int) algebraicLocation::h7);
		}

		BOOST_AUTO_TEST_CASE(fromString_InvalidLength_Exception)
		{
			BOOST_CHECK_THROW(Location("\ta43\r\n"), invalid_argument);
		}

		BOOST_AUTO_TEST_CASE(fromString_InvalidContent_Exception)
		{
			BOOST_CHECK_THROW(Location("\thello world\r\n"), invalid_argument);
		}

		/* TODO : ASSERTS */

	BOOST_AUTO_TEST_SUITE_END() 

	BOOST_AUTO_TEST_SUITE(Location_toString)

		BOOST_AUTO_TEST_CASE(toString_Success)
		{
			BOOST_CHECK_EQUAL(Location(algebraicLocation::a4).toString(), "A4");
			BOOST_CHECK_EQUAL(Location(algebraicLocation::b3).toString(), "B3");
			BOOST_CHECK_EQUAL(Location(algebraicLocation::e1).toString(), "E1");
			BOOST_CHECK_EQUAL(Location(algebraicLocation::f6).toString(), "F6");
			BOOST_CHECK_EQUAL(Location(algebraicLocation::g2).toString(), "G2");
			BOOST_CHECK_EQUAL(Location(algebraicLocation::h7).toString(), "H7");
		}

	BOOST_AUTO_TEST_SUITE_END() 

BOOST_AUTO_TEST_SUITE_END() 