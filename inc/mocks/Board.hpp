#pragma once
#include <vector>
#include <tuple>
#include "IObservableBoard.hpp"
#include "IPlayer.hpp"
#include "IPiece.hpp"
#include "Location.hpp"

namespace Chess
{
namespace Mocks
{
	class Board
		: public IObservableBoard
	{
	public:
		Board();
		~Board();
		std::vector<Location>* HasPieceAtLocationParams;
		std::vector<Location>* GetPieceAtLocationParams;
		std::vector<std::tuple<std::shared_ptr<IPiece>, Location>>* AddPieceAtLocationParams;
		bool HasPieceAtLocationReturnValue = true;
		std::unique_ptr<IPiece> GetPieceAtLocationReturnValue;
		
		/* IBoard methods */
		bool HasPieceAtLocation(const Location& location) const override;
		IPiece& GetPieceAtLocation(const Location& location) const override;
		int AddPieceAtLocationCalls(const IPlayer::Color& color, const IPiece::Type& type, const Location& locationComp);
		void AddPieceAtLocation(std::shared_ptr<IPiece> piece, const Location& location) override;
		void MovePieceToLocation(std::shared_ptr<IPiece> piece, const Location& location) override;
		
		/* IObservableBoard methods */
		void AddListener(IObservableBoardObservor &observor) override;
		void AddListenerForSquare(IObservableBoardObservor &observor, const Location& location) override;
		void RemoveListener(IObservableBoardObservor &observor) override;
		void RemoveListenerForSquare(IObservableBoardObservor &observor, const Location& location) override;
	};
}
}