#pragma once
#include "IPlayer.hpp"
#include "IPiece.hpp"
#include "Location.hpp"

namespace Chess
{
namespace IO
{
	class IFENParser;
	class IFENParserDelegate
	{
	public:
		virtual void FENParserError(IFENParser& parser, const std::string& error) {};
		virtual void FENParserPiece(IFENParser& parser, Location location, IPlayer::Color color, IPiece::Type type) {};
		virtual void FENParserActiveColor(IFENParser& parser, IPlayer::Color color) {};
		virtual void FENParserCompleted(IFENParser& parser) {};
		virtual ~IFENParserDelegate() {};
	};
}
}