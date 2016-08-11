#pragma once

#include "Location.h"
#include "Piece.h"
#include <memory>

namespace Chess
{
	class Square
	{
	private:
		const Location location;
		std::shared_ptr<Piece> piece;
	public:
		Square() = delete;
		Square(const Location &location, std::shared_ptr<Piece> piece = nullptr);
		Piece& GetPiece() const;
		bool HasPiece() const;
		void AssignPiece(std::shared_ptr<Piece> toAssign);
	};
}