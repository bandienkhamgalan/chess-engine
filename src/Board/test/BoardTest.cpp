#include <map>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Helpers.hpp"
#include "Board.hpp"
#include "Location.hpp"
#include "Player.hpp"
#include "mocks/Piece.hpp"
#include "mocks/ObservableSquare.hpp"
#include "mocks/ObservableSquareFactory.hpp"

using namespace std;
using namespace Chess;
using testing::NiceMock;
using testing::Return;
using testing::ReturnRef;
using testing::Invoke;
using testing::ByMove;
using testing::Eq;
using testing::_;

TEST(Board_Constructor, InitializesSquares)
{
	NiceMock<Mocks::ObservableSquareFactory> squareFactory;
	Location::for_each( [&](Location current)
	{
		EXPECT_CALL(squareFactory, makeSquare(current))
			.Times(1)
			.WillOnce(Return(ByMove(unique_ptr<IObservableSquare>(nullptr))));
	});
	Board board(squareFactory);
};

class Board_
	: public testing::Test
{
public:
	NiceMock<Mocks::ObservableSquareFactory> squareFactory;
	std::map<Location, NiceMock<Mocks::ObservableSquare>*> squares;
	Board board;

	Board_()
		: board(prepareFactory())
	{

	}
	/*
	virtual void SetUp()
	{

	}

	virtual void TearDown()
	{
		
	}
	*/
	NiceMock<Mocks::ObservableSquareFactory>& prepareFactory()
	{
		ON_CALL(squareFactory, makeSquare(_))
			.WillByDefault(Invoke([&](const Location& location) {
				auto square = new NiceMock<Mocks::ObservableSquare>();
				ON_CALL(*square, GetLocation())
					.WillByDefault(ReturnRef(location));
				squares[location] = square;
				return unique_ptr<IObservableSquare>(square);
			}));
		return squareFactory;
	}
};

TEST_F(Board_, HasPieceAtLocation_DelegatesToISquare)
{
	Location location(Location::f4);
	EXPECT_CALL(*squares[location], HasPiece())
		.WillOnce(Return(true))
		.WillOnce(Return(false));
	EXPECT_EQ(true, board.HasPieceAtLocation(location));
	EXPECT_EQ(false, board.HasPieceAtLocation(location));
}

TEST_F(Board_, GetPieceAtLocation_DelegatesToISquare)
{
	Location location(Location::f4);
	Mocks::Piece piece;
	EXPECT_CALL(*squares[location], GetPiece())
		.WillOnce(ReturnRef(piece));
	EXPECT_EQ(&board.GetPieceAtLocation(location), &piece);
}

MATCHER_P(SharedPointerAddressEq, object, "")
{
	return arg.get() == object;
}

TEST_F(Board_, AddPieceAtLocation_SquareEmpty_PieceNotInPlay_Success)
{
	Location location(Location::f4);
	auto piece = make_shared<NiceMock<Mocks::Piece>>();
	ON_CALL(*squares[location], HasPiece())
		.WillByDefault(Return(false));
	ON_CALL(*piece, IsInPlay())
		.WillByDefault(Return(false));
	EXPECT_CALL(*piece, SetLocation(SharedPointerAddressEq(squares[location])))
		.Times(1);
	EXPECT_CALL(*squares[location], AssignPiece(SharedPointerAddressEq(piece.get())))
		.Times(1);

	board.AddPieceAtLocation(piece, location);
}

TEST_F(Board_, AddPieceAtLocation_SquareEmpty_PieceInPlay_ThrowsInvalidArgumentException)
{
	Location location(Location::f4);
	auto piece = make_shared<NiceMock<Mocks::Piece>>();
	ON_CALL(*squares[location], HasPiece())
		.WillByDefault(Return(false));
	ON_CALL(*piece, IsInPlay())
		.WillByDefault(Return(true));

	EXPECT_THROW(board.AddPieceAtLocation(piece, location), invalid_argument);
}

TEST_F(Board_, AddPieceAtLocation_SquareOccupied_ThrowsInvalidArgumentException)
{
	Location location(Location::f4);
	auto piece = make_shared<NiceMock<Mocks::Piece>>();
	ON_CALL(*squares[location], HasPiece())
		.WillByDefault(Return(true));

	EXPECT_THROW(board.AddPieceAtLocation(piece, location), invalid_argument);
}

TEST_F(Board_, AddPieceAtLocation_NullPiece_ThrowsInvalidArgumentException)
{
	shared_ptr<IPiece> piece = nullptr;

	EXPECT_THROW(board.AddPieceAtLocation(piece, Location::f4), invalid_argument);
}

TEST_F(Board_, MovePieceToLocation_NullPiece_ThrowsInvalidArgumentException)
{
	shared_ptr<IPiece> piece = nullptr;

	EXPECT_THROW(board.MovePieceToLocation(piece, Location::f4), invalid_argument);
}

TEST_F(Board_, MovePieceToLocation_PieceNotInPlay_ThrowsRuntimeError)
{
	auto piece = make_shared<NiceMock<Mocks::Piece>>();
	ON_CALL(*piece, IsInPlay())
		.WillByDefault(Return(false));

	EXPECT_THROW(board.MovePieceToLocation(piece, Location::f4), runtime_error);
}

TEST_F(Board_, MovePieceToLocation_UnregisteredPiece_ThrowsInvalidArgumentException)
{
	Location source(Location::f4);
	Location destination(Location::g5);
	auto piece = make_shared<NiceMock<Mocks::Piece>>();
	ON_CALL(*piece, IsInPlay())
		.WillByDefault(Return(true));
	ON_CALL(*piece, GetLocation())
		.WillByDefault(ReturnRef(source));

	EXPECT_THROW(board.MovePieceToLocation(piece, destination), invalid_argument);
}

class Board_MovePieceToLocation_PieceRegistered
	: public Board_
{
public:
	Location source;
	Location destination;
	shared_ptr<NiceMock<Mocks::Piece>> piece;

	Board_MovePieceToLocation_PieceRegistered()
		: source(Location::f4), destination(Location::g5), piece(make_shared<NiceMock<Mocks::Piece>>())
	{
		ON_CALL(*piece, IsInPlay())
			.WillByDefault(Return(true));
		ON_CALL(*piece, GetLocation())
			.WillByDefault(ReturnRef(source));
		ON_CALL(*squares[source], HasPiece())
			.WillByDefault(Return(true));
		ON_CALL(*squares[source], GetPiece())
			.WillByDefault(ReturnRef(*piece));
	}

	/*
	virtual void SetUp()
	{

	}

	virtual void TearDown()
	{
		
	}
	*/
};

TEST_F(Board_MovePieceToLocation_PieceRegistered, DestinationOccupied_ThrowsInvalidArgumentException)
{
	ON_CALL(*squares[destination], HasPiece())
		.WillByDefault(Return(true));

	EXPECT_THROW(board.MovePieceToLocation(piece, destination), invalid_argument);
}

TEST_F(Board_MovePieceToLocation_PieceRegistered, DestinationEmpty_Success)
{
	ON_CALL(*squares[destination], HasPiece())
		.WillByDefault(Return(false));

	EXPECT_CALL(*squares[source], RemovePiece())
		.Times(1);
	EXPECT_CALL(*squares[destination], AssignPiece(SharedPointerAddressEq(piece.get())))
		.Times(1);
	EXPECT_CALL(*piece, SetLocation(SharedPointerAddressEq(squares[destination])))
		.Times(1);

	board.MovePieceToLocation(piece, destination);
}