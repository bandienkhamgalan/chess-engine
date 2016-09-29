#pragma once
#include <vector>
#include <memory>
#include "IObservableSquare.hpp"
#include "IObservableSquareObservor.hpp"
#include "Location.hpp"

namespace Chess
{
	class ObservableSquare :
		public IObservableSquare
	{
	public:
		ObservableSquare() = delete;
		ObservableSquare(const Location &location);

		/* ISquare methods */
		const Location& GetLocation() const override;
		IPiece& GetPiece() const override;
		bool HasPiece() const override;
		void RemovePiece() override;
		void AssignPiece(std::shared_ptr<IPiece> toAssign) override;

		/* IObservableSquare methods*/
		void AddListener(IObservableSquareObservor* observor, const IObservableSquare::Event& event) override;
		void RemoveListener(IObservableSquareObservor* observor, const IObservableSquare::Event& event) override;
	private:
		const Location location;
		std::shared_ptr<IPiece> piece;
		std::vector<IObservableSquareObservor*> listeners;

		void NotifyListeners(const IObservableSquare::Event& event);
	};
}