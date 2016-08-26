#pragma once

#include "ISquareFactory.hpp"
#include "ISquare.hpp"
#include "Location.hpp"
#include <map>
#include <memory>

namespace Chess
{
namespace Mocks
{
	class SquareFactory
		: public ISquareFactory
	{
	public:
		std::map<Location, int> makeSquareCalls;
		std::unique_ptr<ISquare> makeSquare(const Location& location) override;
	};
}
}