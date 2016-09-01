#pragma once
#include <memory>

namespace Chess
{
	class ISquare;
	class Location;
	class ISquareFactory
	{
	public:
		virtual std::unique_ptr<ISquare> makeSquare(const Location& location) = 0;
		virtual ~ISquareFactory() {};
	};
}