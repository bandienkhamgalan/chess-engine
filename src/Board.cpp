#include "Board.hpp"
#include <stdexcept>
#include <string>

namespace Chess
{
	using namespace std;

	/* Private Methods */

	shared_ptr<ISquare> Board::GetSquareAtLocation(const Location& location) const
	{
		return squares[static_cast<int>(location) - static_cast<int>(Location::a8)];
	}

	ISquare& Board::UseSquareAtLocation(const Location& location) const
	{
		return *(GetSquareAtLocation(location));
	}

	/* Public Methods */

	Board::Board(ISquareFactory& squareFactory)
	{
		int currentSquareIndex = 0;
		Location::for_each( [&](Location currentLocation)
			{
				squares[currentSquareIndex++] = std::move(squareFactory.makeSquare(currentLocation));
			});
	}

	bool Board::HasPieceAtLocation(const Location& location) const
	{
		return UseSquareAtLocation(location).HasPiece();
	}

	IPiece& Board::GetPieceAtLocation(const Location& location) const
	{
		return UseSquareAtLocation(location).GetPiece();
	}

	void Board::AddPieceAtLocation(shared_ptr<IPiece> piece, const Location& location)
	{
		if (!piece)
			throw invalid_argument("Board::AddPiece : piece is null");

		if (this->HasPieceAtLocation(location))
			throw invalid_argument("Board::AddPiece : square already occupied");

		auto square = GetSquareAtLocation(location);
		square->AssignPiece(piece);
		piece->SetLocation(square);
	}
}