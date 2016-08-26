#include "mocks/FENParserDelegate.hpp"

namespace Chess
{
namespace IO
{
namespace Mocks
{
	using namespace std;

	void FENParserDelegate::FENParserError(FENParser& parser, const std::string& error)
	{
		FENParserErrorParams.push_back(make_tuple(&parser, error));
	}

	void FENParserDelegate::FENParserPiece(FENParser& parser, Location location, Player::Color color, IPiece::Type type)
	{
		FENParserPieceParams.push_back(make_tuple(&parser, location, color, type));
	}

	void FENParserDelegate::FENParserActiveColor(FENParser& parser, Player::Color color)
	{
		FENParserActiveColorParams.push_back(make_tuple(&parser, color));
	}

	void FENParserDelegate::FENParserCompleted(FENParser& parser)
	{
		FENParserCompletedParams.push_back(make_tuple(&parser));
	}
}
}
}