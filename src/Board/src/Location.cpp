#include "Location.hpp"
#include "Helpers.hpp"
#include <stdexcept>

namespace Chess
{
	using namespace std;

	/* Constructors */

	Location::Location(const AlgebraicLocation& location) : location { location }
	{
		if(location <= UNDEFINED || location >= MAX)
			throw out_of_range("Location::Location(AlgebraicLocation): location param out of range");
	}

	Location::Location(const string& location)
		: Location(Location::fromString(location))
	{

	}

	Location::Location(const File& file, const int8_t rank)
		: Location(Location::fromFileAndRank(file, rank))
	{

	}

	Location::Location(const int8_t file, const int8_t rank)
		: Location(Location::fromFileAndRank(file, rank))
	{

	}

	/* Private */

	Location::AlgebraicLocation Location::fromString(const string& toConvert)
	{
		string processed = Helpers::lower(Helpers::trimmed(toConvert));
		if(processed.length() != 2)
			throw invalid_argument("Location::fromString(string) excepts string of length 2");
		
		int8_t file = processed[0] - 'a' + 1;
		int8_t rank = processed[1] - '1' + 1;

		return fromFileAndRank(static_cast<Location::File>(file), rank);
	}

	Location::AlgebraicLocation Location::fromFileAndRank(const int8_t file, const int8_t rank)
	{
		if(file < a || file > h)
			throw out_of_range("Location::fromFileAndRank() : file param out of range");
		if(rank < 1 || file > 8)
			throw out_of_range("Location::fromFileAndRank() : rank param out of range");

		return static_cast<Location::AlgebraicLocation>(8 * (8 - rank) + file);
	}

	/* Public */

	Location::operator std::string() const
	{
		char file = 'A' + (location - 1) % 8;
		char rank = '8' - (location - 1) / 8;
		return { file, rank };
	}

	Location::operator int() const
	{
		return location;
	}

	bool Location::operator <(const Location& toCompare) const
	{
		return location < static_cast<int>(toCompare);
	}

	bool Location::operator ==(const Location& toCompare) const
	{
		return location == static_cast<int>(toCompare);
	}

	bool Location::operator ==(const AlgebraicLocation& toCompare) const
	{
		return location == static_cast<int>(toCompare);
	} 

	bool Location::operator !=(const Location& toCompare) const
	{
		return location != static_cast<int>(toCompare);
	}

	bool Location::operator !=(const AlgebraicLocation& toCompare) const
	{
		return location != static_cast<int>(toCompare);
	} 

	Location::File Location::GetFile() const
	{
		return static_cast<Location::File>(1 + (location - 1) % 8);
	}

	int8_t Location::GetRank() const
	{
		return 8 - (location - 1) / 8;
	}

	/* Non members */

	ostream& operator<<(ostream& output, const Location& location)
	{
		output << static_cast<string>(location);
		return output;
	}
}