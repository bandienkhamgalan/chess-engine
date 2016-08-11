#pragma once

#include <vector>
#include <memory>
#include "Square.h"
#include "Location.h"
#include "Piece.h"

namespace Chess
{
	class Board
	{
	private:
		std::vector<std::shared_ptr<Piece>> pieces;
		std::vector<std::shared_ptr<Square>> squares;
		Square& operator[](const Location& location) const;

	public:
		bool HasPieceAtLocation(const Location& location) const;
		Piece& GetPieceAtLocation(const Location& location) const;
		Board();
		Board(const std::vector<std::shared_ptr<Piece>>& pieces);
		void AddPieces(const std::vector<std::shared_ptr<Piece>>& pieces);
		void AddPiece(std::shared_ptr<Piece> piece);
	};
}