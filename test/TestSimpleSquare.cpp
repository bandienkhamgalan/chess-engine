#include <stdexcept>
#include "gtest/gtest.h"
#include "SimpleSquare.hpp"
#include "Location.hpp"
#include "mocks/Piece.hpp"
#include "Player.hpp"

using namespace std;
using namespace Chess;

TEST(SimpleSquare_Constructor, InitializesInstanceVariables)
{
	SimpleSquare square { Location::a1  };
	EXPECT_EQ(square.GetLocation(), Location::a1 );
}

TEST(SimpleSquare_GetPiece, NullPiece_ThrowsRuntimeErrorException)
{
	SimpleSquare square { Location::a1 };
	EXPECT_THROW(square.GetPiece(), runtime_error);
}

TEST(SimpleSquare_GetPiece, NonNullPiece_DoesNotThrowAndReturnsPiece)
{
	SimpleSquare square { Location::a1 };
	auto piece = make_shared<Mocks::Piece>();
	square.AssignPiece(piece);
	square.GetPiece();
	EXPECT_EQ(&square.GetPiece(), piece.get());
}

TEST(SimpleSquare_HasPiece, NullPiece_ReturnsFalse)
{
	SimpleSquare square { Location::a1 };
	EXPECT_EQ(square.HasPiece(), false);
}

TEST(SimpleSquare_HasPiece, NonNullPiece_ReturnsTrue)
{
	SimpleSquare square { Location::a1 };
	auto piece = make_shared<Mocks::Piece>();
	square.AssignPiece(piece);
	EXPECT_EQ(square.HasPiece(), true);
}