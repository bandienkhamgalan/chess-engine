#pragma once
#include "ISquare.hpp"
#include "IPiece.hpp"
#include "Location.hpp"
#include "IPlayer.hpp"
#include "IPieceMoveLogic.hpp"
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
		Piece(const IPlayer& _player, const Type& _type, IPieceMoveLogic& pieceMoveLogic);

		const IPlayer& GetPlayer() const override;
		const Type& GetType() const override;
		const Location& GetLocation() const override;
		const IPlayer::Color& GetColor() const override;
		bool IsInPlay() const override;
		const std::vector<Location>& GetValidMoves() const override;

		void RemoveFromPlay() override;
		void SetLocation(std::shared_ptr<ISquare> newSquare) override;

		operator std::string() const;

	private:
		const IPlayer& player;
		Type type;
		std::weak_ptr<ISquare> square;
	};

	std::ostream& operator<<(std::ostream& output, const Piece& piece);
	std::string PieceTypeToString(const IPiece::Type& type);
}