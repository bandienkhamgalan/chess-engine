#include "Location.hpp"
#include <stdexcept>
#include "gtest/gtest.h"

using namespace std;
using namespace Chess;

TEST(Location_Constructor, InRange_Success)
{
	EXPECT_EQ(Location(Location::a4), Location::a4);
	EXPECT_EQ(Location(Location::b3), Location::b3);
	EXPECT_EQ(Location(Location::e1), Location::e1);
	EXPECT_EQ(Location(Location::f6), Location::f6);
	EXPECT_EQ(Location(Location::g2), Location::g2);
	EXPECT_EQ(Location(Location::h7), Location::h7);
}

TEST(Location_Constructor, OutOfRange_Exception)
{
	EXPECT_THROW(new Location(Location::UNDEFINED), out_of_range);
	EXPECT_THROW(new Location(Location::MAX), out_of_range);
}

TEST(Location_fromString, CleanLowerCaseInput_Success)
{
	EXPECT_EQ(Location("a4"), Location::a4);
	EXPECT_EQ(Location("b8"), Location::b8);
	EXPECT_EQ(Location("e1"), Location::e1);
	EXPECT_EQ(Location("f6"), Location::f6);
	EXPECT_EQ(Location("g2"), Location::g2);
	EXPECT_EQ(Location("h7"), Location::h7);
}

TEST(Location_fromString, CleanUpperCaseInput_Success)
{
	EXPECT_EQ(Location("A4"), Location::a4);
	EXPECT_EQ(Location("B3"), Location::b3);
	EXPECT_EQ(Location("E1"), Location::e1);
	EXPECT_EQ(Location("F6"), Location::f6);
	EXPECT_EQ(Location("G2"), Location::g2);
	EXPECT_EQ(Location("H7"), Location::h7);
}

TEST(Location_fromString, NonTrimmedVariCaseInput_Success)
{
	EXPECT_EQ(Location("     a4 "), Location::a4);
	EXPECT_EQ(Location("   \nE1\t   "), Location::e1);
	EXPECT_EQ(Location("\n\t\th7\t\n   "), Location::h7);
}

TEST(Location_fromString, InvalidLength_Exception)
{
	EXPECT_THROW(Location("\ta43\r\n"), invalid_argument);
}

TEST(Location_fromString, InvalidContent_Exception)
{
	EXPECT_THROW(Location("\thello world\r\n"), invalid_argument);
	EXPECT_THROW(Location("\ta9\r\n"), out_of_range);
	EXPECT_THROW(Location("\tA0\r\n"), out_of_range);
	EXPECT_THROW(Location("\tj8\r\n"), out_of_range);
	EXPECT_THROW(Location("\tj1\r\n"), out_of_range);
}

TEST(Location_fromFileAndRank, ValidInput_Success)
{
	EXPECT_EQ(Location(Location::a, 4), Location::a4);
	EXPECT_EQ(Location(Location::b, 8), Location::b8);
	EXPECT_EQ(Location(Location::e, 1), Location::e1);
	EXPECT_EQ(Location(Location::f, 6), Location::f6);
	EXPECT_EQ(Location(Location::g, 2), Location::g2);
	EXPECT_EQ(Location(Location::h, 7), Location::h7);
	EXPECT_EQ(Location(1, 4), Location::a4);
	EXPECT_EQ(Location(2, 8), Location::b8);
	EXPECT_EQ(Location(5, 1), Location::e1);
	EXPECT_EQ(Location(6, 6), Location::f6);
	EXPECT_EQ(Location(7, 2), Location::g2);
	EXPECT_EQ(Location(8, 7), Location::h7);
}

TEST(Location_fromFileAndRank, InvalidFile_ThrowsOutOfRangeException)
{
	EXPECT_THROW(Location(static_cast<Location::File>(0), 4), out_of_range);
	EXPECT_THROW(Location(static_cast<Location::File>(9), 3), out_of_range);
}

TEST(Location_fromFileAndRank, InvalidRank_ThrowsOutOfRangeException)
{
	EXPECT_THROW(Location(Location::a, 0), out_of_range);
	EXPECT_THROW(Location(Location::b, 9), out_of_range);
}

TEST(Location_operator_std_string, Success)
{
	EXPECT_EQ(static_cast<string>(Location(Location::a4)), "A4");
	EXPECT_EQ(static_cast<string>(Location(Location::b8)), "B8");
	EXPECT_EQ(static_cast<string>(Location(Location::e1)), "E1");
	EXPECT_EQ(static_cast<string>(Location(Location::f6)), "F6");
	EXPECT_EQ(static_cast<string>(Location(Location::g2)), "G2");
	EXPECT_EQ(static_cast<string>(Location(Location::h7)), "H7");
}

class Location_for_each
	: public testing::Test
{
public:
	map<Location, int> calls;

	virtual void SetUp()
	{
		Location::for_each([&](const Location& current)
		{
			int numCalls = 1;
			try {
				numCalls += calls.at(current);
			} catch( const out_of_range& ) {}
			calls[current] = numCalls;
		});
	}

	virtual void TearDown()
	{
		calls.clear();
	}
};

TEST_F(Location_for_each, Calls64UniqueLocations)
{
	EXPECT_EQ(calls.size(), 64);
}

TEST_F(Location_for_each, CallsEachLocationOnce)
{
	Location::for_each([&](const Location& current)
	{
		EXPECT_EQ(calls[current], 1);
	});
}

TEST(Location_operator_less_than, LessThan_ReturnsTrue)
{
	EXPECT_TRUE(Location(Location::a1) < Location(Location::b1));
	EXPECT_TRUE(Location(Location::a3) < Location(Location::a2));
	EXPECT_TRUE(Location(Location::a6) < Location(Location::d5));
	EXPECT_TRUE(Location(Location::c8) < Location(Location::h8));
}

