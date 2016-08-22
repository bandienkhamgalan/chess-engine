#pragma once

#include "ISquare.hpp"
#include <memory>

namespace Chess
{
	class ISquareFactory
	{
	public:
		virtual std::unique_ptr<ISquare> makeSquare(const Location& location) = 0;
		virtual ~ISquareFactory() {};
	};
}