#include "mocks/Piece.hpp"

namespace Chess
{
namespace Mocks
{
	using namespace std;

	Piece::Piece()
		: player { Player::White }, type { IPiece::Pawn }
	{
		GetTypeCalls = new int(0);
		GetPlayerCalls = new int(0);
		GetValidMovesCalls = new int(0);
		GetColorCalls = new int(0);
		IsInPlayCalls = new int(0);
		GetLocationCalls = new int(0);
	}

	Piece::~Piece()
	{
		delete GetTypeCalls;
		delete GetPlayerCalls;
		delete GetValidMovesCalls;
		delete GetColorCalls;
		delete IsInPlayCalls;
		delete GetLocationCalls;
	}

	const IPlayer& Piece::GetPlayer() const
	{
		++(*GetPlayerCalls);
		return player;
	}

	const IPiece::Type& Piece::GetType() const
	{
		++(*GetTypeCalls);
		return type;
	}

	const Location& Piece::GetLocation() const
	{
		++(*GetLocationCalls);
		return square.lock()->GetLocation();
	}

	const IPlayer::Color& Piece::GetColor() const
	{
		++(*GetColorCalls);
		return player.GetColor();
	}

	const std::vector<Location>& Piece::GetValidMoves() const
	{
		++(*GetValidMovesCalls);
		return GetValidMovesReturnValue;
	}

	bool Piece::IsInPlay() const
	{
		++(*IsInPlayCalls);
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