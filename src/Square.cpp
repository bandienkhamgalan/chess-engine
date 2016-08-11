#include "Square.h"
#include <stdexcept>

using namespace std;

namespace Chess
{
	Square::Square(const Location &location, shared_ptr<Piece> piece /*= nullptr*/)
		: location { location }
	{
		if (piece)
			AssignPiece(piece);
	}


	Piece& Square::GetPiece() const
	{
		if (!HasPiece())
			throw runtime_error("Square::GetPiece() : piece is null");

		return (*piece);
	}

	bool Square::HasPiece() const
	{
		return (bool) piece;
	}

	void Square::AssignPiece(std::shared_ptr<Piece> toAssign)
	{
		piece = toAssign;
	}
}