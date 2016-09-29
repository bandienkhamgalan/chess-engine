#pragma once
#include "ISquare.hpp"

namespace Chess
{
	class IObservableSquareObservor;
	class IObservableSquare
		: public ISquare
	{
	public:
		enum Event
		{
			UNDEFINED = 0,
			OccupantChanged,
			AttackersChanged,
			MAX
		};

		virtual ~IObservableSquare() {};
		virtual void AddListener(IObservableSquareObservor* observor, const IObservableSquare::Event& event) = 0;
		virtual void RemoveListener(IObservableSquareObservor* observor, const IObservableSquare::Event& event) = 0;
	};
}