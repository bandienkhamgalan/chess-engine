#pragma once
#include "ISquare.hpp"
#include "IPiece.hpp"
#include "Location.hpp"
#include "IPlayer.hpp"
#include <memory>
#include <string>

namespace Chess
{
	class Piece
		: public IPiece
	{
	public:
		Piece() = delete;
		Piece(const IPlayer& _player, const Type& _type);

		const IPlayer& GetPlayer() override;
		const Type& GetType() override;
		const Location& GetLocation() override;
		bool IsInPlay() override;
		void RemoveFromPlay() override;
		operator std::string() const;

		void SetLocation(std::shared_ptr<ISquare> newSquare) override;

	private:
		const IPlayer& player;
		Type type;
		std::weak_ptr<ISquare> square;
	};

	std::ostream& operator<<(std::ostream& output, const Piece& piece);
	std::string PieceTypeToString(const IPiece::Type& type);
}