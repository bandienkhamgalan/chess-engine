#include <memory>
#include "Piece.hpp"
#include "IPiece.hpp"
#include "PieceFactory.hpp"
#include "KnightMoveLogic.hpp"

namespace Chess
{
	using namespace std;

	unique_ptr<IPiece> PieceFactory::makePiece(weak_ptr<IObservableBoard> board, const IPlayer& player, const IPiece::Type& type)
	{
		#pragma message "all pieces currently use KnightMoveLogic"
		return make_unique<Piece>(player, type, make_shared<KnightMoveLogic>(board));
	}
}