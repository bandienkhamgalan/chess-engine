#include "Board.hpp"
#include <stdexcept>
#include <string>

namespace Chess
{
	using namespace std;

	/* IBoard methods */

	Board::Board(ISquareFactory& squareFactory)
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

	IPiece& Board::GetPieceAtLocation(const Location& location) const
	{
		return UseSquareAtLocation(location).GetPiece();
	}

	void Board::AddPieceAtLocation(shared_ptr<IPiece> piece, const Location& location)
	{
		if(!piece)
			throw invalid_argument("Board::AddPiece : piece is null");

		if(HasPieceAtLocation(location))
			throw invalid_argument("Board::AddPiece : square already occupied");

		auto square = GetSquareAtLocation(location);
		square->AssignPiece(piece);
		piece->SetLocation(square);
		NotifyListenersForSquare(location);
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

		NotifyListenersForSquare(oldSquare->GetLocation());
		NotifyListenersForSquare(newSquare->GetLocation());
	}

	/* IObservableBoard methods */
	void Board::AddListener(IObservableBoardObservor &observor)
	{
		Location::for_each([&observor](const Location& location) {
			AddListenerForSquare(observor, location);
		});
	}

	void Board::AddListenerForSquare(IObservableBoardObservor &observor, const Location& location)
	{
		auto& listeners = GetListenerListForSquare(location);
		
		// Return early if listener is already registered
		for(auto& existingObservor : listeners)
			if(!existingObservor.expired() && existingObservor.lock() == &observor)
				return;

		listeners.emplace_back();
	}
	
	void Board::RemoveListener(IObservableBoardObservor &observor)
	{

	}
	
	void Board::RemoveListenerForSquare(IObservableBoardObservor &observor, const Location& location)
	{

	}


	/* Private Methods */

	shared_ptr<ISquare> Board::GetSquareAtLocation(const Location& location) const
	{
		return squares[static_cast<int>(location) - static_cast<int>(Location::a8)];
	}

	ISquare& Board::UseSquareAtLocation(const Location& location) const
	{
		return *(GetSquareAtLocation(location));
	}

	std::vector<std::weak_ptr<IObservableBoardObservor>>& Board::GetListenerListForSquare(const Location& location)
	{
		return GetListenersForSquare(location);
	}

	void Board::NotifyListenersForSquare(const Location& location)
	{
		for(auto& observor : GetListenerListForSquare(location))
			if(!observor.expired())
				observor.lock()->SquareDidChange(*this, location);
	}
}