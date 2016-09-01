#pragma once
#include <memory>
#include <vector>
#include "IPlayer.hpp"

namespace Chess
{
	class IPiece;
	class IPlayer
	{
	public:
		enum Color : uint8_t
		{
			UNDEFINED = 0,
			White,
			Black,
			MAX
		};

		virtual const IPlayer::Color& GetColor() const = 0;
		virtual const std::vector<std::shared_ptr<IPiece>>& GetPieces() const = 0;
		virtual void AddPiece(std::shared_ptr<IPiece> piece) = 0;
		virtual ~IPlayer() {};
	};
}