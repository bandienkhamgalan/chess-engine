#pragma once
#include <vector>
#include "IObservableBoardObservor.hpp"
#include "IPieceMoveLogic.hpp"

namespace Chess
{
namespace Logic
{
	class KnightMoveLogic
		: public IObservableBoardObservor, public IPieceMoveLogic
	{
	public: 
		KnightMoveLogic(const IObservableBoard& board, const IPiece& piece);

		const std::vector<Location>& GetValidMoves() const override;

		/* IObservableBoardObservor methods */
		void SquareDidChange(IObservableBoard &board, const Location& location);

	private:
		IObservableBoard &board;
		IPiece& piece;
		std::vector<Location> validMoves;
		void RecomputeValidMoves();
		void UnregisterListeners();
		void RegisterListeners();
	};
}
}