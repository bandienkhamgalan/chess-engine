#pragma once
#include <memory>
#include "IPiece.hpp"
#include "IPlayer.hpp"
#include "IPieceFactory.hpp"

namespace Chess
{
	class Location;
	class PieceFactory
		: public IPieceFactory
	{
	public:
		std::unique_ptr<IPiece> makePiece(std::weak_ptr<IObservableBoard> board, const IPlayer& player, const IPiece::Type& type) override;
	};
}