#pragma once

#include <array>
#include <memory>
#include "IBoard.hpp"
#include "ISquareFactory.hpp"
#include "ISquare.hpp"
#include "IPiece.hpp"
#include "Location.hpp"

namespace Chess
{
	class Board
		: public IBoard
	{
	public:
		bool HasPieceAtLocation(const Location& location) const override;
		IPiece& GetPieceAtLocation(const Location& location) const override;
		Board() = delete;
		Board(ISquareFactory& squareFactory);
		void AddPieceAtLocation(std::shared_ptr<IPiece> piece, const Location& location) override;
		
	private:
		std::shared_ptr<ISquare> GetSquareAtLocation(const Location& location) const;
		ISquare& UseSquareAtLocation(const Location& location) const;

		std::array<std::shared_ptr<ISquare>, 64> squares;
	};
}