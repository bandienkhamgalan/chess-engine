#pragma once
#include <memory>

namespace Chess
{
	class IObservableSquare;
	class Location;
	class IObservableSquareFactory
	{
	public:
		virtual ~IObservableSquareFactory() {};
		
		virtual std::unique_ptr<IObservableSquare> makeSquare(const Location& location) = 0;
	};
}