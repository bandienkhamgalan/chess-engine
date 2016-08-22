#include "mocks/MockSquareFactory.hpp"
#include "SimpleSquare.hpp"

namespace Chess
{
	using namespace std;
	
	unique_ptr<ISquare> MockSquareFactory::makeSquare(const Location& location)
	{
		int toSet = 1;
		try {
			toSet += makeSquareCalls.at(location);
		} catch(const out_of_range&) { }
		makeSquareCalls[location] = toSet;
		
		return unique_ptr<ISquare> { new SimpleSquare(location) };
	};
}	