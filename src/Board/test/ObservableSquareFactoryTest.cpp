#include <memory>
#include "gtest/gtest.h"
#include "Location.hpp"
#include "ObservableSquareFactory.hpp"
#include "IObservableSquare.hpp"

using namespace Chess;
using namespace std;

TEST(ObservableSquareFactory_makeSquare, ReturnsSquareWithGivenLocation)
{
	unique_ptr<IObservableSquareFactory> factory { new ObservableSquareFactory() };
	Location location { Location::e5 };
	EXPECT_EQ(factory->makeSquare(location)->GetLocation(), location);
}

TEST(ObservableSquareFactory_makeSquare, CreatingSharedPointerFromReturnValue_UseCountEquals1)
{
	unique_ptr<IObservableSquareFactory> factory { new ObservableSquareFactory() };
	Location location { Location::e5 };
	shared_ptr<IObservableSquare> square = factory->makeSquare(location);
	EXPECT_EQ(square.use_count(), 1);
}