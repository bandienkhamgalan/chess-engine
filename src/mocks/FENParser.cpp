#include "mocks/FENParser.hpp"

namespace Chess
{
namespace IO
{
namespace Mocks
{
	void FENParser::SetDelegate(std::shared_ptr<IFENParserDelegate> delegate)
	{

	}
	
	void FENParser::BeginParsing()
	{

	}

	bool FENParser::operator==(const IFENParser& toCompare)
	{
		return this == &toCompare;
	}
	
	bool FENParser::operator!=(const IFENParser& toCompare)
	{
		return !this->operator==(toCompare);
	}
	
}
}
}