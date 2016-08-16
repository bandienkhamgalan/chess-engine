#include <stdexcept>
#include "Piece.h"

using namespace std;

namespace Chess
{
	/* Constructors */

	Piece::Piece(const Location& location)
	{
		this->location = make_shared<Location>(location);
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

	void Piece::SetLocation(std::shared_ptr<Location> newLocation)
	{
		if (location)
		{
			location = newLocation;
		}
	}

	void Piece::RemoveFromPlay()
	{
		location = nullptr;
	}
}