#pragma once
#include "IObservableSquareFactory.hpp"

namespace Chess
{
	class ObservableSquareFactory
		: public IObservableSquareFactory
	{
	public:
		std::unique_ptr<IObservableSquare> makeSquare(const Location& location) override;
	};
}