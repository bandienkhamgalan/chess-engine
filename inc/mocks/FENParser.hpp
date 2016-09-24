#pragma once
#include <memory>
#include "gmock/gmock.h"
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
		MOCK_METHOD1(SetDelegate, void(std::shared_ptr<IFENParserDelegate>));
		MOCK_METHOD0(BeginParsing, void());
	};
}
}
}