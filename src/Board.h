#pragma once

#include <vector>
#include <memory>
#include "ISquareFactory.h"
#include "ISquare.h"
#include "Location.h"
#include "Piece.h"

namespace Chess
{
	class Board
	{
	private:
		std::array<std::unique_ptr<ISquare>, 64> squares;
		ISquare& operator[](const Location& location) const;

	public:
		bool HasPieceAtLocation(const Location& location) const;
		Piece& GetPieceAtLocation(const Location& location) const;
		Board() = delete;
		Board(ISquareFactory& squareFactory);
		Board(ISquareFactory& squareFactory, const std::vector<std::shared_ptr<Piece>>& pieces);
		void AddPieces(const std::vector<std::shared_ptr<Piece>>& pieces);
		void AddPiece(std::shared_ptr<Piece> piece);
	};
}