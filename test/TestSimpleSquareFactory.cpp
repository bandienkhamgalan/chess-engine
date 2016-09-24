#include <memory>
#include "gtest/gtest.h"
#include "Location.hpp"
#include "ISquare.hpp"
#include "ISquareFactory.hpp"
#include "SimpleSquareFactory.hpp"

using namespace Chess;
using namespace std;

TEST(SimpleSquareFactory_makeSquare, ReturnsSquareWithGivenLocation)
{
	unique_ptr<ISquareFactory> factory { new SimpleSquareFactory() };
	Location location { Location::e5 };
	EXPECT_EQ(factory->makeSquare(location)->GetLocation(), location);
}

TEST(SimpleSquareFactory_makeSquare, CreatingSharedPointerFromReturnValue_UseCountEquals1)
{
	unique_ptr<ISquareFactory> factory { new SimpleSquareFactory() };
	Location location { Location::e5 };
	shared_ptr<ISquare> square = factory->makeSquare(location);
	EXPECT_EQ(square.use_count(), 1);
}