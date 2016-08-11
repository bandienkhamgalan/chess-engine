#include "Board.h"
#include <stdexcept>

using namespace std;
using namespace Chess;

Board::Board(const vector<shared_ptr<Piece>>& pieces) : Board()
{
	AddPieces(pieces);
}

/* Private Methods */

Square& Board::operator[](const Location& location) const
{
	return *(squares[(int)location]);
}

/* Public Methods */

Board::Board()
{
	for (auto current = (int) algebraicLocation::a1; current < (int) algebraicLocation::MAX; current++)
		squares.emplace_back(new Square(Location((algebraicLocation) current)));
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
};