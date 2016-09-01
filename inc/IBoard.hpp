#pragma once
#include <memory>
#include "Location.hpp"
#include "IPiece.hpp"

namespace Chess
{
	class IBoard
	{
	public:
		virtual bool HasPieceAtLocation(const Location& location) const = 0;
		virtual IPiece& GetPieceAtLocation(const Location& location) const = 0;
		virtual void AddPieceAtLocation(std::shared_ptr<IPiece> piece, const Location& location) = 0;
		virtual ~IBoard() {};
	};
}