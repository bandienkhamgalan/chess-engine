#pragma once

#include "IPiece.hpp"
#include <vector>
#include <memory>

namespace Chess
{
	class Player
	{
	public:
		enum Color : uint8_t
		{
			UNDEFINED = 0,
			White,
			Black,
			MAX
		};

		Player() = delete;
		Player(const Color& color);

		const Color& GetColor() const;
		const std::vector<std::shared_ptr<IPiece>>& GetPieces() const;

		void AddPieces(std::vector<std::shared_ptr<IPiece>> pieces);
		void AddPiece(std::shared_ptr<IPiece> piece);

	private:
		Color color;
		std::vector<std::shared_ptr<IPiece>> pieces;
	};
}