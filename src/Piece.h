#pragma once

#include "Location.h"
#include <memory>

namespace Chess
{
	class Piece
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

		Piece() = delete;
		Piece(const Type& _type);
		Piece(const Type& _type, const Location& _location);
		const Location& GetLocation() const;
		bool IsInPlay() const;
		void SetLocation(std::shared_ptr<Location> newLocation);
		void RemoveFromPlay();
		const Type& GetType() const;

		operator std::string() const;

	private:
		Type type;
		std::shared_ptr<Location> location;
	};

	std::ostream& operator<<(std::ostream& output, const Piece& piece);
	std::string PieceTypeToString(const Piece::Type& type);
}