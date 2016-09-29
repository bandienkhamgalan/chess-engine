#include "Game.hpp"
#include "Piece.hpp"
#include "Helpers.hpp"

namespace Chess
{
	using namespace std;

	Game::Game(shared_ptr<IObservableBoard> board, shared_ptr<IPieceFactory> pieceFactory, std::shared_ptr<IPlayer> white, std::shared_ptr<IPlayer> black)
		: board(board), pieceFactory(pieceFactory), white(white), black(black), activeColor(IPlayer::White)
	{
		DefaultSetup();
	}

	Game::Game(std::shared_ptr<IObservableBoard> board, shared_ptr<IPieceFactory> pieceFactory, std::shared_ptr<IPlayer> white, std::shared_ptr<IPlayer> black, std::shared_ptr<IO::IFENParser> parser)
		: board(board), pieceFactory(pieceFactory), white(white), black(black), activeColor(IPlayer::UNDEFINED)
	{
		if(!parser)
			throw invalid_argument("Game::Game() : must pass in non-null parser object");
		FENParser = parser;
	}

	const IBoard& Game::GetBoard()
	{
		return *board;
	}

	const IPlayer& Game::GetWhitePlayer()
	{
		return *white;
	}

	const IPlayer& Game::GetBlackPlayer()
	{
		return *black;
	}

	IPlayer::Color Game::GetActiveColor()
	{
		if(activeColor != IPlayer::White && activeColor != IPlayer::Black)
			throw runtime_error("Game::GetActiveColor() : Game is still initializing, there is no active color");
		
		return activeColor;
	}

	/* IO::IFENParserDelegate methods */

	void Game::FENParserError(IO::IFENParser& parser, const std::string& error)
	{
		if(parser != *FENParser)
			throw invalid_argument("Game::FENParserError() : Unsolicited parser event");
		
		throw runtime_error(Helpers::sprint("Game::FENParserError() : FEN parse error : ", error));
		FENParser = nullptr;
	}

	void Game::FENParserPiece(IO::IFENParser& parser, Location location, IPlayer::Color color, IPiece::Type type)
	{
		if(parser != *FENParser)
			throw invalid_argument("Game::FENParserPiece() : Unsolicited parser event");

		CreatePieceForPlayerAtLocation(color, location, type);
	}
	
	void Game::FENParserActiveColor(IO::IFENParser& parser, IPlayer::Color color)
	{
		if(parser != *FENParser)
			throw invalid_argument("Game::FENParserActiveColor() : Unsolicited parser event");
		
		activeColor = color;
	}

	void Game::FENParserCompleted(IO::IFENParser& parser)
	{
		if(parser != *FENParser)
			throw invalid_argument("Game::FENParserCompleted() : Unsolicited parser event");
		
		FENParser = nullptr;
	}

	/* Private methods */

	void Game::DefaultSetup()
	{
		IPiece::Type types[] = { IPiece::Rook, IPiece::Knight, IPiece::Bishop, IPiece::Queen, IPiece::King, IPiece::Bishop, IPiece::Knight, IPiece::Rook };
		for(auto file = 1 ; file <= 8 ; file++)
		{
			CreatePieceForPlayerAtLocation(IPlayer::Black, Location(file, 8), types[file - 1]);
		}

		for(auto file = 1 ; file <= 8 ; file++)
		{
			CreatePieceForPlayerAtLocation(IPlayer::Black, Location(file, 7), IPiece::Pawn);
		}

		for(auto file = 1 ; file <= 8 ; file++)
		{
			CreatePieceForPlayerAtLocation(IPlayer::White, Location(file, 2), IPiece::Pawn);
		}

		for(auto file = 1 ; file <= 8 ; file++)
		{
			CreatePieceForPlayerAtLocation(IPlayer::White, Location(file, 1), types[file - 1]);
		}
	}

	void Game::CreatePieceForPlayerAtLocation(const IPlayer::Color& color, const Location& location, const IPiece::Type& type)
	{
		IPlayer& player = GetPlayer(color);
		shared_ptr<IPiece> piece = pieceFactory->makePiece(board, player, type);
		player.AddPiece(piece);
		board->AddPieceAtLocation(piece, location);
	}

	IPlayer& Game::GetPlayer(const IPlayer::Color& color)
	{
		if(color == IPlayer::White)
			return *white;
		else if(color == IPlayer::Black)
			return *black;
		else
			throw invalid_argument("Game::GetPlayer() : color must be White or Black");
	}
}