#pragma once
#include "Location.hpp"

namespace Chess
{
	class IPieceMoveLogic
	{
	public:
		virtual ~IPieceMoveLogic() {};
		virtual const std::vector<Location>& GetValidMoves() const = 0;
	};
}