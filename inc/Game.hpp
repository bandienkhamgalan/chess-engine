#pragma once

#include <memory>
#include <string>
#include "IPlayer.hpp"
#include "IPiece.hpp"
#include "IPieceFactory.hpp"
#include "IObservableBoard.hpp"
#include "IFENParser.hpp"
#include "IFENParserDelegate.hpp"

namespace Chess
{
	class Game
		: public IO::IFENParserDelegate
	{
	public:
		Game() = delete;
		Game(std::shared_ptr<IObservableBoard> board, std::shared_ptr<IPieceFactory> pieceFactory, std::shared_ptr<IPlayer> white, std::shared_ptr<IPlayer> black);
		Game(std::shared_ptr<IObservableBoard> board, std::shared_ptr<IPieceFactory> pieceFactory, std::shared_ptr<IPlayer> white, std::shared_ptr<IPlayer> black, std::shared_ptr<IO::IFENParser> parser);

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
		std::shared_ptr<IObservableBoard> board;
		std::shared_ptr<IPieceFactory> pieceFactory;
		std::shared_ptr<IPlayer> white;
		std::shared_ptr<IPlayer> black;
		std::shared_ptr<IO::IFENParser> FENParser;
		IPlayer::Color activeColor;

		void DefaultSetup();
		IPlayer& GetPlayer(const IPlayer::Color& color);
		void CreatePieceForPlayerAtLocation(const IPlayer::Color& color, const Location& location, const IPiece::Type& type);
	};
}