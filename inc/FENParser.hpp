#pragma once

#include <string>
#include <memory>
#include "IFENParser.hpp"
#include "Player.hpp"
#include "Location.hpp"
#include "IPiece.hpp"
#include "IFENParserDelegate.hpp"

namespace Chess
{
namespace IO
{
	class FENParser
		: public IFENParser
	{
	public:
		FENParser() = delete;
		FENParser(const std::string& FEN, std::shared_ptr<IFENParserDelegate> delegate = nullptr);
		void SetDelegate(std::shared_ptr<IFENParserDelegate> delegate) override;
		void BeginParsing() override;
		bool operator==(const IFENParser& toCompare) override;
		bool operator!=(const IFENParser& toCompare) override;
	private:
		void ParsePiecePlacement(const std::string& toParse);
		void ParseActiveColor(const std::string& toParse);
		bool ParsePiece(const char& c, Player::Color& color, IPiece::Type& type);
		std::weak_ptr<IFENParserDelegate> delegate;
		const std::string FEN;
	};
}
}