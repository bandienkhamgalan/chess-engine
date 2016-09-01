#include <stdexcept>
#include "Piece.hpp"

namespace Chess
{
	using namespace std;

	/* Constructors */

	Piece::Piece(const IPlayer& _player, const Piece::Type& _type)
		: player(_player), type { _type }
	{
		if( static_cast<int>(type) <= UNDEFINED || static_cast<int>(type) >= MAX )
			throw out_of_range("Piece::Piece : invalid piece type given");
	}

	/* Public methods */

	const Location& Piece::GetLocation()
	{
		if (!IsInPlay())
			throw runtime_error("Piece::GetLocation : location was null");
		return square.lock()->GetLocation();
	}

	bool Piece::IsInPlay()
	{
		return !square.expired();
	}

	void Piece::SetLocation(shared_ptr<ISquare> newSquare)
	{
		if (IsInPlay() && !newSquare)
			throw runtime_error("Piece::SetLocation : piece still in play, so newSquare cannot be null, call RemoveFromPlay()");
		else if(newSquare)
			square = newSquare;
	}

	void Piece::RemoveFromPlay()
	{
		square.reset();
	}
	
	const Piece::Type& Piece::GetType()
	{
		return type;
	}

	Piece::operator string() const
	{
		string toReturn = PieceTypeToString(type);
		if (!square.expired())
			toReturn +=  " at " + static_cast<string>(square.lock()->GetLocation());
		return toReturn;
	}

	const IPlayer& Piece::GetPlayer()
	{
		return player;
	}

	/* Non-member functions */
	ostream& operator<<(std::ostream& output, const Piece& piece)
	{
		output << static_cast<string>(piece);
		return output;
	}

	string PieceTypeToString(const IPiece::Type& type)
	{
		switch(type)
		{
			case IPiece::Pawn:
				return "Pawn";
			case IPiece::Knight:
				return "Knight";
			case IPiece::Bishop:
				return "Bishop";
			case IPiece::Rook:
				return "Rook";
			case IPiece::Queen:
				return "Queen";
			case IPiece::King:
				return "King";
			default:
				throw invalid_argument("PieceTypeToString : unrecognized PieceType");
		}
	};
}
