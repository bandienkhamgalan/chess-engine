#pragma once
#include "gmock/gmock.h"
#include "ISquare.hpp"

namespace Chess
{
namespace Mocks
{
	class Square
		: public ISquare
	{
	public:
		MOCK_CONST_METHOD0(GetLocation, const Location&());
		MOCK_CONST_METHOD0(GetPiece, IPiece&());
		MOCK_CONST_METHOD0(HasPiece, bool());
		MOCK_METHOD0(RemovePiece, void());
		MOCK_METHOD1(AssignPiece, void(std::shared_ptr<IPiece>));
	};
}
}