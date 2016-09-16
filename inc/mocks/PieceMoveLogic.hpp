#pragma once
#include <vector>
#include "IPiece.hpp"
#include "IPieceMoveLogic.hpp"

namespace Chess
{
namespace Mocks
{
	class PieceMoveLogic
		: public IPieceMoveLogic
	{
	public:
		PieceMoveLogic();
		~PieceMoveLogic();

		int *GetValidMovesCalls;
		std::vector<Location> GetValidMovesReturnValue;
		const std::vector<Location>& GetValidMoves() override;

		int *SetPieceCalls;
		std::vector<std::shared_ptr<IPiece>> SetPieceParams;
		void SetPiece(std::shared_ptr<IPiece> _piece) override;
	};
}
}