#pragma once
#include "gmock/gmock.h"
#include "IPieceFactory.hpp"
#include "IObservableBoard.hpp"

namespace Chess
{
	class IObservableBoard;
	class Location;
	class IPlayer;
namespace Mocks
{
	class PieceFactory
		: public IPieceFactory
	{
	public:
		MOCK_METHOD3(makePiece, std::unique_ptr<IPiece>(std::weak_ptr<IObservableBoard>, const IPlayer&, const IPiece::Type&));
	};
}
}