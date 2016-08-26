#include "Game.hpp"
#include "Piece.hpp"
#include "Helpers.hpp"

namespace Chess
{
	using namespace std;

	Game::Game(const string& FEN)
		: white { new Player(Player::White) }, black { new Player(Player::Black) }, board { new Board(simpleSquareFactory) }, activeColor { Player::UNDEFINED }
	{
		IFENParserDelegate& self = *this;
		fenParser.reset(new IO::FENParser(self, FEN));
		fenParser->BeginParsing();
	}

	Game::Game()
		: Game("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1")
	{
		
	}

	const Board& Game::GetBoard()
	{
		return *board;
	}

	const Player& Game::GetWhitePlayer()
	{
		return *white;
	}

	const Player& Game::GetBlackPlayer()
	{
		return *black;
	}

	Player::Color Game::GetActiveColor()
	{
		return activeColor;
	}

	/* IO::IFENParserDelegate methods */

	void Game::FENParserError(IO::FENParser& parser, const std::string& error)
	{
		if(&parser == fenParser.get())
		{
			throw invalid_argument(Helpers::sprint("Game::Game() : FEN parse error : ", error));
			fenParser.reset(nullptr);
		}
	}

	void Game::FENParserPiece(IO::FENParser& parser, Location location, Player::Color color, IPiece::Type type)
	{
		if(parser == *fenParser)
		{
			Player& player = color == Player::White ? *white : *black;
			shared_ptr<IPiece> piece = make_shared<Piece>(player, type);
			player.AddPiece(piece);
			board->AddPieceAtLocation(piece, location);
		}
	}
	
	void Game::FENParserActiveColor(IO::FENParser& parser, Player::Color color)
	{
		if(parser == *fenParser)
		{
			activeColor = color;
		}
	}

	void Game::FENParserCompleted(IO::FENParser& parser)
	{
		if(parser == *fenParser)
		{
			fenParser.reset(nullptr);
		}
	}
}