#include <stdexcept>
#include "Piece.h"

using namespace Chess;
using namespace std;

const Location& Piece::GetLocation() const
{
	if (!IsInPlay())
		throw runtime_error("Piece::GetLocation : location was null");
	return *location;
}

bool Piece::IsInPlay() const
{
	return inPlay;
}

void Piece::SetLocation(std::shared_ptr<Location> newLocation)
{
	if (location)
	{
		inPlay = true;
		location = newLocation;
	}
}

void Piece::RemoveFromPlay()
{
	location = nullptr;
	inPlay = false;
}