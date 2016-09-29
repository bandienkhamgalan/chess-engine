#include <stdexcept>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "KnightMoveLogic.hpp"
#include "mocks/Board.hpp"
#include "mocks/Piece.hpp"

using namespace std;
using namespace Chess;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::ReturnRef;
using ::testing::Eq;

TEST(KnightMoveLogic_Constructor, NullPiece_ThrowsInvalidArgumentException)
{
	EXPECT_THROW(KnightMoveLogic(make_shared<NiceMock<Mocks::Board>>(), shared_ptr<IPiece>(nullptr)), invalid_argument);
}

TEST(KnightMoveLogic_SetPiece, NullPiece_ThrowsInvalidArgumentException)
{
	auto board { make_shared<NiceMock<Mocks::Board>>() };
	KnightMoveLogic knightMoveLogic { board };
	EXPECT_THROW(knightMoveLogic.SetPiece(shared_ptr<IPiece>(nullptr)), invalid_argument);
}

TEST(KnightMoveLogic_SetPiece, ExistingPiece_ThrowsRuntimeErrorException)
{
	auto board { make_shared<NiceMock<Mocks::Board>>() };
	auto piece { make_shared<NiceMock<Mocks::Piece>>() };
	KnightMoveLogic knightMoveLogic { board, piece };
	EXPECT_THROW(knightMoveLogic.SetPiece(make_shared<Mocks::Piece>()), runtime_error);
}

TEST(KnightMoveLogic_GetValidMoves, NoPiece_ThrowsRuntimeErrorException)
{
	auto board { make_shared<NiceMock<Mocks::Board>>() };
	KnightMoveLogic knightMoveLogic { board };
	EXPECT_THROW(knightMoveLogic.GetValidMoves(), runtime_error);
}

TEST(KnightMoveLogic_GetValidMoves, BoardExpired_ThrowsRuntimeErrorException)
{
	auto piece { make_shared<NiceMock<Mocks::Piece>>() };
	KnightMoveLogic knightMoveLogic { make_shared<Mocks::Board>(), piece };
	EXPECT_THROW(knightMoveLogic.GetValidMoves(), runtime_error);
}

TEST(KnightMoveLogic_GetValidMoves, PieceNotInPlay_ReturnsEmptyVector)
{
	auto piece { make_shared<NiceMock<Mocks::Piece>>() };
	auto board { make_shared<NiceMock<Mocks::Board>>() };
	KnightMoveLogic knightMoveLogic { board, piece };
	ON_CALL(*piece, IsInPlay())
		.WillByDefault(Return(false));
	EXPECT_EQ(knightMoveLogic.GetValidMoves().size(), 0);
}

class KnightMoveLogic_GetValidMoves_PieceInPlay
	: public testing::Test
{
public:
	shared_ptr<NiceMock<Mocks::Board>> board;
	shared_ptr<NiceMock<Mocks::Piece>> piece;
	KnightMoveLogic knightMoveLogic;

	KnightMoveLogic_GetValidMoves_PieceInPlay()
		: board(make_shared<NiceMock<Mocks::Board>>()), piece(make_shared<NiceMock<Mocks::Piece>>()), knightMoveLogic(board, piece)
	{
		ON_CALL(*piece, IsInPlay())
			.WillByDefault(Return(true));
	}
};

TEST_F(KnightMoveLogic_GetValidMoves_PieceInPlay, StartingPosition_TwoMoves)
{
	Location location(Location::b1);
	ON_CALL(*piece, GetLocation())
		.WillByDefault(ReturnRef(location));
	const auto& validMoves = knightMoveLogic.GetValidMoves();
	EXPECT_EQ(validMoves.size(), 2);
	EXPECT_EQ(count(validMoves.begin(), validMoves.end(), Location::a3), 1);
	EXPECT_EQ(count(validMoves.begin(), validMoves.end(), Location::c3), 1);
}

TEST_F(KnightMoveLogic_GetValidMoves_PieceInPlay, StartingPosition_OccupiedOneMove)
{
	Location location(Location::b1);
	ON_CALL(*piece, GetLocation())
		.WillByDefault(ReturnRef(location));
	ON_CALL(*board, HasPieceAtLocation(Eq(Location::a3)))
		.WillByDefault(Return(true));
	const auto& validMoves = knightMoveLogic.GetValidMoves();
	EXPECT_EQ(validMoves.size(), 1);
	EXPECT_EQ(count(validMoves.begin(), validMoves.end(), Location::c3), 1);
}

TEST_F(KnightMoveLogic_GetValidMoves_PieceInPlay, CenterPosition_BoardFree_FourMoves)
{
	Location location(Location::e4);
	ON_CALL(*piece, GetLocation())
		.WillByDefault(ReturnRef(location));
	const auto& validMoves = knightMoveLogic.GetValidMoves();
	EXPECT_EQ(validMoves.size(), 4);
	EXPECT_EQ(count(validMoves.begin(), validMoves.end(), Location::d6), 1);
	EXPECT_EQ(count(validMoves.begin(), validMoves.end(), Location::f6), 1);
	EXPECT_EQ(count(validMoves.begin(), validMoves.end(), Location::d2), 1);
	EXPECT_EQ(count(validMoves.begin(), validMoves.end(), Location::f2), 1);
}