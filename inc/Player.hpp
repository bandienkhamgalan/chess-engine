#pragma once

#include "IPlayer.hpp"
#include "IPiece.hpp"
#include <vector>
#include <memory>

namespace Chess
{
	class Player
		: public IPlayer
	{
	public:
		Player() = delete;
		Player(const IPlayer::Color& color);

		const IPlayer::Color& GetColor() const override;
		const std::vector<std::shared_ptr<IPiece>>& GetPieces() const override;

		void AddPiece(std::shared_ptr<IPiece> piece) override;

	private:
		IPlayer::Color color;
		std::vector<std::shared_ptr<IPiece>> pieces;
	};
}