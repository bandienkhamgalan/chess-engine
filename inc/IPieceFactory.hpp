#pragma once
#include <memory>
#include "IPiece.hpp"
#include "IPlayer.hpp"

namespace Chess
{
	class IObservableBoard;
	class Location;
	class IPieceFactory
	{
	public:
		virtual ~IPieceFactory() {};
		virtual std::unique_ptr<IPiece> makePiece(std::weak_ptr<IObservableBoard> board, const IPlayer& player, const IPiece::Type& type) = 0;
	};
}