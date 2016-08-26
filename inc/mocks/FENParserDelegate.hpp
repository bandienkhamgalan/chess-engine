#pragma once

#include "FENParser.hpp"
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
		std::vector<std::tuple<FENParser*, std::string>> FENParserErrorParams;
		void FENParserError(FENParser& parser, const std::string& error) override;

		std::vector<std::tuple<FENParser*, Location, Player::Color, IPiece::Type>> FENParserPieceParams;
		void FENParserPiece(FENParser& parser, Location location, Player::Color color, IPiece::Type type) override;

		std::vector<std::tuple<FENParser*, Player::Color>> FENParserActiveColorParams;
		void FENParserActiveColor(FENParser& parser, Player::Color color) override;

		std::vector<std::tuple<FENParser*>> FENParserCompletedParams; 
		void FENParserCompleted(FENParser& parser) override;
	};
}
}
}