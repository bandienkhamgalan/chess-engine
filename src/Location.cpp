#include "Location.h"
#include "Helpers.h"
#include <stdexcept>

using namespace Chess;
using namespace std;

Location::Location(const algebraicLocation& location) : location { location }
{
	if (location <= UNDEFINED || location >= MAX)
		throw out_of_range("Location::Location(algebraicLocation): location param out of range");
}

Location::Location(const string& location) : Location(Location::fromString(location)) { }

algebraicLocation Location::fromString(const string& toConvert)
{
	string processed = Helpers::lower(Helpers::trimmed(toConvert));
	if (processed.length() != 2)
		throw invalid_argument("Location::fromString(string) excepts string of length 2");
	
	int column = processed[0] - 'a';
	int row = processed[1] - '1';
	int index = (int) a1 + column + 8 * row;

	if (index <= UNDEFINED || index >= MAX)
		throw invalid_argument("Location::fromString(string) excepts chess board location in algebraic notation");
	return (algebraicLocation)index;
}

string Location::toString() const
{
	char column = 'A' + (location - 1) % 8;
	char row = '1' + (location - 1) / 8;
	return { column, row };
}

ostream& operator<<(ostream& output, const Location& location)
{
	output << location.toString();
	return output;
}

Location::operator int() const
{
	return (int)location;
}