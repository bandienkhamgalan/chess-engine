#include "Location.hpp"
#include <stdexcept>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(Location_)

	using namespace std;
	using namespace Chess;

	BOOST_AUTO_TEST_SUITE(constructor)

		BOOST_AUTO_TEST_CASE(InRange_Success)
		{
			BOOST_CHECK_EQUAL(Location(Location::a4), Location::a4);
			BOOST_CHECK_EQUAL(Location(Location::b3), Location::b3);
			BOOST_CHECK_EQUAL(Location(Location::e1), Location::e1);
			BOOST_CHECK_EQUAL(Location(Location::f6), Location::f6);
			BOOST_CHECK_EQUAL(Location(Location::g2), Location::g2);
			BOOST_CHECK_EQUAL(Location(Location::h7), Location::h7);
		}

		BOOST_AUTO_TEST_CASE(OutOfRange_Exception)
		{
			BOOST_CHECK_THROW(new Location(Location::UNDEFINED), out_of_range);
			BOOST_CHECK_THROW(new Location(Location::MAX), out_of_range);
		}

	BOOST_AUTO_TEST_SUITE_END() 

	BOOST_AUTO_TEST_SUITE(fromString)

		BOOST_AUTO_TEST_CASE(CleanLowerCaseInput_Success)
		{
			BOOST_CHECK_EQUAL(Location("a4"), Location::a4);
			BOOST_CHECK_EQUAL(Location("b8"), Location::b8);
			BOOST_CHECK_EQUAL(Location("e1"), Location::e1);
			BOOST_CHECK_EQUAL(Location("f6"), Location::f6);
			BOOST_CHECK_EQUAL(Location("g2"), Location::g2);
			BOOST_CHECK_EQUAL(Location("h7"), Location::h7);
		}

		BOOST_AUTO_TEST_CASE(CleanUpperCaseInput_Success)
		{
			BOOST_CHECK_EQUAL(Location("A4"), Location::a4);
			BOOST_CHECK_EQUAL(Location("B3"), Location::b3);
			BOOST_CHECK_EQUAL(Location("E1"), Location::e1);
			BOOST_CHECK_EQUAL(Location("F6"), Location::f6);
			BOOST_CHECK_EQUAL(Location("G2"), Location::g2);
			BOOST_CHECK_EQUAL(Location("H7"), Location::h7);
		}

		BOOST_AUTO_TEST_CASE(NonTrimmedVariCaseInput_Success)
		{
			BOOST_CHECK_EQUAL(Location("     a4 "), Location::a4);
			BOOST_CHECK_EQUAL(Location("   \nE1\t   "), Location::e1);
			BOOST_CHECK_EQUAL(Location("\n\t\th7\t\n   "), Location::h7);
		}

		BOOST_AUTO_TEST_CASE(InvalidLength_Exception)
		{
			BOOST_CHECK_THROW(Location("\ta43\r\n"), invalid_argument);
		}

		BOOST_AUTO_TEST_CASE(InvalidContent_Exception)
		{
			BOOST_CHECK_THROW(Location("\thello world\r\n"), invalid_argument);
			BOOST_CHECK_THROW(Location("\ta9\r\n"), out_of_range);
			BOOST_CHECK_THROW(Location("\tA0\r\n"), out_of_range);
			BOOST_CHECK_THROW(Location("\tj8\r\n"), out_of_range);
			BOOST_CHECK_THROW(Location("\tj1\r\n"), out_of_range);
		}

	BOOST_AUTO_TEST_SUITE_END() 

	BOOST_AUTO_TEST_SUITE(fromFileAndRank)

		BOOST_AUTO_TEST_CASE(ValidInput_Success)
		{
			BOOST_CHECK_EQUAL(Location(Location::a, 4), Location::a4);
			BOOST_CHECK_EQUAL(Location(Location::b, 8), Location::b8);
			BOOST_CHECK_EQUAL(Location(Location::e, 1), Location::e1);
			BOOST_CHECK_EQUAL(Location(Location::f, 6), Location::f6);
			BOOST_CHECK_EQUAL(Location(Location::g, 2), Location::g2);
			BOOST_CHECK_EQUAL(Location(Location::h, 7), Location::h7);
			BOOST_CHECK_EQUAL(Location(1, 4), Location::a4);
			BOOST_CHECK_EQUAL(Location(2, 8), Location::b8);
			BOOST_CHECK_EQUAL(Location(5, 1), Location::e1);
			BOOST_CHECK_EQUAL(Location(6, 6), Location::f6);
			BOOST_CHECK_EQUAL(Location(7, 2), Location::g2);
			BOOST_CHECK_EQUAL(Location(8, 7), Location::h7);
		}

		BOOST_AUTO_TEST_CASE(InvalidFile_ThrowsOutOfRangeException)
		{
			BOOST_CHECK_THROW(Location(static_cast<Location::File>(0), 4), out_of_range);
			BOOST_CHECK_THROW(Location(static_cast<Location::File>(9), 3), out_of_range);
		}

		BOOST_AUTO_TEST_CASE(InvalidRank_ThrowsOutOfRangeException)
		{
			BOOST_CHECK_THROW(Location(Location::a, 0), out_of_range);
			BOOST_CHECK_THROW(Location(Location::b, 9), out_of_range);
		}

	BOOST_AUTO_TEST_SUITE_END() 

	BOOST_AUTO_TEST_SUITE(operator_std_string)

		BOOST_AUTO_TEST_CASE(Success)
		{
			BOOST_CHECK_EQUAL(static_cast<string>(Location(Location::a4)), "A4");
			BOOST_CHECK_EQUAL(static_cast<string>(Location(Location::b8)), "B8");
			BOOST_CHECK_EQUAL(static_cast<string>(Location(Location::e1)), "E1");
			BOOST_CHECK_EQUAL(static_cast<string>(Location(Location::f6)), "F6");
			BOOST_CHECK_EQUAL(static_cast<string>(Location(Location::g2)), "G2");
			BOOST_CHECK_EQUAL(static_cast<string>(Location(Location::h7)), "H7");
		}

	BOOST_AUTO_TEST_SUITE_END() 

	BOOST_AUTO_TEST_SUITE(for_each)

		struct for_each_Fixture
		{
			map<Location, int> calls;
			for_each_Fixture()
			{
				Location::for_each([&](Location current)
				{
					int numCalls = 1;
					try {
						numCalls += calls.at(current);
					} catch( const out_of_range& ) {}
					calls[current] = numCalls;
				});
			}
		};

		BOOST_FIXTURE_TEST_CASE(Calls64UniqueLocations, for_each_Fixture)
		{
			BOOST_CHECK_EQUAL(calls.size(), 64);
		}

		BOOST_FIXTURE_TEST_CASE(CallsEachLocationOnce, for_each_Fixture)
		{
			Location::for_each([&](Location current)
			{
				BOOST_CHECK_EQUAL(calls[current], 1);
			});
		}

	BOOST_AUTO_TEST_SUITE_END() 

	BOOST_AUTO_TEST_SUITE(operator_less_than)

		BOOST_AUTO_TEST_CASE(LessThan_ReturnsTrue)
		{
			BOOST_CHECK(Location(Location::a1) < Location(Location::b1));
			BOOST_CHECK(Location(Location::a3) < Location(Location::a2));
			BOOST_CHECK(Location(Location::a6) < Location(Location::d5));
			BOOST_CHECK(Location(Location::c8) < Location(Location::h8));
		}

		BOOST_AUTO_TEST_CASE(GreaterThan_ReturnsFalse)
		{
			BOOST_CHECK(!(Location(Location::b1) < Location(Location::a1)));
			BOOST_CHECK(!(Location(Location::a2) < Location(Location::a3)));
			BOOST_CHECK(!(Location(Location::d5) < Location(Location::a6)));
			BOOST_CHECK(!(Location(Location::h8) < Location(Location::c8)));
		}

		BOOST_AUTO_TEST_CASE(Equals_ReturnsFalse)
		{
			BOOST_CHECK(!(Location(Location::a1) < Location(Location::a1)));
			BOOST_CHECK(!(Location(Location::a2) < Location(Location::a2)));
			BOOST_CHECK(!(Location(Location::d5) < Location(Location::d5)));
			BOOST_CHECK(!(Location(Location::h8) < Location(Location::h8)));
		}

	BOOST_AUTO_TEST_SUITE_END() 

	BOOST_AUTO_TEST_SUITE(operator_equals)

		BOOST_AUTO_TEST_SUITE(Location__)

			BOOST_AUTO_TEST_CASE(Self_ReturnsTrue)
			{
				Location toCheck { Location::a1 };
				BOOST_CHECK(toCheck == toCheck);
			}

			BOOST_AUTO_TEST_CASE(CopyConstructor_ReturnsTrue)
			{
				Location toCheck { Location::a1 };
				BOOST_CHECK(toCheck == Location(toCheck));
			}

			BOOST_AUTO_TEST_CASE(EqualLocation_ReturnsTrue)
			{
				Location toCheck { Location::a1 };
				Location toCheck2 { Location::a1 };
				BOOST_CHECK(toCheck == toCheck2);
			}

			BOOST_AUTO_TEST_CASE(DifferentLocation_ReturnsFalse)
			{
				Location toCheck { Location::a1 };
				Location toCheck2 { Location::a2 };
				BOOST_CHECK(!(toCheck == toCheck2));
			}

		BOOST_AUTO_TEST_SUITE_END() 

		BOOST_AUTO_TEST_SUITE(AlgebraicLocation)

			BOOST_AUTO_TEST_CASE(Self_ReturnsTrue)
			{
				Location toCheck { Location::a1 };
				BOOST_CHECK(toCheck == static_cast<Location::AlgebraicLocation>(static_cast<int>(toCheck)));
			}

			BOOST_AUTO_TEST_CASE(EqualLocation_Reflexive_ReturnsTrue)
			{
				Location toCheck { Location::a1 };
				BOOST_CHECK(toCheck == Location::a1);
				BOOST_CHECK(Location::a1 == toCheck);
			}

			BOOST_AUTO_TEST_CASE(DifferentLocation_Reflexive_ReturnsFalse)
			{
				Location toCheck { Location::a1 };
				BOOST_CHECK(!(toCheck == Location::a2));
				BOOST_CHECK(!(Location::a2 == toCheck));
			}

		BOOST_AUTO_TEST_SUITE_END() 

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(operator_not_equals)

		BOOST_AUTO_TEST_SUITE(Location__)

			BOOST_AUTO_TEST_CASE(Self_ReturnsFalse)
			{
				Location toCheck { Location::a1 };
				BOOST_CHECK(!(toCheck != toCheck));
			}

			BOOST_AUTO_TEST_CASE(CopyConstructor_ReturnsFalse)
			{
				Location toCheck { Location::a1 };
				BOOST_CHECK(!(toCheck != Location(toCheck)));
			}

			BOOST_AUTO_TEST_CASE(EqualLocation_ReturnsFalse)
			{
				Location toCheck { Location::a1 };
				Location toCheck2 { Location::a1 };
				BOOST_CHECK(!(toCheck != toCheck2));
			}

			BOOST_AUTO_TEST_CASE(DifferentLocation_ReturnsTrue)
			{
				Location toCheck { Location::a1 };
				Location toCheck2 { Location::a2 };
				BOOST_CHECK(toCheck != toCheck2);
			}

		BOOST_AUTO_TEST_SUITE_END() 

		BOOST_AUTO_TEST_SUITE(AlgebraicLocation)

			BOOST_AUTO_TEST_CASE(Self_ReturnsFalse)
			{
				Location toCheck { Location::a1 };
				BOOST_CHECK(!(toCheck != static_cast<Location::AlgebraicLocation>(static_cast<int>(toCheck))));
			}

			BOOST_AUTO_TEST_CASE(EqualLocation_Reflexive_ReturnsFalse)
			{
				Location toCheck { Location::a1 };
				BOOST_CHECK(!(toCheck != Location::a1));
				BOOST_CHECK(!(Location::a1 != toCheck));
			}

			BOOST_AUTO_TEST_CASE(DifferentLocation_Reflexive_ReturnsTrue)
			{
				Location toCheck { Location::a1 };
				BOOST_CHECK(toCheck != Location::a2);
				BOOST_CHECK(Location::a2 != toCheck);
			}

		BOOST_AUTO_TEST_SUITE_END() 

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(operator_int)

		BOOST_AUTO_TEST_CASE(Success)
		{
			for(int current = static_cast<int>(Location::a1) ; current <= static_cast<int>(Location::h8) ; current++ )
			{
				Location location { static_cast<Location::AlgebraicLocation>(current) };
				BOOST_CHECK_EQUAL(static_cast<int>(location), current);
			}
		}

	BOOST_AUTO_TEST_SUITE_END() 

	BOOST_AUTO_TEST_SUITE(GetFile)

		BOOST_AUTO_TEST_CASE(Success)
		{
			Location location1 { Location::a1 };
			BOOST_CHECK_EQUAL(location1.GetFile(), Location::a);
			Location location2 { Location::b8 };
			BOOST_CHECK_EQUAL(location2.GetFile(), Location::b);
			Location location3 { Location::e3 };
			BOOST_CHECK_EQUAL(location3.GetFile(), Location::e);
			Location location4 { Location::g5 };
			BOOST_CHECK_EQUAL(location4.GetFile(), Location::g);
			Location location5 { Location::h4 };
			BOOST_CHECK_EQUAL(location5.GetFile(), Location::h);
		}

	BOOST_AUTO_TEST_SUITE_END() 

	BOOST_AUTO_TEST_SUITE(GetRank)

		BOOST_AUTO_TEST_CASE(Success)
		{
			Location location1 { Location::a1 };
			BOOST_CHECK_EQUAL(location1.GetRank(), 1);
			Location location2 { Location::b8 };
			BOOST_CHECK_EQUAL(location2.GetRank(), 8);
			Location location3 { Location::e3 };
			BOOST_CHECK_EQUAL(location3.GetRank(), 3);
			Location location4 { Location::g5 };
			BOOST_CHECK_EQUAL(location4.GetRank(), 5);
			Location location5 { Location::h4 };
			BOOST_CHECK_EQUAL(location5.GetRank(), 4);
		}

	BOOST_AUTO_TEST_SUITE_END() 


BOOST_AUTO_TEST_SUITE_END() 