#include "Game.hpp"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(Game_)

	using namespace std;
	using namespace Chess;	

	BOOST_AUTO_TEST_SUITE(Constructor)
	
		BOOST_AUTO_TEST_CASE(InitializesBoardPlayerPiecesAndActiveColor)
		{
			Game game;

			/* Active color */
			BOOST_CHECK_EQUAL(game.GetActiveColor(), Player::White);

			/* Piece numbers */
			auto white = game.GetWhitePlayer();
			auto whitePieces = white.GetPieces();
			BOOST_CHECK_EQUAL(whitePieces.size(), 16);
			auto black = game.GetBlackPlayer();
			auto blackPieces = black.GetPieces();
			BOOST_CHECK_EQUAL(whitePieces.size(), 16);

			auto board = game.GetBoard();

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

BOOST_AUTO_TEST_SUITE_END()