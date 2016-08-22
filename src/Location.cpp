#include "Location.hpp"
#include "Helpers.hpp"
#include <stdexcept>

namespace Chess
{
	using namespace std;

	/* Constructors */

	Location::Location(const algebraicLocation& location) : location { location }
	{
		int locationInt = static_cast<int>(location);
		if (locationInt <= UNDEFINED || locationInt >= MAX)
			throw out_of_range("Location::Location(algebraicLocation): location param out of range");
	}

	Location::Location(const string& location) : Location(Location::fromString(location)) { }

	/* Private */

	Location::algebraicLocation Location::fromString(const string& toConvert)
	{
		string processed = Helpers::lower(Helpers::trimmed(toConvert));
		if (processed.length() != 2)
			throw invalid_argument("Location::fromString(string) excepts string of length 2");
		
		int column = processed[0] - 'a';
		int row = processed[1] - '1';
		int index = (int) a1 + column + 8 * row;

		if (index <= UNDEFINED || index >= MAX)
			throw invalid_argument("Location::fromString(string) excepts chess board location in algebraic notation");
		return static_cast<algebraicLocation>(index);
	}

	/* Public */

	Location::operator std::string() const
	{
		int locationInt = static_cast<int>(location);
		char column = 'A' + (locationInt - 1) % 8;
		char row = '1' + (locationInt - 1) / 8;
		return { column, row };
	}

	Location::operator int() const
	{
		return static_cast<int>(location);
	}

	bool Location::operator <(const Location& toCompare) const
	{
		return static_cast<int>(location) < static_cast<int>(toCompare);
	}

	bool Location::operator ==(const Location& toCompare) const
	{
		return static_cast<int>(location) == static_cast<int>(toCompare);
	}

	bool Location::operator ==(const algebraicLocation& toCompare) const
	{
		return static_cast<int>(location) == static_cast<int>(toCompare);
	} 

	bool Location::operator !=(const Location& toCompare) const
	{
		return static_cast<int>(location) != static_cast<int>(toCompare);
	}

	bool Location::operator !=(const algebraicLocation& toCompare) const
	{
		return static_cast<int>(location) != static_cast<int>(toCompare);
	} 

	/* Non members */

	ostream& operator<<(ostream& output, const Location& location)
	{
		output << static_cast<string>(location);
		return output;
	}
}