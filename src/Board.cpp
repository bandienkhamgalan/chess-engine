#include "Board.h"
#include <stdexcept>

using namespace std;
using namespace Chess;

/* Private Methods */

ISquare& Board::operator[](const Location& location) const
{
	return *(squares[(int)location - (int)algebraicLocation::a1]);
}

/* Public Methods */

Board::Board(ISquareFactory& squareFactory)
{
	int currentSquareIndex = 0;
	int currentLocationIndex = (int) algebraicLocation::a1;
	while ( currentSquareIndex < 64 )
	{
		Location currentLocation { (algebraicLocation)currentLocationIndex };
		squares[currentSquareIndex] = std::move(squareFactory.makeSquare(currentLocation));
		++currentSquareIndex;
		++currentLocationIndex;
	}
}

Board::Board(ISquareFactory& squareFactory, const vector<shared_ptr<Piece>>& pieces) : Board(squareFactory)
{
	AddPieces(pieces);
}


bool Board::HasPieceAtLocation(const Location& location) const
{
	return (*this)[location].HasPiece();
}

Piece& Board::GetPieceAtLocation(const Location& location) const
{
	return (*this)[location].GetPiece();
}

void Board::AddPieces(const vector<shared_ptr<Piece>>& pieces)
{
	this->pieces.reserve(pieces.size());
	for (auto iter = pieces.cbegin(); iter != pieces.cend(); iter++)
		AddPiece(*iter);
}

void Board::AddPiece(shared_ptr<Piece> piece)
{
	if (!piece)
		throw invalid_argument("Board::AddPiece : piece is null");

	Location pieceLocation = piece->GetLocation();
	if (this->HasPieceAtLocation(pieceLocation))
		throw invalid_argument("Board::AddPiece : square already occupied");

	(*this)[pieceLocation].AssignPiece(piece);
	pieces.emplace_back(piece);
}