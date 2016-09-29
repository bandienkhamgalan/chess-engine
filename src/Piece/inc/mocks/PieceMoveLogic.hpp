#pragma once
#include <memory>
#include <vector>
#include "gmock/gmock.h"
#include "IPieceMoveLogic.hpp"
#include "IPiece.hpp"
#include "Location.hpp"

namespace Chess
{
namespace Mocks
{
	class PieceMoveLogic
		: public IPieceMoveLogic
	{
	public:
		MOCK_METHOD0(GetValidMoves, const std::vector<Location>&());
		MOCK_METHOD1(SetPiece, void(std::weak_ptr<IPiece>));
	};
}
}