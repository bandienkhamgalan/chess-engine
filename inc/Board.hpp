#pragma once
#include <array>
#include <map>
#include <vector>
#include <memory>
#include "IObservableBoard.hpp"
#include "IObservableBoardObservor.hpp"
#include "ISquareFactory.hpp"
#include "ISquare.hpp"
#include "IPiece.hpp"
#include "Location.hpp"

namespace Chess
{
	class Board
		: public IObservableBoard
	{
	public:
		/* IBoard methods */
		Board() = delete;
		Board(ISquareFactory& squareFactory);
		bool HasPieceAtLocation(const Location& location) const override;
		const IPiece& GetPieceAtLocation(const Location& location) const override;
		void AddPieceAtLocation(std::shared_ptr<IPiece> piece, const Location& location) override;
		void MovePieceToLocation(std::shared_ptr<IPiece> piece, const Location& location) override;
		
		/* IObservableBoard methods */
		void AddListener(IObservableBoardObservor &observor) override;
		void AddListenerForSquare(IObservableBoardObservor &observor, const Location& location) override;
		void RemoveListener(IObservableBoardObservor &observor) override;
		void RemoveListenerForSquare(IObservableBoardObservor &observor, const Location& location) override;
	private:
		std::array<std::shared_ptr<ISquare>, 64> squares;
		std::map<Location, std::vector<IObservableBoardObservor*>> squareListeners;

		std::shared_ptr<ISquare> GetSquareAtLocation(const Location& location) const;
		ISquare& UseSquareAtLocation(const Location& location) const;

		/* IObservableBoard helper methods */
		void NotifyListenersForSquare(const Location& location);
		std::vector<IObservableBoardObservor*>& GetListenerListForSquare(const Location& location);
	};
}