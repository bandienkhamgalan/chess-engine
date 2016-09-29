#pragma once
#include "IObservableSquare.hpp"

namespace Chess
{
	class IObservableSquareObservor
	{
	public:
		virtual ~IObservableSquareObservor() {};
		virtual void SquareDidChange(const Location& location, const IObservableSquare::Event& event) = 0;
	};
}