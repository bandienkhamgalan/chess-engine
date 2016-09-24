#include <array>
#include <vector>
#include <tuple>
#include <stdexcept>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Player.hpp"
#include "Piece.hpp"
#include "Location.hpp"
#include "Helpers.hpp"
#include "SimpleSquare.hpp"
#include "mocks/PieceMoveLogic.hpp"

using namespace std;
using namespace Chess;
using ::testing::ReturnRef;

TEST(Piece_Constructor, ValidArguments_InitializesInstanceVariables)
{
	Player player { Player::White };
	Piece::Type pieceType { IPiece::Knight };
	unique_ptr<Piece> piece(new Piece(player, pieceType, make_shared<Mocks::PieceMoveLogic>()));
	EXPECT_EQ(piece->GetType(), pieceType);
	EXPECT_EQ(&piece->GetPlayer(), &player);
}

TEST(Piece_Constructor, InvalidType_ThrowsOutOfRangeException)
{
	Player player { Player::White };
	EXPECT_THROW(Piece piece(player, Piece::MAX, make_shared<Mocks::PieceMoveLogic>()), out_of_range);
	EXPECT_THROW(Piece piece(player, Piece::UNDEFINED, make_shared<Mocks::PieceMoveLogic>()), out_of_range);
}

TEST(Piece_GetLocation, InPlay_ReturnsCurrentLocation)
{
	Player player { Player::White };
	Piece piece { player, IPiece::Knight, make_shared<Mocks::PieceMoveLogic>() };
	shared_ptr<ISquare> square = make_shared<SimpleSquare>(Location::a2);
	piece.SetLocation(square);
	ASSERT_EQ(piece.IsInPlay(), true);
	EXPECT_EQ(piece.GetLocation(), square->GetLocation());
}

TEST(Piece_GetLocation, NotInPlay_ThrowsRuntimeErrorException)
{
	Player player { Player::White };
	Piece piece { player, IPiece::Knight, make_shared<Mocks::PieceMoveLogic>() };
	ASSERT_EQ(piece.IsInPlay(), false);
	EXPECT_THROW(piece.GetLocation(), runtime_error);
}

TEST(Piece_SetLocation, InPlayAndNonNullLocation_SetsNewLocation)
{
	Player player { Player::White };
	Piece piece { player, IPiece::Knight, make_shared<Mocks::PieceMoveLogic>() };
	shared_ptr<ISquare> square = make_shared<SimpleSquare>(Location::a2);
	piece.SetLocation(square);
	EXPECT_EQ(piece.GetLocation(), square->GetLocation());
}

TEST(Piece_SetLocation, InPlayAndNullLocation_ThrowsRuntimeErrorException)
{
	Player player { Player::White };
	Piece piece { player, Piece::Knight, make_shared<Mocks::PieceMoveLogic>() };
	shared_ptr<ISquare> square = make_shared<SimpleSquare>(Location::a2);
	piece.SetLocation(square);
	EXPECT_THROW(piece.SetLocation(shared_ptr<ISquare>(nullptr)), runtime_error);
}

TEST(Piece_SetLocation, NotInPlay_Noop)
{
	Player player { Player::White };
	Piece piece { player, IPiece::Knight, make_shared<Mocks::PieceMoveLogic>() };
	EXPECT_EQ(piece.IsInPlay(), false);
	piece.SetLocation(shared_ptr<ISquare>(nullptr));
	EXPECT_EQ(piece.IsInPlay(), false);
}

TEST(Piece_IsInPlay, NullLocation_ReturnsFalse)
{
	Player player { Player::White };
	Piece piece { player, IPiece::Knight, make_shared<Mocks::PieceMoveLogic>() };
	EXPECT_EQ(piece.IsInPlay(), false);
}

TEST(Piece_IsInPlay, NonNullLocation_ReturnsTrue)
{
	Player player { Player::White };
	Piece piece { player, IPiece::Knight, make_shared<Mocks::PieceMoveLogic>() };
	shared_ptr<ISquare> square = make_shared<SimpleSquare>(Location::a1);
	piece.SetLocation(square);
	EXPECT_EQ(piece.IsInPlay(), true);
}

TEST(Piece_RemoveFromPlay, Success)
{
	Player player { Player::White };
	Piece piece { player, IPiece::Knight, make_shared<Mocks::PieceMoveLogic>() };
	shared_ptr<ISquare> square = make_shared<SimpleSquare>(Location::a1);
	piece.SetLocation(square);
	EXPECT_EQ(piece.IsInPlay(), true);
	piece.RemoveFromPlay();
	EXPECT_EQ(piece.IsInPlay(), false);
}

TEST(Piece_GetValidMoves, DelegatesToPieceMoveLogic)
{
	Player player { Player::White };
	auto pieceMoveLogic { make_shared<Mocks::PieceMoveLogic>() };
	vector<Location> validMovesToReturn { Location::e8 };
	EXPECT_CALL(*pieceMoveLogic, GetValidMoves())
		.Times(1)
		.WillOnce(ReturnRef(validMovesToReturn));

	Piece piece { player, IPiece::Knight, pieceMoveLogic };
	const auto& validMoves = piece.GetValidMoves();
	ASSERT_EQ(validMoves.size(), 1);
	ASSERT_EQ(validMoves[0], Location::e8);
}

TEST(Piece_operator_string, NullLocation_ReturnsType)
{
	Player player { Player::White };
	Piece piece { player, IPiece::Knight, make_shared<Mocks::PieceMoveLogic>() };
	EXPECT_EQ(Helpers::sprint(piece), "Knight");
}

TEST(Piece_operator_string, NonNullLocation_ReturnsTypeAndLocation)
{
	Player player { Player::White };
	Piece piece { player, IPiece::Queen, make_shared<Mocks::PieceMoveLogic>() };
	shared_ptr<ISquare> square = make_shared<SimpleSquare>(Location::f4);
	piece.SetLocation(square);
	EXPECT_EQ(Helpers::sprint(piece), "Queen at F4");
}

TEST(PieceTypeToString_, ValidType_ReturnsCorrectString)
{
	array<IPiece::Type, 6> types {{ IPiece::Pawn, IPiece::Knight, IPiece::Bishop, IPiece::Rook, IPiece::Queen, IPiece::King }};
	array<string, 6> strings = {{ "Pawn", "Knight", "Bishop", "Rook", "Queen", "King" }};
	for( uint8_t current = 0 ; current < 6 ; current++ )
	{
		EXPECT_EQ(PieceTypeToString(types[current]), strings[current]);
	}
}

TEST(PieceTypeToString_, InvalidType_ThrowsInvalidArgumentException)
{
	EXPECT_THROW(PieceTypeToString(IPiece::UNDEFINED), invalid_argument);
	EXPECT_THROW(PieceTypeToString(IPiece::MAX), invalid_argument);
}