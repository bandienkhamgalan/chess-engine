#include "SimpleSquare.hpp"
#include <stdexcept>

using namespace std;

namespace Chess
{
	SimpleSquare::SimpleSquare(const Location &location)
		: location { location }
	{
		
	}


	IPiece& SimpleSquare::GetPiece() const
	{
		if(!HasPiece())
			throw runtime_error("SimpleSquare::GetPiece() : piece is null");

		return (*piece);
	}

	const Location& SimpleSquare::GetLocation() const
	{
		return location;
	}

	bool SimpleSquare::HasPiece() const
	{
		return (bool) piece;
	}

	void SimpleSquare::RemovePiece()
	{
		piece = nullptr;
	}

	void SimpleSquare::AssignPiece(std::shared_ptr<IPiece> toAssign)
	{
		if(!toAssign)
			throw invalid_argument("SimpleSquare::AssignPiece() : piece cannot be null, call RemovePiece() instead");

		piece = toAssign;
	}
}