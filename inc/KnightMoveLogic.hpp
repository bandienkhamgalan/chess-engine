#pragma once
#include <vector>
#include "IObservableBoardObservor.hpp"
#include "IPieceMoveLogic.hpp"
#include "IPiece.hpp"
#include "IObservableBoard.hpp"

namespace Chess
{
	class KnightMoveLogic
		: public IObservableBoardObservor, public IPieceMoveLogic
	{
	public: 
		KnightMoveLogic(std::weak_ptr<IObservableBoard> _board);
		KnightMoveLogic(std::weak_ptr<IObservableBoard> _board, std::weak_ptr<IPiece> _piece);
		~KnightMoveLogic();
		
		void SetPiece(std::weak_ptr<IPiece> toSet) override;
		
		const std::vector<Location>& GetValidMoves() override;

		/* IObservableBoardObservor methods */
		void SquareDidChange(IObservableBoard &board, const Location& location) override;
	private:
		std::weak_ptr<IObservableBoard> board;
		std::weak_ptr<IPiece> piece;
		std::vector<Location> validMoves;
		void RecomputeValidMoves();
		void UnregisterListeners();
		void RegisterListeners();
	};
}