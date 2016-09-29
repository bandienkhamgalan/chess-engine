#pragma once
#include <map>
#include <memory>
#include "gmock/gmock.h"
#include "IObservableSquareFactory.hpp"
#include "IObservableSquare.hpp"
#include "Location.hpp"

namespace Chess
{
namespace Mocks
{
	class ObservableSquareFactory
		: public IObservableSquareFactory
	{
	public:
		MOCK_METHOD1(makeSquare, std::unique_ptr<IObservableSquare>(const Location&));
	};
}
}