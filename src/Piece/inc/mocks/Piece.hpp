#pragma once
#include <memory>
#include <vector>
#include "gmock/gmock.h"
#include "ISquare.hpp"
#include "IPiece.hpp"
#include "Player.hpp"
#include "Location.hpp"

namespace Chess
{
namespace Mocks
{
	class Piece
		: public IPiece
	{
	public:
		MOCK_CONST_METHOD0(GetPlayer, const IPlayer&());
		MOCK_CONST_METHOD0(GetType, const Type&());
		MOCK_CONST_METHOD0(GetLocation, const Location&());
		MOCK_CONST_METHOD0(GetColor, const IPlayer::Color&());
		MOCK_CONST_METHOD0(GetValidMoves, const std::vector<Location>&());
		MOCK_CONST_METHOD0(IsInPlay, bool());
		MOCK_METHOD0(RemoveFromPlay, void());
		MOCK_METHOD1(SetLocation, void(std::shared_ptr<ISquare>));
	};
}
}