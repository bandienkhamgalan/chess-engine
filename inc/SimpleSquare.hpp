#pragma once

#include "ISquare.hpp"
#include <memory>

namespace Chess
{
	class SimpleSquare :
		public ISquare
	{
	public:
		SimpleSquare() = delete;
		SimpleSquare(const Location &location);
		const Location& GetLocation() const override;
		IPiece& GetPiece() const override;
		bool HasPiece() const override;
		void AssignPiece(std::shared_ptr<IPiece> toAssign) override;
	private:
		const Location location;
		std::shared_ptr<IPiece> piece;
	};
}