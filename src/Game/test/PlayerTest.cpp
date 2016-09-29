#include <stdexcept>
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Player.hpp"
#include "Location.hpp"
#include "mocks/Piece.hpp"

using namespace std;
using namespace Chess;

TEST(Player_constructor_color, InvalidColor_ThrowsOutOfRangeException)
{
	EXPECT_THROW(Player player(Player::UNDEFINED), out_of_range);
	EXPECT_THROW(Player player(Player::MAX), out_of_range);
}

TEST(Player_constructor_color, ValidColor_InitializesColor)
{
	Player player(Player::White);
	EXPECT_EQ(player.GetColor(), Player::White);
}

TEST(Player_AddPiece, NonNullPiece_AddsPiece)
{
	Player player { Player::White };
	EXPECT_EQ(player.GetPieces().size(), 0);
	player.AddPiece(make_shared<Mocks::Piece>());
	EXPECT_EQ(player.GetPieces().size(), 1);
}

TEST(Player_AddPiece, NullPiece_ThrowsInvalidArgumentException)
{
	Player player { Player::White };
	EXPECT_THROW(player.AddPiece(shared_ptr<IPiece>(nullptr)), invalid_argument);
}