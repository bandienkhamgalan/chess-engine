#include "Helpers.hpp"
#include "Board.hpp"
#include "Location.hpp"
#include "Player.hpp"
#include "mocks/Piece.hpp"
#include "mocks/SquareFactory.hpp"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(Board_)

	using namespace std;
	using namespace Chess;	

	BOOST_AUTO_TEST_SUITE(Constructor)

		BOOST_AUTO_TEST_CASE(InitializesSquares)
		{
			Mocks::SquareFactory mockSquareFactory;
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
			Mocks::SquareFactory mockSquareFactory;
			Board board { mockSquareFactory };
			Location::for_each( [&](Location current)
			{
				BOOST_CHECK_MESSAGE(!board.HasPieceAtLocation(current), Helpers::sprint(current, " should be empty"));
			});
		}

	BOOST_AUTO_TEST_SUITE_END()

	struct PieceAtLocation_Fixture
	{
		Mocks::SquareFactory mockSquareFactory;
		Board board;
		Location location;
		Player player;
		shared_ptr<Mocks::Piece> piece;

		PieceAtLocation_Fixture(Location _location = Location::a1)
			: board { mockSquareFactory }, location { _location }, player { Player::White }
		{
			piece = make_shared<Mocks::Piece>();
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

		BOOST_FIXTURE_TEST_CASE(ExistingPiece_DoesNotThrowAndReturnsPiece, PieceAtLocation_Fixture)
		{
			BOOST_CHECK_NO_THROW(board.GetPieceAtLocation(location));
			BOOST_CHECK_EQUAL(&board.GetPieceAtLocation(location), piece.get());
		}

		BOOST_FIXTURE_TEST_CASE(NonExistingPiece_Throws, PieceAtLocation_Fixture)
		{
			BOOST_CHECK_THROW(board.GetPieceAtLocation(Location::h8), runtime_error);
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(AddPieceAtLocation)

		BOOST_FIXTURE_TEST_CASE(NonNullPiece_SquareEmpty_Success, PieceAtLocation_Fixture)
		{
			BOOST_CHECK(board.HasPieceAtLocation(location));
			BOOST_REQUIRE_MESSAGE(piece->SetLocationParams.size() == 1, "calls Piece::SetLocation() once");
			BOOST_CHECK_MESSAGE(piece->SetLocationParams[0]->GetLocation() == location, "calls Piece::SetLocation() with correct ISquare");
			BOOST_CHECK_MESSAGE(&piece->SetLocationParams[0]->GetPiece() == piece.get(), "assigns IPiece to ISquare (mem address check)");
			BOOST_CHECK_MESSAGE(piece->GetLocation() == location, "sets Piece location");
		}

		BOOST_FIXTURE_TEST_CASE(NonNullPiece_SquareOccupied_ThrowsException, PieceAtLocation_Fixture)
		{
			auto piece = make_shared<Mocks::Piece>();
			BOOST_CHECK_THROW(board.AddPieceAtLocation(piece, location), invalid_argument);
		}

		BOOST_FIXTURE_TEST_CASE(NullPiece_ThrowsException, PieceAtLocation_Fixture)
		{
			BOOST_CHECK_THROW(board.AddPieceAtLocation(shared_ptr<IPiece>(nullptr), Location::h8), invalid_argument);
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(MovePieceToLocation)

		BOOST_FIXTURE_TEST_CASE(NullPiece_ThrowsInvalidArgument, PieceAtLocation_Fixture)
		{
			BOOST_CHECK_THROW(board.MovePieceToLocation(shared_ptr<IPiece>(nullptr), Location::h8), invalid_argument);
		}

		BOOST_FIXTURE_TEST_CASE(PieceNotInPlay_ThrowsInvalidArgument, PieceAtLocation_Fixture)
		{
			auto piece = make_shared<Mocks::Piece>();
			BOOST_CHECK_THROW(board.MovePieceToLocation(piece, Location::a1), runtime_error);
		}

		BOOST_FIXTURE_TEST_CASE(UnregisteredPieceInPlay_ThrowsInvalidArgument, PieceAtLocation_Fixture)
		{
			auto piece = make_shared<Mocks::Piece>();
			piece->IsInPlayReturnValue = true;
			BOOST_CHECK_THROW(board.MovePieceToLocation(piece, Location::a1), invalid_argument);
		}

		BOOST_FIXTURE_TEST_CASE(LocationOccupied_ThrowsInvalidArgument, PieceAtLocation_Fixture)
		{
			auto piece2 = make_shared<Mocks::Piece>();
			board.AddPieceAtLocation(piece2, Location::a2);
			piece->IsInPlayReturnValue = true;
			BOOST_CHECK_THROW(board.MovePieceToLocation(piece, Location::a2), invalid_argument);
		}

		BOOST_FIXTURE_TEST_CASE(Success, PieceAtLocation_Fixture)
		{
			Location newLocation { Location::a2 };
			piece->IsInPlayReturnValue = true;
			BOOST_REQUIRE(piece->SetLocationParams.size() == 1);
			BOOST_CHECK_MESSAGE(piece->SetLocationParams[0]->GetLocation() == location, "pre: piece location");
			BOOST_CHECK_MESSAGE(board.HasPieceAtLocation(location), "pre: removes piece from old square");
			BOOST_CHECK_MESSAGE(!board.HasPieceAtLocation(newLocation), "pre: destination square empty");
			board.MovePieceToLocation(piece, newLocation);
			BOOST_CHECK_MESSAGE(!board.HasPieceAtLocation(location), "removes piece from old square");
			BOOST_CHECK_MESSAGE(board.HasPieceAtLocation(newLocation), "moves piece to new square");
			BOOST_REQUIRE(piece->SetLocationParams.size() == 2);
			BOOST_CHECK_MESSAGE(piece->SetLocationParams[1]->GetLocation() == newLocation, "sets Piece location");
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()