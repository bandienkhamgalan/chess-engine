#pragma once
#include <map>
#include <memory>
#include "gmock/gmock.h"
#include "ISquareFactory.hpp"
#include "ISquare.hpp"
#include "Location.hpp"

namespace Chess
{
namespace Mocks
{
	class SquareFactory
		: public ISquareFactory
	{
	public:
		MOCK_METHOD1(makeSquare, std::unique_ptr<ISquare>(const Location&));
	};
}
}