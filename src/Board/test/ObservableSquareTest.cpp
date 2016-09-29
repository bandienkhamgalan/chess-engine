#include <stdexcept>
#include "gtest/gtest.h"
#include "ObservableSquare.hpp"
#include "Location.hpp"
#include "mocks/Piece.hpp"
#include "Player.hpp"

using namespace std;
using namespace Chess;

TEST(ObservableSquare_Constructor, InitializesInstanceVariables)
{
	ObservableSquare square { Location::a1  };
	EXPECT_EQ(square.GetLocation(), Location::a1 );
}

TEST(ObservableSquare_GetPiece, NullPiece_ThrowsRuntimeErrorException)
{
	ObservableSquare square { Location::a1 };
	EXPECT_THROW(square.GetPiece(), runtime_error);
}

TEST(ObservableSquare_GetPiece, NonNullPiece_DoesNotThrowAndReturnsPiece)
{
	ObservableSquare square { Location::a1 };
	auto piece = make_shared<Mocks::Piece>();
	square.AssignPiece(piece);
	square.GetPiece();
	EXPECT_EQ(&square.GetPiece(), piece.get());
}

TEST(ObservableSquare_HasPiece, NullPiece_ReturnsFalse)
{
	ObservableSquare square { Location::a1 };
	EXPECT_EQ(square.HasPiece(), false);
}

TEST(ObservableSquare_HasPiece, NonNullPiece_ReturnsTrue)
{
	ObservableSquare square { Location::a1 };
	auto piece = make_shared<Mocks::Piece>();
	square.AssignPiece(piece);
	EXPECT_EQ(square.HasPiece(), true);
}