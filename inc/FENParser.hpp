#pragma once

#include <string>
#include "Player.hpp"
#include "Location.hpp"
#include "IPiece.hpp"

namespace Chess
{
namespace IO
{
	class FENParser;

	class IFENParserDelegate
	{
	public:
		virtual void FENParserError(FENParser& parser, const std::string& error) {};
		virtual void FENParserPiece(FENParser& parser, Location location, Player::Color color, IPiece::Type type) {};
		virtual void FENParserActiveColor(FENParser& parser, Player::Color color) {};
		virtual void FENParserCompleted(FENParser& parser) {};
		virtual ~IFENParserDelegate() {};
	};

	class FENParser
	{
	public:
		FENParser() = delete;
		FENParser(IFENParserDelegate& delegate, const std::string& FEN);
		void BeginParsing();
		bool operator==(const FENParser& toCompare);
		bool operator!=(const FENParser& toCompare);
	private:
		void ParsePiecePlacement(const std::string& toParse);
		void ParseActiveColor(const std::string& toParse);
		bool ParsePiece(const char& c, Player::Color& color, IPiece::Type& type);
		IFENParserDelegate& delegate;
		const std::string FEN;
	};
}
}