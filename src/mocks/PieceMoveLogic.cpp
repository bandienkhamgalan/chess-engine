#include "mocks/PieceMoveLogic.hpp"

namespace Chess
{
namespace Mocks
{
	PieceMoveLogic::PieceMoveLogic()
	{
		GetValidMovesCalls = new int(0);
		SetPieceCalls = new int(0);
	}
	
	PieceMoveLogic::~PieceMoveLogic()
	{
		delete GetValidMovesCalls;
		delete SetPieceCalls;
	}

	const std::vector<Location>& PieceMoveLogic::GetValidMoves()
	{
		++(*GetValidMovesCalls);
		return GetValidMovesReturnValue;
	}

	void PieceMoveLogic::SetPiece(std::shared_ptr<IPiece> _piece)
	{
		++(*SetPieceCalls);
		SetPieceParams.push_back(_piece);
	}
}
}