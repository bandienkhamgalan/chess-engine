#include "KnightMoveLogic.hpp"
#include <stdexcept>

namespace Chess
{
	using namespace std;

	KnightMoveLogic::KnightMoveLogic(shared_ptr<IObservableBoard> _board, shared_ptr<IPiece> _piece)
		: board(_board)
	{
		if(_piece)
			SetPiece(_piece);

		// RecomputeValidMoves();
		// RegisterListeners();
	}

	KnightMoveLogic::~KnightMoveLogic()
	{
		if(!board.expired())
			board.lock()->RemoveListener(*this);
	}

	/* Public methods */

	void KnightMoveLogic::SetPiece(std::shared_ptr<IPiece> toSet)
	{
		if(!toSet)
			throw invalid_argument("Piece::SetPiece() : piece cannot be null");
		if(!piece.expired())
			throw runtime_error("Piece::SetPiece() : piece already set");

		piece = toSet;
	}

	const std::vector<Location>& KnightMoveLogic::GetValidMoves()
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
		if(piece.expired())
			throw runtime_error("KnightMoveLogic::RecomputeValidMoves() : piece has not been set or has expired");
		if(board.expired())
			throw runtime_error("KnightMoveLogic::RecomputeValidMoves() : board has not been set or has expired");
		
		auto piecePtr = piece.lock(); 
		if(piecePtr->IsInPlay())
		{
			auto rank = piecePtr->GetLocation().GetRank();
			auto file = piecePtr->GetLocation().GetFile();
			for(auto fileAdder = -1  ; fileAdder <= 1 ; fileAdder += 2)
			{
				for(auto rankAdder = -2 ; rankAdder <= 2 ; rankAdder += 4)
				{
					try 
					{
						Location potentialMove { static_cast<int8_t>(file + fileAdder), static_cast<int8_t>(rank + rankAdder) };
						if(!board.lock()->HasPieceAtLocation(potentialMove))
							newValidMoves.push_back(potentialMove);
					} catch(const out_of_range&) { }
				}
			}
		}
		validMoves = move(newValidMoves);
	}
	
	void KnightMoveLogic::RegisterListeners()
	{
		auto boardPtr = board.lock();
		for(Location location : validMoves)
			boardPtr->AddListenerForSquare(*this, location);
	}

	void KnightMoveLogic::UnregisterListeners()
	{
		board.lock()->RemoveListener(*this);
	}
}