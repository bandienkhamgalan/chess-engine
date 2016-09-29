#pragma once
#include <vector>
#include <tuple>
#include "gmock/gmock.h"
#include "IFENParserDelegate.hpp"
#include "IFENParser.hpp"
#include "Player.hpp"
#include "IPiece.hpp"
#include "Location.hpp"

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
		MOCK_METHOD2(FENParserError, void(IFENParser&, const std::string&));
		MOCK_METHOD4(FENParserPiece, void(IFENParser&, Location, IPlayer::Color, IPiece::Type));
		MOCK_METHOD2(FENParserActiveColor, void(IFENParser&, IPlayer::Color));
		MOCK_METHOD1(FENParserCompleted, void(IFENParser&));
	};
}
}
}