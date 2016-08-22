#pragma once

#include "Location.hpp"
#include "IPiece.hpp"
#include <memory>

namespace Chess
{
	class ISquare
	{
	public:
		virtual IPiece& GetPiece() const = 0;
		virtual const Location& GetLocation() const = 0;
		virtual bool HasPiece() const = 0;
		virtual void AssignPiece(std::shared_ptr<IPiece> toAssign) = 0;
		virtual ~ISquare() {};
	};
}