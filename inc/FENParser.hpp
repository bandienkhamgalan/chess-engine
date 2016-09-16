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
		FENParser(const std::string& _FEN, std::shared_ptr<IFENParserDelegate> _delegate = nullptr);
		void SetDelegate(std::shared_ptr<IFENParserDelegate> _delegate) override;
		void BeginParsing() override;
		bool operator==(const IFENParser& toCompare) override;
		bool operator!=(const IFENParser& toCompare) override;
	private:
		const std::string FEN;
		std::weak_ptr<IFENParserDelegate> delegate;
		
		void ParsePiecePlacement(const std::string& toParse);
		void ParseActiveColor(const std::string& toParse);
		bool ParsePiece(const char& c, Player::Color& color, IPiece::Type& type);
	};
}
}