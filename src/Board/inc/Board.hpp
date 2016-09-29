#pragma once
#include <tuple>
#include <array>
#include <map>
#include <vector>
#include <memory>
#include "IObservableBoard.hpp"
#include "IObservableSquare.hpp"
#include "IObservableSquareFactory.hpp"
#include "IObservableSquareObservor.hpp"
#include "IPiece.hpp"
#include "Location.hpp"

namespace Chess
{
	class Board
		: public IObservableBoard, public IObservableSquareObservor
	{
	public:
		/* IBoard methods */
		Board() = delete;
		Board(IObservableSquareFactory& squareFactory);
		bool HasPieceAtLocation(const Location& location) const override;
		const IPiece& GetPieceAtLocation(const Location& location) const override;
		void AddPieceAtLocation(std::shared_ptr<IPiece> piece, const Location& location) override;
		void MovePieceToLocation(std::shared_ptr<IPiece> piece, const Location& location) override;
		
		/* IObservableBoard methods */
		void AddListener(IObservableBoardObservor* observor, const IObservableSquare::Event& event) override;
		void AddListenerForSquare(IObservableBoardObservor* observor, const Location& location, const IObservableSquare::Event& event) override;
		void RemoveListener(IObservableBoardObservor* observor, const IObservableSquare::Event& event) override;
		void RemoveListenerForSquare(IObservableBoardObservor* observor, const Location& location, const IObservableSquare::Event& event) override;

		/* IObservableSquareObservor methods */
		void SquareDidChange(const Location& location, const IObservableSquare::Event& event) override;
	private:
		std::array<std::shared_ptr<IObservableSquare>, 64> squares;
		std::map<Location, std::vector<std::tuple<IObservableBoardObservor*, IObservableSquare::Event>>> squareObservors;

		std::shared_ptr<IObservableSquare> GetSquareAtLocation(const Location& location) const;
		IObservableSquare& UseSquareAtLocation(const Location& location) const;
	};
}