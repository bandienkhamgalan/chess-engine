#include "Player.hpp"
#include <stdexcept>

namespace Chess
{
	using namespace std;

	/* Constructors */

	Player::Player(const Player::Color& _color) 
		: color { _color }
	{
		if( color <= Player::Color::UNDEFINED || color >= Player::Color::MAX )
			throw out_of_range("Player::Player() : invalid player color");
	}

	/* Public Methods */

	const Player::Color& Player::GetColor() const
	{
		return color;
	}

	const vector<shared_ptr<IPiece>>& Player::GetPieces() const
	{
		return pieces;
	}

	void Player::AddPieces(vector<shared_ptr<IPiece>> pieces)
	{
		for (auto piece : pieces)
			AddPiece(piece);
	}

	void Player::AddPiece(shared_ptr<IPiece> piece)
	{
		if (!piece)
			throw invalid_argument("Player::AddPiece : piece is null");
		pieces.emplace_back(piece);
	}
}