#pragma once

#include <memory>
#include <string>
#include "Player.hpp"
#include "IPiece.hpp"
#include "Board.hpp"
#include "SimpleSquareFactory.hpp"
#include "FENParser.hpp"

namespace Chess
{
	class Game
		: public IO::IFENParserDelegate
	{
	public:
		Game();
		Game(const std::string& FEN);

		const Board& GetBoard();
		const Player& GetWhitePlayer();
		const Player& GetBlackPlayer();
		Player::Color GetActiveColor();

		/* IO::IFenParserDelegate functions */
		void FENParserError(IO::FENParser& parser, const std::string& error) override;
		void FENParserPiece(IO::FENParser& parser, Location location, Player::Color color, IPiece::Type type) override;
		void FENParserActiveColor(IO::FENParser& parser, Player::Color color) override;
		void FENParserCompleted(IO::FENParser& parser) override;

	private:
		std::unique_ptr<Player> white;
		std::unique_ptr<Player> black;
		SimpleSquareFactory simpleSquareFactory;
		std::unique_ptr<Board> board;
		std::unique_ptr<IO::FENParser> fenParser;
		Player::Color activeColor;
	};
}