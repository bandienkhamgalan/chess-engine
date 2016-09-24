#pragma once
#include <vector>
#include <memory>
#include "gmock/gmock.h"
#include "IPlayer.hpp"

namespace Chess
{
namespace Mocks
{
	class Player
		: public IPlayer
	{
	public:
		MOCK_CONST_METHOD0(GetColor, const IPlayer::Color&());
		MOCK_CONST_METHOD0(GetPieces, const std::vector<std::shared_ptr<IPiece>>&());
		MOCK_METHOD1(AddPiece, void(std::shared_ptr<IPiece>));
	};
}
}