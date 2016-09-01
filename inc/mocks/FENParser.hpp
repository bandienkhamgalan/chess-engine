#pragma once
#include <memory>
#include "IFENParser.hpp"

namespace Chess
{
namespace IO
{
namespace Mocks
{
	class FENParser
		: public IFENParser
	{
	public:
		void SetDelegate(std::shared_ptr<IFENParserDelegate> delegate) override;
		void BeginParsing() override;
		bool operator==(const IFENParser& toCompare) override;
		bool operator!=(const IFENParser& toCompare) override;
	};
}
}
}