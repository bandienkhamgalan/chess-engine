#include "mocks/Piece.hpp"

namespace Chess
{
namespace Mocks
{
	using namespace std;

	Piece::Piece()
		: player { Player::White }, type { IPiece::Pawn }
	{

	}

	const Player& Piece::GetPlayer()
	{
		++GetPlayerCalls;
		return player;
	}

	const IPiece::Type& Piece::GetType()
	{
		++GetTypeCalls;
		return type;
	}

	const Location& Piece::GetLocation()
	{
		++GetLocationCalls;
		return square.lock()->GetLocation();
	}

	bool Piece::IsInPlay()
	{
		++IsInPlayCalls;
		return !square.expired();
	}

	void Piece::RemoveFromPlay()
	{
		++RemoveFromPlayCalls;
		square.reset();
	}

	void Piece::SetLocation(std::shared_ptr<ISquare> newSquare)
	{
		++SetLocationCalls;
		square = newSquare;
	}
}
}