TEST(Location_operator_less_than, GreaterThan_ReturnsFalse)
{
	EXPECT_FALSE(Location(Location::b1) < Location(Location::a1));
	EXPECT_FALSE(Location(Location::a2) < Location(Location::a3));
	EXPECT_FALSE(Location(Location::d5) < Location(Location::a6));
	EXPECT_FALSE(Location(Location::h8) < Location(Location::c8));
}

TEST(Location_operator_less_than, Equals_ReturnsFalse)
{
	EXPECT_FALSE(Location(Location::a1) < Location(Location::a1));
	EXPECT_FALSE(Location(Location::a2) < Location(Location::a2));
	EXPECT_FALSE(Location(Location::d5) < Location(Location::d5));
	EXPECT_FALSE(Location(Location::h8) < Location(Location::h8));
}

TEST(Location_operator_equals_Location, Self_ReturnsTrue)
{
	Location toCheck { Location::a1 };
	EXPECT_TRUE(toCheck == toCheck);
}

TEST(Location_operator_equals_Location, CopyConstructor_ReturnsTrue)
{
	Location toCheck { Location::a1 };
	EXPECT_TRUE(toCheck == Location(toCheck));
}

TEST(Location_operator_equals_Location, EqualLocation_ReturnsTrue)
{
	Location toCheck { Location::a1 };
	Location toCheck2 { Location::a1 };
	EXPECT_TRUE(toCheck == toCheck2);
}

TEST(Location_operator_equals_Location, DifferentLocation_ReturnsFalse)
{
	Location toCheck { Location::a1 };
	Location toCheck2 { Location::a2 };
	EXPECT_FALSE(toCheck == toCheck2);
}

TEST(Location_operator_equals_AlgebraicLocation, Self_ReturnsTrue)
{
	Location toCheck { Location::a1 };
	EXPECT_TRUE(toCheck == static_cast<Location::AlgebraicLocation>(static_cast<int>(toCheck)));
}

TEST(Location_operator_equals_AlgebraicLocation, EqualLocation_Reflexive_ReturnsTrue)
{
	Location toCheck { Location::a1 };
	EXPECT_TRUE(toCheck == Location::a1);
	EXPECT_TRUE(Location::a1 == toCheck);
}

TEST(Location_operator_equals_AlgebraicLocation, DifferentLocation_Reflexive_ReturnsFalse)
{
	Location toCheck { Location::a1 };
	EXPECT_FALSE(toCheck == Location::a2);
	EXPECT_FALSE(Location::a2 == toCheck);
}

TEST(Location_operator_not_equals_Location, Self_ReturnsFalse)
{
	Location toCheck { Location::a1 };
	EXPECT_FALSE(toCheck != toCheck);
}

TEST(Location_operator_not_equals_Location, CopyConstructor_ReturnsFalse)
{
	Location toCheck { Location::a1 };
	EXPECT_FALSE(toCheck != Location(toCheck));
}

TEST(Location_operator_not_equals_Location, EqualLocation_ReturnsFalse)
{
	Location toCheck { Location::a1 };
	Location toCheck2 { Location::a1 };
	EXPECT_FALSE(toCheck != toCheck2);
}

TEST(Location_operator_not_equals_Location, DifferentLocation_ReturnsTrue)
{
	Location toCheck { Location::a1 };
	Location toCheck2 { Location::a2 };
	EXPECT_TRUE(toCheck != toCheck2);
}

TEST(Location_operator_not_equals_AlgebraicLocation, Self_ReturnsFalse)
{
	Location toCheck { Location::a1 };
	EXPECT_FALSE(toCheck != static_cast<Location::AlgebraicLocation>(static_cast<int>(toCheck)));
}

TEST(Location_operator_not_equals_AlgebraicLocation, EqualLocation_Reflexive_ReturnsFalse)
{
	Location toCheck { Location::a1 };
	EXPECT_FALSE(toCheck != Location::a1);
	EXPECT_FALSE(Location::a1 != toCheck);
}

TEST(Location_operator_not_equals_AlgebraicLocation, DifferentLocation_Reflexive_ReturnsTrue)
{
	Location toCheck { Location::a1 };
	EXPECT_TRUE(toCheck != Location::a2);
	EXPECT_TRUE(Location::a2 != toCheck);
}

TEST(Location_operator_int, Success)
{
	for(int current = static_cast<int>(Location::a1) ; current <= static_cast<int>(Location::h8) ; current++ )
	{
		Location location { static_cast<Location::AlgebraicLocation>(current) };
		EXPECT_EQ(static_cast<int>(location), current);
	}
}

TEST(Location_GetFile, Success)
{
	Location location1 { Location::a1 };
	EXPECT_EQ(location1.GetFile(), Location::a);
	Location location2 { Location::b8 };
	EXPECT_EQ(location2.GetFile(), Location::b);
	Location location3 { Location::e3 };
	EXPECT_EQ(location3.GetFile(), Location::e);
	Location location4 { Location::g5 };
	EXPECT_EQ(location4.GetFile(), Location::g);
	Location location5 { Location::h4 };
	EXPECT_EQ(location5.GetFile(), Location::h);
}

TEST(Location_GetRank, Success)
{
	Location location1 { Location::a1 };
	EXPECT_EQ(location1.GetRank(), 1);
	Location location2 { Location::b8 };
	EXPECT_EQ(location2.GetRank(), 8);
	Location location3 { Location::e3 };
	EXPECT_EQ(location3.GetRank(), 3);
	Location location4 { Location::g5 };
	EXPECT_EQ(location4.GetRank(), 5);
	Location location5 { Location::h4 };
	EXPECT_EQ(location5.GetRank(), 4);
}