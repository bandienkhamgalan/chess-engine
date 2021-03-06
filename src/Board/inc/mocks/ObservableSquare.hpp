#pragma once
#include "gmock/gmock.h"
#include "IObservableSquare.hpp"

namespace Chess
{
namespace Mocks
{
	class ObservableSquare
		: public IObservableSquare
	{
	public:
		/* ISquare methods */
		MOCK_CONST_METHOD0(GetLocation, const Location&());
		MOCK_CONST_METHOD0(GetPiece, IPiece&());
		MOCK_CONST_METHOD0(HasPiece, bool());
		MOCK_METHOD0(RemovePiece, void());
		MOCK_METHOD1(AssignPiece, void(std::shared_ptr<IPiece>));

		/* IObservableSquare methods */
		MOCK_METHOD2(AddListener, void(IObservableSquareObservor*, const IObservableSquare::Event&));
		MOCK_METHOD2(RemoveListener, void(IObservableSquareObservor*, const IObservableSquare::Event&));
	};
}
}