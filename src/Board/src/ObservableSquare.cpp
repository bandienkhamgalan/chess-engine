#include "ObservableSquare.hpp"
#include <stdexcept>

using namespace std;

namespace Chess
{
	ObservableSquare::ObservableSquare(const Location &location)
		: location { location }
	{
		
	}

	/* ISquare methods */
	IPiece& ObservableSquare::GetPiece() const
	{
		if(!HasPiece())
			throw runtime_error("ObservableSquare::GetPiece() : piece is null");

		return (*piece);
	}

	const Location& ObservableSquare::GetLocation() const
	{
		return location;
	}

	bool ObservableSquare::HasPiece() const
	{
		return (bool) piece;
	}

	void ObservableSquare::RemovePiece()
	{
		piece = nullptr;
		NotifyListeners(OccupantChanged);
	}

	void ObservableSquare::AssignPiece(std::shared_ptr<IPiece> toAssign)
	{
		if(!toAssign)
			throw invalid_argument("ObservableSquare::AssignPiece() : piece cannot be null, call RemovePiece() instead");

		piece = toAssign;
		NotifyListeners(OccupantChanged);
	}

	/* IObservableSquare methods */
	void ObservableSquare::AddListener(IObservableSquareObservor* observor, const IObservableSquare::Event& event)
	{
		for(IObservableSquareObservor* existingObservor : listeners)
			if(existingObservor == observor)
				return;
		
		listeners.push_back(observor);
	}

	void ObservableSquare::RemoveListener(IObservableSquareObservor* observor, const IObservableSquare::Event& event)
	{
		auto itr = find(listeners.begin(), listeners.end(), observor);
		if(itr != listeners.end())
			listeners.erase(itr);
	}

	/* Private methods */

	void ObservableSquare::NotifyListeners(const IObservableSquare::Event& event)
	{
		for(IObservableSquareObservor* existingObservor : listeners)
			existingObservor->SquareDidChange(location, event);
	}
}