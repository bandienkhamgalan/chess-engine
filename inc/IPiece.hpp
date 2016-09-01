#pragma once

#include <stdexcept>
#include <memory>

namespace Chess
{
	class IPlayer;
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

		virtual const IPlayer& GetPlayer() = 0;
		virtual const Type& GetType() = 0;
		virtual const Location& GetLocation() = 0;
		virtual bool IsInPlay() = 0;
		
		virtual void RemoveFromPlay() = 0;
		virtual void SetLocation(std::shared_ptr<ISquare> newSquare) = 0;

		virtual ~IPiece() {};
	};
}