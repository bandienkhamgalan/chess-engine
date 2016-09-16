#pragma once
#include <array>
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
		bool HasPieceAtLocation(const Location& location) const override;
		IPiece& GetPieceAtLocation(const Location& location) const override;
		Board() = delete;
		Board(ISquareFactory& squareFactory);
		void AddPieceAtLocation(std::shared_ptr<IPiece> piece, const Location& location) override;
		void MovePieceToLocation(std::shared_ptr<IPiece> piece, const Location& location) override;
		
		/* IObservableBoard methods */
		void AddListener(IObservableBoardObservor &observor) override;
		void AddListenerForSquare(IObservableBoardObservor &observor, const Location& location) override;
		void RemoveListener(IObservableBoardObservor &observor) override;
		void RemoveListenerForSquare(IObservableBoardObservor &observor, const Location& location) override;
	private:
		std::shared_ptr<ISquare> GetSquareAtLocation(const Location& location) const;
		ISquare& UseSquareAtLocation(const Location& location) const;

		void NotifyListenersForSquare(const Location& location);
		std::vector<std::weak_ptr<IObservableBoardObservor>>& GetListenerListForSquare(const Location& location);

		std::array<std::shared_ptr<ISquare>, 64> squares;
		std::array<std::vector<std::weak_ptr<IObservableBoardObservor>>, 64> squareListeners;
	};
}