#pragma once

#include <memory>
#include <string>
#include "IPlayer.hpp"
#include "IPiece.hpp"
#include "IBoard.hpp"
#include "IFENParser.hpp"
#include "IFENParserDelegate.hpp"

namespace Chess
{
	class Game
		: public IO::IFENParserDelegate
	{
	public:
		Game() = delete;
		Game(std::shared_ptr<IBoard> board, std::shared_ptr<IPlayer> white, std::shared_ptr<IPlayer> black);
		Game(std::shared_ptr<IBoard> board, std::shared_ptr<IPlayer> white, std::shared_ptr<IPlayer> black, std::shared_ptr<IO::IFENParser> parser);

		const IBoard& GetBoard();
		const IPlayer& GetWhitePlayer();
		const IPlayer& GetBlackPlayer();
		IPlayer::Color GetActiveColor();

		/* IO::IFENParserDelegate methods */
		void FENParserError(IO::IFENParser& parser, const std::string& error) override;
		void FENParserPiece(IO::IFENParser& parser, Location location, IPlayer::Color color, IPiece::Type type) override;
		void FENParserActiveColor(IO::IFENParser& parser, IPlayer::Color color) override;
		void FENParserCompleted(IO::IFENParser& parser) override;

	private:
		void DefaultSetup();
		void CreatePieceForPlayerAtLocation(IPlayer::Color color, Location location, IPiece::Type type);
		std::shared_ptr<IPlayer> white;
		std::shared_ptr<IPlayer> black;
		std::shared_ptr<IBoard> board;
		std::shared_ptr<IO::IFENParser> FENParser;
		IPlayer::Color activeColor;
	};
}