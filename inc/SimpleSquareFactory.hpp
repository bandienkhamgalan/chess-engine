#pragma once

#include "ISquareFactory.hpp"

namespace Chess
{
	class SimpleSquareFactory
		: public ISquareFactory
	{
	public:
		std::unique_ptr<ISquare> makeSquare(const Location& location) override;
	};
}