#pragma once

#include "ISquare.hpp"
#include "IPiece.hpp"
#include "Player.hpp"
#include "Location.hpp"
#include <memory>
#include <vector>

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
		~Piece();
		int* GetPlayerCalls;
		const IPlayer& GetPlayer() const override;
		int* GetTypeCalls;
		const Type& GetType() const override;
		int* GetLocationCalls = 0;
		const Location& GetLocation() const override;
		int* GetColorCalls;
		const IPlayer::Color& GetColor() const override;
		int* GetValidMovesCalls = 0;
		std::vector<Location> GetValidMovesReturnValue;
		const std::vector<Location>& GetValidMoves() const override;
		int* IsInPlayCalls;
		bool IsInPlay() const override;
		int RemoveFromPlayCalls = 0;
		void RemoveFromPlay() override;
		int SetLocationCalls = 0;
		void SetLocation(std::shared_ptr<ISquare> newSquare) override;
	};
}
}