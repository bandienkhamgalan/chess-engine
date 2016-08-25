#include "SimpleSquare.hpp"
#include "Location.hpp"
#include "mocks/Piece.hpp"
#include "Player.hpp"
#include <stdexcept>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(SimpleSquare_)

	using namespace std;
	using namespace Chess;

	BOOST_AUTO_TEST_SUITE(constructor)

		BOOST_AUTO_TEST_CASE(InitializesInstanceVariables)
		{
			SimpleSquare square { Location::a1  };
			BOOST_CHECK_EQUAL(square.GetLocation(), Location::a1 );
		}

	BOOST_AUTO_TEST_SUITE_END() 

	BOOST_AUTO_TEST_SUITE(GetPiece)

		BOOST_AUTO_TEST_CASE(NullPiece_ThrowsRuntimeErrorException)
		{
			SimpleSquare square { Location::a1 };
			BOOST_CHECK_THROW(square.GetPiece(), runtime_error);
		}

		BOOST_AUTO_TEST_CASE(NonNullPiece_DoesNotThrowAndReturnsPiece)
		{
			SimpleSquare square { Location::a1 };
			auto piece = make_shared<Mocks::Piece>();
			square.AssignPiece(piece);
			BOOST_CHECK_NO_THROW(square.GetPiece());
			BOOST_CHECK_EQUAL(&square.GetPiece(), piece.get());
		}

	BOOST_AUTO_TEST_SUITE_END() 

	BOOST_AUTO_TEST_SUITE(HasPiece)

		BOOST_AUTO_TEST_CASE(NullPiece_ReturnsFalse)
		{
			SimpleSquare square { Location::a1 };
			BOOST_CHECK_EQUAL(square.HasPiece(), false);
		}

		BOOST_AUTO_TEST_CASE(NonNullPiece_ReturnsTrue)
		{
			SimpleSquare square { Location::a1 };
			auto piece = make_shared<Mocks::Piece>();
			square.AssignPiece(piece);
			BOOST_CHECK_EQUAL(square.HasPiece(), true);
		}

	BOOST_AUTO_TEST_SUITE_END() 

BOOST_AUTO_TEST_SUITE_END() 