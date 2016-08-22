#include "Player.hpp"
#include "Piece.hpp"
#include "Location.hpp"
#include "mocks/MockSquareFactory.hpp"
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
			BOOST_CHECK_EQUAL( player.GetColor(), Player::White );
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(AddPiece)

		BOOST_AUTO_TEST_CASE(NonNullPiece_DoesNotThrowAndAddsPiece)
		{
			Player player { Player::White };
			BOOST_CHECK_EQUAL(player.GetPieces().size(), 0);
			BOOST_CHECK_NO_THROW(player.AddPiece(make_shared<Piece>(player, IPiece::Pawn)));
			BOOST_CHECK_EQUAL(player.GetPieces().size(), 1);
		}

		BOOST_AUTO_TEST_CASE(NullPiece_ThrowsInvalidArgumentException)
		{
			Player player { Player::White };
			BOOST_CHECK_THROW(player.AddPiece(shared_ptr<Piece>(nullptr)), invalid_argument);
		}

	BOOST_AUTO_TEST_SUITE_END() 

	BOOST_AUTO_TEST_SUITE(AddPieces)

		BOOST_AUTO_TEST_CASE(Success)
		{
			MockSquareFactory factory;
			Player player { Player::White };
			auto piece1 = make_shared<Piece>(player, IPiece::Pawn);
			piece1->SetLocation(move(factory.makeSquare(Location::a1)));
			auto piece2 = make_shared<Piece>(player, IPiece::Pawn);
			piece2->SetLocation(move(factory.makeSquare(Location::a2)));
			auto piece3 = make_shared<Piece>(player, IPiece::Pawn);
			piece3->SetLocation(move(factory.makeSquare(Location::a3)));
			BOOST_CHECK_EQUAL(player.GetPieces().size(), 0);
			BOOST_CHECK_NO_THROW(player.AddPieces( { piece1, piece2, piece3 } ));
			auto pieces = player.GetPieces();
			BOOST_CHECK_EQUAL(pieces.size(), 3);
			BOOST_CHECK_EQUAL(pieces[0].get(), piece1.get());
			BOOST_CHECK_EQUAL(pieces[1].get(), piece2.get());
			BOOST_CHECK_EQUAL(pieces[2].get(), piece3.get());
		}

	BOOST_AUTO_TEST_SUITE_END() 

BOOST_AUTO_TEST_SUITE_END() 