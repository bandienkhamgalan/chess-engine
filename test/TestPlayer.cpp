#include "Player.hpp"
#include "Location.hpp"
#include "mocks/SquareFactory.hpp"
#include "mocks/Piece.hpp"
#include <stdexcept>
#include <boost/test/unit_test.hpp>

using namespace std;
using namespace Chess;

BOOST_AUTO_TEST_SUITE(Player_)

	BOOST_AUTO_TEST_SUITE(constructor_color)

		BOOST_AUTO_TEST_CASE(InvalidColor_ThrowsOutOfRangeException)
		{
			BOOST_CHECK_THROW(Player player(Player::UNDEFINED), out_of_range);
			BOOST_CHECK_THROW(Player player(Player::MAX), out_of_range);
		}

		BOOST_AUTO_TEST_CASE(ValidColor_InitializesInstanceVariables)
		{
			BOOST_CHECK_NO_THROW(Player player(Player::White));
			Player player { Player::White };
			BOOST_CHECK_EQUAL(player.GetColor(), Player::White);
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(AddPiece)

		BOOST_AUTO_TEST_CASE(NonNullPiece_DoesNotThrowAndAddsPiece)
		{
			Player player { Player::White };
			BOOST_CHECK_EQUAL(player.GetPieces().size(), 0);
			BOOST_CHECK_NO_THROW(player.AddPiece(make_shared<Mocks::Piece>()));
			BOOST_CHECK_EQUAL(player.GetPieces().size(), 1);
		}

		BOOST_AUTO_TEST_CASE(NullPiece_ThrowsInvalidArgumentException)
		{
			Player player { Player::White };
			BOOST_CHECK_THROW(player.AddPiece(shared_ptr<IPiece>(nullptr)), invalid_argument);
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END() 