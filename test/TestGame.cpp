#include "Game.hpp"
#include "mocks/Board.hpp"
#include "Player.hpp"
#include "IFENParser.hpp"
#include "mocks/FENParser.hpp"
#include "Location.hpp"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(Game_)

	using namespace std;
	using namespace Chess;

	struct GameWithParserTestFixture
	{
		shared_ptr<Mocks::Board> board;
		shared_ptr<IPlayer> white;
		shared_ptr<IPlayer> black;
		shared_ptr<IO::IFENParser> parser;
		shared_ptr<Game> game;

		GameWithParserTestFixture()
			:	board(make_shared<Mocks::Board>()),
				white(make_shared<Player>(IPlayer::White)),
				black(make_shared<Player>(IPlayer::Black)),
				parser(make_shared<IO::Mocks::FENParser>()),
				game(make_shared<Game>(board, white, black, parser)) { }
	};

	struct GameTestFixture
	{
		shared_ptr<Mocks::Board> board;
		shared_ptr<IPlayer> white;
		shared_ptr<IPlayer> black;
		shared_ptr<Game> game;

		GameTestFixture()
			:	board(make_shared<Mocks::Board>()),
				white(make_shared<Player>(IPlayer::White)),
				black(make_shared<Player>(IPlayer::Black)),
				game(make_shared<Game>(board, white, black)) { }
	};

	BOOST_AUTO_TEST_SUITE(Constructor_Default)
	
		BOOST_FIXTURE_TEST_CASE(InitializesBoardPlayerPiecesAndActiveColor, GameTestFixture)
		{
			/* Active color */
			BOOST_CHECK_EQUAL(game->GetActiveColor(), Player::White);

			/* Piece count */
			BOOST_CHECK_EQUAL(game->GetWhitePlayer().GetPieces().size(), 16);
			BOOST_CHECK_EQUAL(game->GetBlackPlayer().GetPieces().size(), 16);
			BOOST_CHECK_EQUAL(board->AddPieceAtLocationParams->size(), 32);

			/* Black pieces */
			IPiece::Type types[] = { IPiece::Rook, IPiece::Knight, IPiece::Bishop, IPiece::Queen, IPiece::King, IPiece::Bishop, IPiece::Knight, IPiece::Rook };
			for(int file = 1 ; file <= 8 ; file++)
				BOOST_CHECK_EQUAL(board->AddPieceAtLocationCalls(Player::Black, types[file - 1], Location(file, 8)), 1);
			for(int file = 1 ; file <= 8 ; file++)
				BOOST_CHECK_EQUAL(board->AddPieceAtLocationCalls(Player::Black, IPiece::Pawn, Location(file, 7)), 1);

			/* White pieces */
			for(int file = 1 ; file <= 8 ; file++)
				BOOST_CHECK_EQUAL(board->AddPieceAtLocationCalls(Player::White, types[file - 1], Location(file, 1)), 1);
			for(int file = 1 ; file <= 8 ; file++)
				BOOST_CHECK_EQUAL(board->AddPieceAtLocationCalls(Player::White, IPiece::Pawn, Location(file, 2)), 1);
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(Constructor_Parser)
	
		BOOST_FIXTURE_TEST_CASE(DoesNotInitializeBoard, GameWithParserTestFixture)
		{
			/* Piece numbers */
			BOOST_CHECK_EQUAL(game->GetWhitePlayer().GetPieces().size(), 0);
			BOOST_CHECK_EQUAL(game->GetBlackPlayer().GetPieces().size(), 0);
			BOOST_CHECK_EQUAL(board->AddPieceAtLocationParams->size(), 0);
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(GetActiveColor)
	
		BOOST_FIXTURE_TEST_CASE(Uninitialized_ThrowsRuntimeErrorException, GameWithParserTestFixture)
		{
			/* Piece numbers */
			BOOST_CHECK_THROW(game->GetActiveColor(), runtime_error);
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(IFENParserDelegate_)

		BOOST_AUTO_TEST_CASE(UnsolicitedParser_ThrowsInvalidArgumentException)
		{
			shared_ptr<IO::IFENParser> parser = make_shared<IO::Mocks::FENParser>();
			auto game = make_shared<Game>(make_shared<Mocks::Board>(), make_shared<Player>(Player::White), make_shared<Player>(Player::Black));
			BOOST_CHECK_THROW(game->FENParserError(*parser, "test"), invalid_argument);
			BOOST_CHECK_THROW(game->FENParserPiece(*parser, Location::a1, IPlayer::White, IPiece::Rook), invalid_argument);
			BOOST_CHECK_THROW(game->FENParserActiveColor(*parser, IPlayer::White), invalid_argument);
			BOOST_CHECK_THROW(game->FENParserCompleted(*parser), invalid_argument);			
		}

		BOOST_AUTO_TEST_SUITE(FENParserError)

			BOOST_FIXTURE_TEST_CASE(ThrowsRuntimeErrorException, GameWithParserTestFixture)
			{
				BOOST_CHECK_THROW(game->FENParserError(*parser, "test"), runtime_error);
			}

		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(FENParserPiece)

			BOOST_FIXTURE_TEST_CASE(CallsBoard_AddPieceAtLocation, GameWithParserTestFixture)
			{
				game->FENParserPiece(*parser, Location::a1, Player::White, IPiece::Pawn);
				BOOST_REQUIRE_EQUAL(board->AddPieceAtLocationParams->size(), 1);
				shared_ptr<IPiece> addedPiece = get<0>((*board->AddPieceAtLocationParams)[0]);
				const Location& location = get<1>((*board->AddPieceAtLocationParams)[0]);
				BOOST_CHECK_EQUAL(addedPiece->GetColor(), Player::White);
				BOOST_CHECK_EQUAL(addedPiece->GetType(), IPiece::Pawn);	
				BOOST_CHECK_EQUAL(location, Location::a1);				
			}

		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(FENParserActiveColor)

			BOOST_FIXTURE_TEST_CASE(SetsActiveColor, GameWithParserTestFixture)
			{
				game->FENParserActiveColor(*parser, IPlayer::White);
				BOOST_CHECK_EQUAL(game->GetActiveColor(), IPlayer::White);				
			}

		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()