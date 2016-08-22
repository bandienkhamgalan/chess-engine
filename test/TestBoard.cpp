#include "Helpers.hpp"
#include "Board.hpp"
#include "Piece.hpp"
#include "Location.hpp"
#include "Player.hpp"
#include "mocks/MockSquareFactory.hpp"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(Board_)

	using namespace std;
	using namespace Chess;	

	BOOST_AUTO_TEST_SUITE(Constructor)

		BOOST_AUTO_TEST_CASE(InitializesSquares)
		{
			MockSquareFactory mockSquareFactory;
			Board board { mockSquareFactory };
			Location::for_each( [&](Location current)
			{
				int calls = 0;
				try {
					calls = mockSquareFactory.makeSquareCalls.at(current);
				} catch(const out_of_range&) { }

				BOOST_CHECK_MESSAGE(calls == 1, Helpers::sprint("Constructor called factory instantiator for square ", current, " ", calls, " times (should be 1). "));
			});
		}

		BOOST_AUTO_TEST_CASE(AllSquaresEmpty)
		{
			MockSquareFactory mockSquareFactory;
			Board board { mockSquareFactory };
			Location::for_each( [&](Location current)
			{
				BOOST_CHECK_MESSAGE(!board.HasPieceAtLocation(current), Helpers::sprint(current, " should be empty"));
			});
		}

	BOOST_AUTO_TEST_SUITE_END()

	shared_ptr<IPiece> makePiece(const Player& player, const IPiece::Type type = IPiece::Pawn)
	{
		return make_shared<Piece>(player, type);
	}

	struct PieceAtLocation_Fixture
	{
		MockSquareFactory mockSquareFactory;
		Board board;
		Location location;
		Player player;
		shared_ptr<IPiece> piece;

		PieceAtLocation_Fixture(Location _location)
			: board { mockSquareFactory }, location { _location }, player { Player::White }
		{
			piece = makePiece(player);
			board.AddPieceAtLocation(piece, location);
		}
	};

	BOOST_AUTO_TEST_SUITE(HasPieceAtLocation)

		BOOST_AUTO_TEST_CASE(Success)
		{
			Location::for_each( [](Location addPieceToThisLocation)
			{
				PieceAtLocation_Fixture fixture {addPieceToThisLocation};
				Location::for_each( [&](Location toCheck)
				{
					if(toCheck == addPieceToThisLocation)
						BOOST_CHECK_MESSAGE(fixture.board.HasPieceAtLocation(toCheck), Helpers::sprint(toCheck, " should be occupied"));
					else
						BOOST_CHECK_MESSAGE(!fixture.board.HasPieceAtLocation(toCheck), Helpers::sprint(toCheck, " should be empty"));	
				});
			});	
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(GetPieceAtLocation)

		BOOST_AUTO_TEST_CASE(ExistingPiece_DoesNotThrowAndReturnsPiece)
		{
			PieceAtLocation_Fixture fixture { Location::d4 };
			BOOST_CHECK_NO_THROW(fixture.board.GetPieceAtLocation(fixture.location));
			BOOST_CHECK_EQUAL(&fixture.board.GetPieceAtLocation(fixture.location), fixture.piece.get());
		}

		BOOST_AUTO_TEST_CASE(NonExistingPiece_Throws)
		{
			PieceAtLocation_Fixture fixture { Location::d4 };
			BOOST_CHECK_THROW(fixture.board.GetPieceAtLocation(Location::a1), runtime_error);
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(AddPieceAtLocation)

		BOOST_AUTO_TEST_CASE(NonNullPiece_SquareEmpty_GetsAdded)
		{
			PieceAtLocation_Fixture fixture { Location::d4 };
			BOOST_CHECK(fixture.board.HasPieceAtLocation(fixture.location));
		}

		BOOST_AUTO_TEST_CASE(NonNullPiece_SquareOccupied_ThrowsException)
		{
			PieceAtLocation_Fixture fixture { Location::d4 };
			Player player { Player::White };
			auto piece2 = makePiece(player);
			BOOST_CHECK_THROW(fixture.board.AddPieceAtLocation(piece2, fixture.location), invalid_argument);
		}

		BOOST_AUTO_TEST_CASE(NullPiece_ThrowsException)
		{
			MockSquareFactory mockFactory;
			Board board { mockFactory };
			BOOST_CHECK_THROW(board.AddPieceAtLocation(shared_ptr<IPiece>(nullptr), Location::a1), invalid_argument);
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()