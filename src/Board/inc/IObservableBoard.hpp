#pragma once
#include "IBoard.hpp"
#include "Location.hpp"
#include "IObservableSquare.hpp"

namespace Chess
{
	class IObservableBoardObservor;
	class IObservableBoard
		: public IBoard
	{
	public:
		virtual ~IObservableBoard() {};

		virtual void AddListener(IObservableBoardObservor* observor, const IObservableSquare::Event& event) = 0;
		virtual void AddListenerForSquare(IObservableBoardObservor* observor, const Location& location, const IObservableSquare::Event& event) = 0;
		virtual void RemoveListener(IObservableBoardObservor* observor, const IObservableSquare::Event& event) = 0;
		virtual void RemoveListenerForSquare(IObservableBoardObservor* observor, const Location& location, const IObservableSquare::Event& event) = 0;
	};
}