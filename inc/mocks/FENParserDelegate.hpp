#pragma once

#include "IFENParserDelegate.hpp"
#include "IFENParser.hpp"
#include "Player.hpp"
#include "IPiece.hpp"
#include "Location.hpp"
#include <vector>
#include <tuple>

namespace Chess
{
namespace IO
{
namespace Mocks
{
	class FENParserDelegate
		: public IFENParserDelegate
	{
	public:
		std::vector<std::tuple<IFENParser*, std::string>> FENParserErrorParams;
		void FENParserError(IFENParser& parser, const std::string& error) override;

		std::vector<std::tuple<IFENParser*, Location, IPlayer::Color, IPiece::Type>> FENParserPieceParams;
		void FENParserPiece(IFENParser& parser, Location location, IPlayer::Color color, IPiece::Type type) override;

		std::vector<std::tuple<IFENParser*, IPlayer::Color>> FENParserActiveColorParams;
		void FENParserActiveColor(IFENParser& parser, IPlayer::Color color) override;

		std::vector<std::tuple<IFENParser*>> FENParserCompletedParams; 
		void FENParserCompleted(IFENParser& parser) override;
	};
}
}
}