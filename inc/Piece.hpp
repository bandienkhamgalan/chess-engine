#pragma once

#include "ISquare.hpp"
#include "IPiece.hpp"
#include <memory>

namespace Chess
{
	class Player;
	class Location;
	
	class Piece
		: public IPiece
	{
	public:
		Piece() = delete;
		Piece(const Player& _player, const Type& _type);

		const Player& GetPlayer() const override;
		const Type& GetType() const override;
		const Location& GetLocation() const override;
		bool IsInPlay() const override;
		void RemoveFromPlay() override;
		operator std::string() const;

		void SetLocation(std::shared_ptr<ISquare> newSquare) override;

	private:
		const Player& player;
		Type type;
		std::weak_ptr<ISquare> square;
	};

	std::ostream& operator<<(std::ostream& output, const Piece& piece);
	std::string PieceTypeToString(const IPiece::Type& type);
}