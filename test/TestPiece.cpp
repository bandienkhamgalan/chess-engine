#include "Player.hpp"
#include "Piece.hpp"
#include "Location.hpp"
#include "Helpers.hpp"
#include "mocks/SquareFactory.hpp"
#include <array>
#include <tuple>
#include <stdexcept>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(Piece_)

	using namespace std;
	using namespace Chess;

	BOOST_AUTO_TEST_SUITE(constructor)

		BOOST_AUTO_TEST_CASE(ValidArguments_InitializesInstanceVariables)
		{
			Player player { Player::White };
			Piece::Type pieceType { IPiece::Knight };
			unique_ptr<Piece> piece;
			BOOST_CHECK_NO_THROW(piece.reset(new Piece(player, pieceType)));
			BOOST_CHECK_EQUAL(piece->GetType(), pieceType);
			BOOST_CHECK_EQUAL(&piece->GetPlayer(), &player);
		}

		BOOST_AUTO_TEST_CASE(InvalidType_ThrowsOutOfRangeException)
		{
			Player player { Player::White };
			BOOST_CHECK_THROW(Piece piece(player, Piece::MAX), out_of_range);
			BOOST_CHECK_THROW(Piece piece(player, Piece::UNDEFINED), out_of_range);
		}

	BOOST_AUTO_TEST_SUITE_END() 

	BOOST_AUTO_TEST_SUITE(GetLocation)

		BOOST_AUTO_TEST_CASE(InPlay_ReturnsCurrentLocation)
		{
			Player player { Player::White };
			Piece piece { player, IPiece::Knight };
			Mocks::SquareFactory factory;
			shared_ptr<ISquare> square = move(factory.makeSquare(Location::a1));
			piece.SetLocation(square);
			BOOST_REQUIRE_EQUAL(piece.IsInPlay(), true);
			BOOST_CHECK_EQUAL(piece.GetLocation(), square->GetLocation());
		}

		BOOST_AUTO_TEST_CASE(NotInPlay_ThrowsRuntimeErrorException)
		{
			Player player { Player::White };
			Piece piece { player, IPiece::Knight };
			BOOST_REQUIRE_EQUAL(piece.IsInPlay(), false);
			BOOST_CHECK_THROW(piece.GetLocation(), runtime_error);
		}

	BOOST_AUTO_TEST_SUITE_END() 

	BOOST_AUTO_TEST_SUITE(SetLocation)

		BOOST_AUTO_TEST_CASE(InPlayAndNonNullLocation_SetsNewLocation)
		{
			Player player { Player::White };
			Piece piece { player, IPiece::Knight };
			Mocks::SquareFactory factory;
			shared_ptr<ISquare> square = move(factory.makeSquare(Location::a2));
			BOOST_CHECK_NO_THROW(piece.SetLocation(square));
			BOOST_CHECK_EQUAL(piece.GetLocation(), square->GetLocation());
		}

		BOOST_AUTO_TEST_CASE(InPlayAndNullLocation_ThrowsRuntimeErrorException)
		{
			Player player { Player::White };
			Piece piece { player, Piece::Knight };
			Mocks::SquareFactory factory;
			shared_ptr<ISquare> square = move(factory.makeSquare(Location::a2));
			BOOST_CHECK_NO_THROW(piece.SetLocation(square));
			BOOST_CHECK_THROW(piece.SetLocation(shared_ptr<ISquare>(nullptr)), runtime_error);
		}

		BOOST_AUTO_TEST_CASE(NotInPlay_Noop)
		{
			Player player { Player::White };
			Piece piece { player, IPiece::Knight };
			BOOST_CHECK_EQUAL(piece.IsInPlay(), false);
			BOOST_CHECK_NO_THROW(piece.SetLocation(shared_ptr<ISquare>(nullptr)));
			BOOST_CHECK_EQUAL(piece.IsInPlay(), false);
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(IsInPlay)

		BOOST_AUTO_TEST_CASE(NullLocation_ReturnsFalse)
		{
			Player player { Player::White };
			Piece piece { player, IPiece::Knight };
			BOOST_CHECK_EQUAL(piece.IsInPlay(), false);
		}

		BOOST_AUTO_TEST_CASE(NonNullLocation_ReturnsTrue)
		{
			Player player { Player::White };
			Piece piece { player, IPiece::Knight };
			Mocks::SquareFactory factory;
			shared_ptr<ISquare> square = move(factory.makeSquare(Location::a1));
			BOOST_CHECK_NO_THROW(piece.SetLocation(square));
			BOOST_CHECK_EQUAL(piece.IsInPlay(), true);
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(RemoveFromPlay)

		BOOST_AUTO_TEST_CASE(Success)
		{
			Player player { Player::White };
			Piece piece { player, IPiece::Knight };
			Mocks::SquareFactory factory;
			shared_ptr<ISquare> square = move(factory.makeSquare(Location::a1));
			BOOST_CHECK_NO_THROW(piece.SetLocation(square));
			BOOST_CHECK_EQUAL(piece.IsInPlay(), true);
			piece.RemoveFromPlay();
			BOOST_CHECK_EQUAL(piece.IsInPlay(), false);
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(operator_string)

		BOOST_AUTO_TEST_CASE(NullLocation_ReturnsType)
		{
			Player player { Player::White };
			Piece piece { player, IPiece::Knight };
			BOOST_CHECK_EQUAL(Helpers::sprint(piece), "Knight");
		}

		BOOST_AUTO_TEST_CASE(NonNullLocation_ReturnsTypeAndLocation)
		{
			Player player { Player::White };
			Piece piece { player, IPiece::Queen };
			Mocks::SquareFactory factory;
			shared_ptr<ISquare> square = move(factory.makeSquare(Location::f4));
			BOOST_CHECK_NO_THROW(piece.SetLocation(square));
			BOOST_CHECK_EQUAL(Helpers::sprint(piece), "Queen at F4");
		}

	BOOST_AUTO_TEST_SUITE_END() 

	BOOST_AUTO_TEST_SUITE(PieceTypeToString_)

		BOOST_AUTO_TEST_CASE(ValidType_ReturnsCorrectString)
		{
			array<IPiece::Type, 6> types {{ IPiece::Pawn, IPiece::Knight, IPiece::Bishop, IPiece::Rook, IPiece::Queen, IPiece::King }};
			array<string, 6> strings = {{ "Pawn", "Knight", "Bishop", "Rook", "Queen", "King" }};
			for( uint8_t current = 0 ; current < 6 ; current++ )
			{
				BOOST_CHECK_EQUAL(PieceTypeToString(types[current]), strings[current]);
			}
		}

		BOOST_AUTO_TEST_CASE(InvalidType_ThrowsInvalidArgumentException)
		{
			BOOST_CHECK_THROW(PieceTypeToString(IPiece::UNDEFINED), invalid_argument);
			BOOST_CHECK_THROW(PieceTypeToString(IPiece::MAX), invalid_argument);
		}

	BOOST_AUTO_TEST_SUITE_END() 

BOOST_AUTO_TEST_SUITE_END() 