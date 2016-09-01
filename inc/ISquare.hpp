#pragma once

#include <memory>

namespace Chess
{
	class IPiece;
	class Location;
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