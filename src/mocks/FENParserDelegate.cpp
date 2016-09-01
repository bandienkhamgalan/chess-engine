#include "mocks/FENParserDelegate.hpp"

namespace Chess
{
namespace IO
{
namespace Mocks
{
	using namespace std;

	void FENParserDelegate::FENParserError(IFENParser& parser, const std::string& error)
	{
		FENParserErrorParams.push_back(make_tuple(&parser, error));
	}

	void FENParserDelegate::FENParserPiece(IFENParser& parser, Location location, Player::Color color, IPiece::Type type)
	{
		FENParserPieceParams.push_back(make_tuple(&parser, location, color, type));
	}

	void FENParserDelegate::FENParserActiveColor(IFENParser& parser, Player::Color color)
	{
		FENParserActiveColorParams.push_back(make_tuple(&parser, color));
	}

	void FENParserDelegate::FENParserCompleted(IFENParser& parser)
	{
		FENParserCompletedParams.push_back(make_tuple(&parser));
	}
}
}
}