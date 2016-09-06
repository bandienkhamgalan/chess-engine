#pragma once
#include "IBoard.hpp"
#include "Location.hpp"

namespace Chess
{
	class IObservableBoardObservor;
	class IObservableBoard
		: public IBoard
	{
	public:
		virtual ~IObservableBoard() {};

		virtual void AddListener(IObservableBoardObservor &observor) = 0;
		virtual void AddListenerForSquare(IObservableBoardObservor &observor, const Location& location) = 0;
		virtual void RemoveListener(IObservableBoardObservor &observor) = 0;
		virtual void RemoveListenerForSquare(IObservableBoardObservor &observor, const Location& location) = 0;
	};
}