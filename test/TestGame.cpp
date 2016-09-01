#include "Game.hpp"
#include "Board.hpp"
#include "Player.hpp"
#include "SimpleSquareFactory.hpp"
#include "IFENParser.hpp"
#include "mocks/FENParser.hpp"
#include "Location.hpp"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(Game_)

	using namespace std;
	using namespace Chess;

	BOOST_AUTO_TEST_SUITE(Constructor_Default)
	
		BOOST_AUTO_TEST_CASE(InitializesBoardPlayerPiecesAndActiveColor)
		{
			SimpleSquareFactory squareFactory;
			Game game(make_shared<Board>(squareFactory), make_shared<Player>(Player::White), make_shared<Player>(Player::Black));

			/* Active color */
			BOOST_CHECK_EQUAL(game.GetActiveColor(), Player::White);

			/* Piece numbers */
			const auto& white = game.GetWhitePlayer();
			const auto& whitePieces = white.GetPieces();
			BOOST_CHECK_EQUAL(whitePieces.size(), 16);
			const auto& black = game.GetBlackPlayer();
			const auto& blackPieces = black.GetPieces();
			BOOST_CHECK_EQUAL(blackPieces.size(), 16);

			const auto& board = game.GetBoard();

			/* Black pieces */
			for(int rank = 7 ; rank <= 8 ; rank++)
				for(int file = 1 ; file <= 8 ; file++)
					BOOST_CHECK_EQUAL(board.GetPieceAtLocation(Location(file, rank)).GetPlayer().GetColor(), Player::Black);

			IPiece::Type types[] = { IPiece::Rook, IPiece::Knight, IPiece::Bishop, IPiece::Queen, IPiece::King, IPiece::Bishop, IPiece::Knight, IPiece::Rook };
			for(int file = 1 ; file <= 8 ; file++)
				BOOST_CHECK_EQUAL(board.GetPieceAtLocation(Location(file, 8)).GetType(), types[file - 1]);

			for(int file = 1 ; file <= 8 ; file++)
				BOOST_CHECK_EQUAL(board.GetPieceAtLocation(Location(file, 7)).GetType(), IPiece::Pawn);

			/* Empty pieces */
			for(int rank = 3 ; rank <= 6 ; rank++)
				for( int file = 1 ; file <= 8 ; file++ )
					BOOST_CHECK_EQUAL(board.HasPieceAtLocation(Location(file, rank)), false);

			/* White pieces */
			for(int rank = 1 ; rank <= 2 ; rank++)
				for(int file = 1 ; file <= 8 ; file++)
					BOOST_CHECK_EQUAL(board.GetPieceAtLocation(Location(file, rank)).GetPlayer().GetColor(), Player::White);

			for(int file = 1 ; file <= 8 ; file++)
				BOOST_CHECK_EQUAL(board.GetPieceAtLocation(Location(file, 1)).GetType(), types[file - 1]);

			for(int file = 1 ; file <= 8 ; file++)
				BOOST_CHECK_EQUAL(board.GetPieceAtLocation(Location(file, 2)).GetType(), IPiece::Pawn);
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(Constructor_Parser)
	
		BOOST_AUTO_TEST_CASE(DoesNotInitializeBoard)
		{
			SimpleSquareFactory squareFactory;
			auto game = make_shared<Game>(make_shared<Board>(squareFactory), make_shared<Player>(Player::White), make_shared<Player>(Player::Black), make_shared<IO::Mocks::FENParser>());
			
			/* Piece numbers */
			BOOST_CHECK_EQUAL(game->GetWhitePlayer().GetPieces().size(), 0);
			BOOST_CHECK_EQUAL(game->GetBlackPlayer().GetPieces().size(), 0);

			const auto& board = game->GetBoard();
			Location::for_each( [&board](const Location& current)
			{
				BOOST_CHECK_EQUAL(board.HasPieceAtLocation(current), false);
			});
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(IFENParserDelegate_)

		BOOST_AUTO_TEST_SUITE(FENParserError)

			BOOST_AUTO_TEST_CASE(UnsolicitedParser_ThrowsInvalidArgumentException)
			{
				SimpleSquareFactory squareFactory;
				shared_ptr<IO::IFENParser> parser = make_shared<IO::Mocks::FENParser>();
				auto game = make_shared<Game>(make_shared<Board>(squareFactory), make_shared<Player>(Player::White), make_shared<Player>(Player::Black));
				BOOST_CHECK_THROW(game->FENParserError(*parser, "test"), invalid_argument);
			}

			BOOST_AUTO_TEST_CASE(SolicitedParser_ThrowsRuntimeErrorException)
			{
				SimpleSquareFactory squareFactory;
				shared_ptr<IO::IFENParser> parser = make_shared<IO::Mocks::FENParser>();
				auto game = make_shared<Game>(make_shared<Board>(squareFactory), make_shared<Player>(Player::White), make_shared<Player>(Player::Black), parser);
				BOOST_CHECK_THROW(game->FENParserError(*parser, "test"), runtime_error);
			}

		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(FENParserPiece)

			BOOST_AUTO_TEST_CASE(UnsolicitedParser_ThrowsInvalidArgumentException)
			{
				SimpleSquareFactory squareFactory;
				shared_ptr<IO::IFENParser> parser = make_shared<IO::Mocks::FENParser>();
				auto game = make_shared<Game>(make_shared<Board>(squareFactory), make_shared<Player>(Player::White), make_shared<Player>(Player::Black));
				BOOST_CHECK_THROW(game->FENParserPiece(*parser, Location::a1, Player::White, IPiece::Pawn), invalid_argument);
			}

			BOOST_AUTO_TEST_CASE(SolicitedParser_AddsPieceToSquare)
			{
				SimpleSquareFactory squareFactory;
				shared_ptr<IO::IFENParser> parser = make_shared<IO::Mocks::FENParser>();
				auto game = make_shared<Game>(make_shared<Board>(squareFactory), make_shared<Player>(Player::White), make_shared<Player>(Player::Black), parser);
				game->FENParserPiece(*parser, Location::a1, Player::White, IPiece::Pawn);
			}

		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()