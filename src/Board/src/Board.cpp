#include "Board.hpp"
#include "IObservableSquare.hpp"
#include <stdexcept>
#include <string>

namespace Chess
{
	using namespace std;

	/* IBoard methods */

	Board::Board(IObservableSquareFactory& squareFactory)
	{
		int currentSquareIndex = 0;
		Location::for_each( [&](Location currentLocation)
			{
				squares[currentSquareIndex++] = squareFactory.makeSquare(currentLocation);
			});
	}

	bool Board::HasPieceAtLocation(const Location& location) const
	{
		return UseSquareAtLocation(location).HasPiece();
	}

	const IPiece& Board::GetPieceAtLocation(const Location& location) const
	{
		return UseSquareAtLocation(location).GetPiece();
	}

	void Board::AddPieceAtLocation(shared_ptr<IPiece> piece, const Location& location)
	{
		if(!piece)
			throw invalid_argument("Board::AddPiece() : piece is null");

		if(piece->IsInPlay())
			throw invalid_argument("Board::AddPiece() : piece already in play cannot be added");

		if(HasPieceAtLocation(location))
			throw invalid_argument("Board::AddPiece() : square already occupied");

		auto square = GetSquareAtLocation(location);
		square->AssignPiece(piece);
		piece->SetLocation(square);
	}

	void Board::MovePieceToLocation(std::shared_ptr<IPiece> piece, const Location& location) 
	{
		if(!piece)
			throw invalid_argument("Board::MovePieceToLocation() : piece cannot be null");

		if(!piece->IsInPlay())
			throw runtime_error("Board::MovePieceToLocation() : piece is not in play cannot move");

		auto oldSquare = GetSquareAtLocation(piece->GetLocation());
		if(!oldSquare->HasPiece() || &oldSquare->GetPiece() != piece.get())
			throw invalid_argument("Board::MovePieceToLocation() : piece was not registered with this board");
		auto newSquare = GetSquareAtLocation(location);
		if(newSquare->HasPiece())
			throw invalid_argument("Board::MovePieceToLocation() : location is occupied");
		
		piece->SetLocation(newSquare);
		oldSquare->RemovePiece();
		newSquare->AssignPiece(piece);
	}

	/* IObservableSquareObservor methods */
	void Board::SquareDidChange(const Location& location, const IObservableSquare::Event& event)
	{

	}

	/* IObservableBoard methods */
	void Board::AddListener(IObservableBoardObservor* observor, const IObservableSquare::Event& event)
	{
		Location::for_each([&](const Location& location) {
			AddListenerForSquare(observor, location, event);
		});
	}

	void Board::AddListenerForSquare(IObservableBoardObservor* observor, const Location& location, const IObservableSquare::Event& event)
	{
		auto& observors = squareObservors[location];
		auto observorTuple = make_tuple(observor, event);
		for(auto& existingObservorTuple : observors)
			if(existingObservorTuple == observorTuple)
				return;

		observors.push_back(observorTuple);
	}
	
	void Board::RemoveListener(IObservableBoardObservor* observor, const IObservableSquare::Event& event)
	{
		Location::for_each([&](const Location& location) {
			RemoveListenerForSquare(observor, location, event);
		});
	}
	
	void Board::RemoveListenerForSquare(IObservableBoardObservor* observor, const Location& location, const IObservableSquare::Event& event)
	{
		auto& observors = squareObservors[location];
		auto observorTuple = make_tuple(observor, event);
		auto itr = find(observors.begin(), observors.end(), observorTuple);
		if(itr != observors.end())
			observors.erase(itr);
	}

	/* Private Methods */

	shared_ptr<IObservableSquare> Board::GetSquareAtLocation(const Location& location) const
	{
		return squares[static_cast<int>(location) - static_cast<int>(Location::a8)];
	}

	IObservableSquare& Board::UseSquareAtLocation(const Location& location) const
	{
		return *(GetSquareAtLocation(location));
	}
}