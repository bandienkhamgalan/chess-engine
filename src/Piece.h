#pragma once

#include "Location.h"
#include <memory>

namespace Chess
{
	class Piece
	{
	private:
		std::shared_ptr<Location> location;
		
	public:
		Piece(const Location& location);
		const Location& GetLocation() const;
		bool IsInPlay() const;
		void SetLocation(std::shared_ptr<Location> newLocation);
		void RemoveFromPlay();
	};
}