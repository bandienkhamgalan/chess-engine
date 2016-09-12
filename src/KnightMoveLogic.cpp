#include "KnightMoveLogic.hpp"

namespace Chess
{
	using namespace std;

	/* Constructors */
	KnightMoveLogic::KnightMoveLogic(const IObservableBoard& board, const IPiece& piece)
		: board(board), piece(piece)
	{
		// RecomputeValidMoves();
		// RegisterListeners();
	}

	const std::vector<Location>& GetValidMoves() const
	{
		RecomputeValidMoves();
		return validMoves;
	}

	/* IObservableBoardObservor methods */

	void KnightMoveLogic::SquareDidChange(IObservableBoard& board, const Location& location)
	{
		UnregisterListeners();
		RecomputeValidMoves();
		RegisterListeners();
	}

	/* Private methods */

	void KnightMoveLogic::RecomputeValidMoves()
	{
		vector<Location> newValidMoves;
		uint8_t rank = piece.GetLocation().GetRank();
		uint8_t file = piece.GetLocation().GetFile();
		for(uint8_t fileAdder = -1  ; fileAdder <= 1 ; fileAdder += 2)
			for(uint8_t rankAdder = -2 ; rankAdder <= 2 ; rankAdder += 4)
				if(rank >= 1 && rank <= 8 && file >= 1 && file <= 8)
					newValidMoves.emplace_back(file, rank);
		validMoves.swap(newValidMoves);
	}
	
	void KnightMoveLogic::RegisterListeners()
	{
		for(Location location : validMoves)
			board.AddListenerForSquare(*this, location);
	}

	void KnightMoveLogic::UnregisterListeners()
	{
		board.RemoveListener(*this);
	}
}