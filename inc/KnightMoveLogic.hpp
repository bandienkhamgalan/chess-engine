#pragma once
#include "IObservableBoardObservor.hpp"

namespace Chess
{
namespace Logic
{
	class KnightMoveLogic
		: public IObservableBoardObservor
	{
	public: 
		KnightMoveLogic(const IObservableBoard& board, const IPiece& knight);
		void SquareDidChange(IObservableBoard &board);
	}
}
}