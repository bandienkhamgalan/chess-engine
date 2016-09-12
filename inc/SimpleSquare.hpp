#pragma once
#include <memory>
#include "ISquare.hpp"
#include "Location.hpp"

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
		void RemovePiece() override;
		void AssignPiece(std::shared_ptr<IPiece> toAssign) override;
	private:
		const Location location;
		std::shared_ptr<IPiece> piece;
	};
}