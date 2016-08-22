#include "SimpleSquareFactory.hpp"
#include "SimpleSquare.hpp"

namespace Chess
{
	using namespace std;

	std::unique_ptr<ISquare> SimpleSquareFactory::makeSquare(const Location& location)
	{
		return std::unique_ptr<ISquare> { new SimpleSquare(location) };
	}
}