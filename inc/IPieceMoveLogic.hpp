#pragma once
#include "Location.hpp"
#include <memory>

namespace Chess
{
	class IPiece;
	class IPieceMoveLogic
	{
	public:
		virtual ~IPieceMoveLogic() {};
		virtual void SetPiece(std::shared_ptr<IPiece> _piece) = 0;
		virtual const std::vector<Location>& GetValidMoves() = 0;
	};
}