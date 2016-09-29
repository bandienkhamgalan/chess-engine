#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Game.hpp"
#include "Player.hpp"
#include "IFENParser.hpp"
#include "mocks/Board.hpp"
#include "mocks/Piece.hpp"
#include "mocks/FENParser.hpp"
#include "mocks/PieceFactory.hpp"
#include "mocks/Player.hpp"
#include "Location.hpp"

using namespace std;
using namespace Chess;
using testing::NiceMock;
using testing::Eq;
using testing::ByMove;
using testing::Return;
using testing::ReturnRef;
using testing::AllOf;
using testing::_;

class Game_
	: public testing::Test
{
public:
	shared_ptr<NiceMock<Mocks::Board>> board;
	shared_ptr<NiceMock<Mocks::PieceFactory>> pieceFactory;
	shared_ptr<NiceMock<Mocks::Player>> white;
	shared_ptr<NiceMock<Mocks::Player>> black;
	shared_ptr<Game> game;

	virtual void InitializeBoardAndPlayers()
	{
		board = make_shared<NiceMock<Mocks::Board>>();
		pieceFactory = make_shared<NiceMock<Mocks::PieceFactory>>();
		white = make_shared<NiceMock<Mocks::Player>>();
		black = make_shared<NiceMock<Mocks::Player>>();
	}

	virtual void SetUp()
	{
		InitializeBoardAndPlayers();
	}

	virtual void InitializeGame()
	{
		game = make_shared<Game>(board, pieceFactory, white, black);
	}
};

class Game_WithParser_
	: public Game_
{
public:
	shared_ptr<NiceMock<IO::Mocks::FENParser>> parser;

	virtual void SetUp()
	{
		InitializeBoardAndPlayers();
		parser = make_shared<NiceMock<IO::Mocks::FENParser>>();
	}

	virtual void InitializeGame()
	{
		game = make_shared<Game>(board, pieceFactory, white, black, parser);
	}
};

TEST_F(Game_, Constructor_DefaultBoardSetup)
{
	/* Adds pieces to board */
	for(int file = 1 ; file <= 8 ; file++)
	{
		EXPECT_CALL(*board, AddPieceAtLocation(_, Eq(Location(file, 8))))
			.Times(1);
		EXPECT_CALL(*board, AddPieceAtLocation(_, Eq(Location(file, 7))))
			.Times(1);
		for(int rank = 6 ; rank >= 3 ; rank--)
			EXPECT_CALL(*board, AddPieceAtLocation(_, Eq(Location(file, rank))))
				.Times(0);
		EXPECT_CALL(*board, AddPieceAtLocation(_, Eq(Location(file, 2))))
			.Times(1);
		EXPECT_CALL(*board, AddPieceAtLocation(_, Eq(Location(file, 1))))
			.Times(1);
	}

	EXPECT_CALL(*black, AddPiece(_))
		.Times(16);
	EXPECT_CALL(*white, AddPiece(_))
		.Times(16);

	InitializeGame();

	/* Sets white to play */
	EXPECT_EQ(game->GetActiveColor(), Player::White);
}

TEST_F(Game_WithParser_, DoesNotInitializeBoard)
{
	EXPECT_CALL(*black, AddPiece(_))
		.Times(0);
	EXPECT_CALL(*white, AddPiece(_))
		.Times(0);
	EXPECT_CALL(*board, AddPieceAtLocation(_, _))
		.Times(0);

	InitializeGame();
} 

TEST_F(Game_WithParser_, Uninitialized_ThrowsRuntimeErrorException)
{
	InitializeGame();
	EXPECT_THROW(game->GetActiveColor(), runtime_error);
}

TEST_F(Game_WithParser_, IFENParserDelegate_UnsolicitedParser_ThrowsInvalidArgumentException)
{
	InitializeGame();
	shared_ptr<IO::IFENParser> parser2 = make_shared<IO::Mocks::FENParser>();
	EXPECT_THROW(game->FENParserError(*parser2, "test"), invalid_argument);
	EXPECT_THROW(game->FENParserPiece(*parser2, Location::a1, IPlayer::White, IPiece::Rook), invalid_argument);
	EXPECT_THROW(game->FENParserActiveColor(*parser2, IPlayer::White), invalid_argument);
	EXPECT_THROW(game->FENParserCompleted(*parser2), invalid_argument);		
}

TEST_F(Game_WithParser_, IFENParserDelegate_FENParserError_ThrowsRuntimeErrorException)
{
	InitializeGame();
	EXPECT_THROW(game->FENParserError(*parser, "test"), runtime_error);	
}

MATCHER_P(AddressEq, address, "")
{
	return &arg == address;
}

MATCHER_P(WeakPtrAddressEq, address, "")
{
	return arg.lock().get() == address;
}

MATCHER_P(SharedPtrAddressEq, address, "")
{
	return arg.get() == address;
}

TEST_F(Game_WithParser_, IFENParserDelegate_FENParserPiece_CreatesPieceAndAddsPieceToBoardAndPlayer)
{
	auto piece = new NiceMock<Mocks::Piece>();
	EXPECT_CALL(*pieceFactory, makePiece(WeakPtrAddressEq(board.get()), AddressEq(white.get()), Eq(IPiece::Queen)))
		.Times(1)
		.WillOnce(Return(ByMove(unique_ptr<IPiece>(piece))));
	EXPECT_CALL(*board, AddPieceAtLocation(SharedPtrAddressEq(piece), Eq(Location::e7)));

	InitializeGame();
	game->FENParserPiece(*parser, Location::e7, Player::White, IPiece::Queen);
}

TEST_F(Game_WithParser_, IFENParserDelegate_FENParserActiveColor_SetsActiveColor)
{
	InitializeGame();
	game->FENParserActiveColor(*parser, IPlayer::Black);
	EXPECT_EQ(game->GetActiveColor(), IPlayer::Black);				
}