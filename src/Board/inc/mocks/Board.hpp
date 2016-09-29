#pragma once
#include <vector>
#include <tuple>
#include <map>
#include "gmock/gmock.h"
#include "IObservableBoard.hpp"
#include "IObservableSquare.hpp"
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
		std::vector<Location>* HasPieceAtLocationParams;
		std::vector<Location>* GetPieceAtLocationParams;
		std::vector<std::tuple<std::shared_ptr<IPiece>, Location>>* AddPieceAtLocationParams;
		std::map<Location, bool> HasPieceAtLocationReturnValue;
		std::unique_ptr<IPiece> GetPieceAtLocationReturnValue;
		
		/* IBoard methods */
		MOCK_CONST_METHOD1(HasPieceAtLocation, bool(const Location&));
		MOCK_CONST_METHOD1(GetPieceAtLocation, const IPiece&(const Location&));
		MOCK_METHOD2(AddPieceAtLocation, void(std::shared_ptr<IPiece>, const Location&));
		MOCK_METHOD2(MovePieceToLocation, void(std::shared_ptr<IPiece>, const Location&));
		
		/* IObservableBoard methods */
		MOCK_METHOD2(AddListener, void(IObservableBoardObservor*, const IObservableSquare::Event&));
		MOCK_METHOD3(AddListenerForSquare, void(IObservableBoardObservor*, const Location&, const IObservableSquare::Event&));
		MOCK_METHOD2(RemoveListener, void(IObservableBoardObservor*, const IObservableSquare::Event&));
		MOCK_METHOD3(RemoveListenerForSquare, void(IObservableBoardObservor*, const Location&, const IObservableSquare::Event&));
	};
}
}