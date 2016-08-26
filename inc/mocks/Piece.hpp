#pragma once

#include "ISquare.hpp"
#include "IPiece.hpp"
#include "Player.hpp"
#include "Location.hpp"
#include <memory>

namespace Chess
{
namespace Mocks
{
	class Piece
		: public IPiece
	{
	public:
		Player player;
		Type type;
		std::weak_ptr<ISquare> square;

		Piece();
		int GetPlayerCalls = 0;
		const Player& GetPlayer() override;
		int GetTypeCalls = 0;
		const Type& GetType() override;
		int GetLocationCalls = 0;
		const Location& GetLocation() override;
		int IsInPlayCalls = 0;
		bool IsInPlay() override;
		int RemoveFromPlayCalls = 0;
		void RemoveFromPlay() override;
		int SetLocationCalls = 0;
		void SetLocation(std::shared_ptr<ISquare> newSquare) override;
	};
}
}