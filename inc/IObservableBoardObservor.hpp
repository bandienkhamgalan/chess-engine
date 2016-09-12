#pragma once
#include "Location.hpp"

namespace Chess
{
	class IObservableBoard;
	class IObservableBoardObservor
	{
	public:
		virtual ~IObservableBoardObservor() {};
		virtual void SquareDidChange(IObservableBoard &board, const Location& location) = 0;
	};
}