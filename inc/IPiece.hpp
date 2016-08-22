#pragma once

#include <stdexcept>
#include <memory>

namespace Chess
{
	class Player;
	class Type;
	class Location;
	class ISquare;
	class IPiece
	{
	public:
		enum Type : uint8_t
		{
			UNDEFINED = 0,
			Pawn,
			Knight,
			Bishop,
			Rook,
			Queen,
			King,
			MAX
		};

		virtual const Player& GetPlayer() const = 0;
		virtual const Type& GetType() const = 0;
		virtual const Location& GetLocation() const = 0;
		virtual bool IsInPlay() const = 0;
		
		virtual void RemoveFromPlay() = 0;
		virtual void SetLocation(std::shared_ptr<ISquare> newSquare) = 0;

		virtual ~IPiece() {};
	};
}