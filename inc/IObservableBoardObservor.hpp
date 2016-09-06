#pragma once

namespace Chess
{
	class IObservableBoard;
	class IObservableBoardObservor
	{
	public:
		virtual ~IObservableBoardObservor() {};
		virtual void SquareDidChange(IObservableBoard &board) = 0;
	};
}