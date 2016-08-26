#include "FENParser.hpp"
#include "Helpers.hpp"
#include <stdexcept>
#include <string>

namespace Chess
{
namespace IO
{
	using namespace std;

	/* Constructor */

	FENParser::FENParser(IFENParserDelegate& delegate, const string& FEN)
		: delegate(delegate), FEN(FEN)
	{
		
	}

	/* Public methods */

	void FENParser::BeginParsing()
	{
		try
		{
			string toParse = Helpers::trimmed(FEN);
			// Validate (length)
			if(toParse.length() < 25)
				throw invalid_argument("PRE-VALIDATION: failed string length check");

			// Validate (character set)
			const auto firstNonValid = toParse.find_first_not_of("PNBRQKpnbrqk0123456789WwBbABCDEFGHabcdefgh/- ");
			if(firstNonValid != string::npos)
				throw invalid_argument(Helpers::sprint("PRE-VALIDATION: character set check failed at pos ", firstNonValid, ": ", toParse[firstNonValid]));

			// Validate (split & check number of components)
			auto components = Helpers::split(toParse);
			if(components.size() != 6)
				throw invalid_argument(Helpers::sprint("PRE-VALIDATION: failed component count check"));

			ParsePiecePlacement(components[0]);
			ParseActiveColor(components[1]);

			delegate.FENParserCompleted(*this);
		}
		catch(const invalid_argument& exception)
		{
			delegate.FENParserError(*this, exception.what());
		}
	}

	bool FENParser::operator==(const FENParser& toCompare)
	{
		return this == &toCompare;
	}

	bool FENParser::operator!=(const FENParser& toCompare)
	{
		return this != &toCompare;
	}

	/* Private methods */

	void FENParser::ParsePiecePlacement(const string& toParse)
	{
		auto iter = toParse.cbegin();
		for( uint16_t rank = 8 ; rank >= 1 ; --rank )
		{
			uint16_t file = 0;
			while(true)
			{
				if(*iter >= '1' && *iter <= '8')
					file += *iter - '0';
				else
				{
					++file;

					Player::Color color;
					IPiece::Type type;
					if(ParsePiece(*iter, color, type))
						delegate.FENParserPiece(*this, Location(static_cast<Location::File>(file), rank), color, type);
					else
						throw invalid_argument(Helpers::sprint("PIECE PLACEMENT: failed to parse piece in rank ", rank, ": ", *iter));
				}

				++iter;

				if(iter == toParse.cend() || *iter == '/' || file > 8)
					break;
			}

			if(file != 8)
				throw invalid_argument(Helpers::sprint("PIECE PLACEMENT: rank ", rank, " had more than 8 files : ", file));
			if(rank == 1 && iter != toParse.cend())
				throw invalid_argument(Helpers::sprint("PIECE PLACEMENT: had unexpected contents after last rank"));
			
			++iter;
		}			
	}

	void FENParser::ParseActiveColor(const string& toParse)
	{
		// Validate (length)
		if(toParse.length() != 1)
			throw invalid_argument("ACTIVE COLOR: failed string length check");

		switch(toParse[0])
		{
			case 'w':
			case 'W':
				delegate.FENParserActiveColor(*this, Player::White);
				break;
			case 'b':
			case 'B':
				delegate.FENParserActiveColor(*this, Player::Black);
				break;
			default:
				throw invalid_argument(Helpers::sprint("ACTIVE COLOR: expected 'w' or 'b', given : ", toParse[0]));
		}
	}

	bool FENParser::ParsePiece(const char& c, Player::Color& color, IPiece::Type& type)
	{
		switch(c)
		{
			case 'R':
				color = Player::White;
				type = IPiece::Rook;
				return true;
			case 'N':
				color = Player::White;
				type = IPiece::Knight;
				return true;
			case 'B':
				color = Player::White;
				type = IPiece::Bishop;
				return true;
			case 'Q':
				color = Player::White;
				type = IPiece::Queen;
				return true;
			case 'K':
				color = Player::White;
				type = IPiece::King;
				return true;
			case 'P':
				color = Player::White;
				type = IPiece::Pawn;
				return true;
			case 'r':
				color = Player::Black;
				type = IPiece::Rook;
				return true;
			case 'n':
				color = Player::Black;
				type = IPiece::Knight;
				return true;
			case 'b':
				color = Player::Black;
				type = IPiece::Bishop;
				return true;
			case 'q':
				color = Player::Black;
				type = IPiece::Queen;
				return true;
			case 'k':
				color = Player::Black;
				type = IPiece::King;
				return true;
			case 'p':
				color = Player::Black;
				type = IPiece::Pawn;
				return true;
			default:
				return false;
		}
	}
}
}