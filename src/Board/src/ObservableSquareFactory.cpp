#include "ObservableSquareFactory.hpp"
#include "ObservableSquare.hpp"

namespace Chess
{
	using namespace std;

	std::unique_ptr<IObservableSquare> ObservableSquareFactory::makeSquare(const Location& location)
	{
		return make_unique<ObservableSquare>(location);
	}
}