#include "ISquareFactory.hpp"
#include "SimpleSquareFactory.hpp"
#include <memory>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(SimpleSquareFactory_)

	using namespace Chess;
	using namespace std;

	BOOST_AUTO_TEST_SUITE(makeSquare)

		BOOST_AUTO_TEST_CASE(ReturnsSquareWithGivenLocation)
		{
			unique_ptr<ISquareFactory> factory { new SimpleSquareFactory() };
			Location location { Location::e5 };
			BOOST_CHECK_EQUAL(factory->makeSquare(location)->GetLocation(), location);
		}

		BOOST_AUTO_TEST_CASE(CreatingSharedPointerFromReturnValue_UseCountEquals1)
		{
			unique_ptr<ISquareFactory> factory { new SimpleSquareFactory() };
			Location location { Location::e5 };
			shared_ptr<ISquare> square = move(factory->makeSquare(location));
			BOOST_CHECK_EQUAL(square.use_count(), 1);
		}

	BOOST_AUTO_TEST_SUITE_END() 

BOOST_AUTO_TEST_SUITE_END() 