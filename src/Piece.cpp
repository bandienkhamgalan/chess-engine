#include <stdexcept>
#include "Piece.h"

namespace Chess
{
	using namespace std;

	/* Constructors */

	Piece::Piece(const Piece::Type& _type)
		: type { _type }
	{
		if( static_cast<int>(type) <= UNDEFINED || static_cast<int>(type) >= MAX )
			throw out_of_range("Piece::Piece : invalid piece type given");
	}

	Piece::Piece(const Piece::Type& _type, const Location& _location)
		: Piece(_type)
	{
		location = make_shared<Location>(_location);
	}

	/* Public methods */

	const Location& Piece::GetLocation() const
	{
		if (!IsInPlay())
			throw runtime_error("Piece::GetLocation : location was null");
		return *location;
	}

	bool Piece::IsInPlay() const
	{
		return (bool)location;
	}

	void Piece::SetLocation(shared_ptr<Location> newLocation)
	{
		if (IsInPlay() && !newLocation)
			throw runtime_error("Piece::SetLocation : piece still in play, so newLocation cannot be null, call RemoveFromPlay()");
		else if(newLocation)
			location = newLocation;
	}

	void Piece::RemoveFromPlay()
	{
		location = nullptr;
	}
	
	const Piece::Type& Piece::GetType() const
	{
		return type;
	}

	Piece::operator string() const
	{
		string toReturn = PieceTypeToString(type);
		if(IsInPlay())
			toReturn += " at " + static_cast<string>(*location);
		return toReturn;
	}

	/* Non-member functions */
	ostream& operator<<(std::ostream& output, const Piece& piece)
	{
		output << static_cast<string>(piece);
		return output;
	}

	string PieceTypeToString(const Piece::Type& type)
	{
		switch(type)
		{
			case Piece::Pawn:
				return "Pawn";
			case Piece::Knight:
				return "Knight";
			case Piece::Bishop:
				return "Bishop";
			case Piece::Rook:
				return "Rook";
			case Piece::Queen:
				return "Queen";
			case Piece::King:
				return "King";
			default:
				throw invalid_argument("PieceTypeToString : unrecognized PieceType");
		}
	}
}
