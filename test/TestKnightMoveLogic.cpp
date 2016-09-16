#include <boost/test/unit_test.hpp>
#include <stdexcept>
#include "KnightMoveLogic.hpp"
#include "mocks/Board.hpp"
#include "mocks/Piece.hpp"

using namespace std;
using namespace Chess;

BOOST_AUTO_TEST_SUITE(KnightMoveLogic_)

	BOOST_AUTO_TEST_SUITE(SetPiece)
	
		BOOST_AUTO_TEST_CASE(NullPiece_ThrowsInvalidArgumentException)
		{
			KnightMoveLogic knightMoveLogic { make_shared<Mocks::Board>() };
			BOOST_CHECK_THROW(knightMoveLogic.SetPiece(shared_ptr<IPiece>(nullptr)), invalid_argument);
		}
	
		BOOST_AUTO_TEST_CASE(ExistingPiece_ThrowsRuntimeErrorException)
		{
			shared_ptr<IPiece> piece { make_shared<Mocks::Piece>() };
			KnightMoveLogic knightMoveLogic { make_shared<Mocks::Board>(), piece };
			BOOST_CHECK_THROW(knightMoveLogic.SetPiece(make_shared<Mocks::Piece>()), runtime_error);
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(GetValidMoves)

		struct GetValidMovesFixture
		{
			shared_ptr<Mocks::Board> board;
			shared_ptr<Mocks::Piece> piece;
			KnightMoveLogic knightMoveLogic;

			GetValidMovesFixture()
				: board(make_shared<Mocks::Board>()), piece(make_shared<Mocks::Piece>()), knightMoveLogic(board, piece)
			{

			}
		};
	
		BOOST_AUTO_TEST_CASE(NoPiece_ThrowsRuntimeErrorException)
		{
			auto board { make_shared<Mocks::Board>() };
			KnightMoveLogic knightMoveLogic { board };
			BOOST_CHECK_THROW(knightMoveLogic.GetValidMoves(), runtime_error);
		}

		BOOST_AUTO_TEST_CASE(BoardExpired_ThrowsRuntimeErrorException)
		{
			shared_ptr<IPiece> piece { make_shared<Mocks::Piece>() };
			KnightMoveLogic knightMoveLogic { make_shared<Mocks::Board>(), piece };
			BOOST_CHECK_THROW(knightMoveLogic.GetValidMoves(), runtime_error);
		}
	
		BOOST_FIXTURE_TEST_CASE(PieceNotInPlay_ReturnsEmptyVector, GetValidMovesFixture)
		{
			BOOST_CHECK_EQUAL(knightMoveLogic.GetValidMoves().size(), 0);
		}
	
		BOOST_FIXTURE_TEST_CASE(StartingPosition_TwoMoves, GetValidMovesFixture)
		{
			piece->IsInPlayReturnValue = true;
			piece->GetLocationReturnValue = Location(Location::b1);
			const vector<Location>& validMoves = knightMoveLogic.GetValidMoves();
			BOOST_CHECK_EQUAL(validMoves.size(), 2);
			BOOST_CHECK_EQUAL(count(validMoves.begin(), validMoves.end(), Location(Location::a3)), 1);
			BOOST_CHECK_EQUAL(count(validMoves.begin(), validMoves.end(), Location(Location::c3)), 1);
		}
	
		BOOST_FIXTURE_TEST_CASE(StartingPosition_OccupiedOneMove, GetValidMovesFixture)
		{
			piece->IsInPlayReturnValue = true;
			piece->GetLocationReturnValue = Location(Location::b1);
			board->HasPieceAtLocationReturnValue[Location::a3] = true;
			const vector<Location>& validMoves = knightMoveLogic.GetValidMoves();
			BOOST_CHECK_EQUAL(validMoves.size(), 1);
			BOOST_CHECK_EQUAL(count(validMoves.begin(), validMoves.end(), Location(Location::c3)), 1);
			BOOST_CHECK_EQUAL(count(validMoves.begin(), validMoves.end(), Location(Location::a3)), 0);
		}
	
		BOOST_FIXTURE_TEST_CASE(CenterPosition_BoardFree_FourMoves, GetValidMovesFixture)
		{
			piece->IsInPlayReturnValue = true;
			piece->GetLocationReturnValue = Location(Location::e4);
			const vector<Location>& validMoves = knightMoveLogic.GetValidMoves();
			BOOST_CHECK_EQUAL(validMoves.size(), 4);
			BOOST_CHECK_EQUAL(count(validMoves.begin(), validMoves.end(), Location(Location::d6)), 1);
			BOOST_CHECK_EQUAL(count(validMoves.begin(), validMoves.end(), Location(Location::f6)), 1);
			BOOST_CHECK_EQUAL(count(validMoves.begin(), validMoves.end(), Location(Location::d2)), 1);
			BOOST_CHECK_EQUAL(count(validMoves.begin(), validMoves.end(), Location(Location::f2)), 1);
		}
	
		BOOST_FIXTURE_TEST_CASE(CenterPosition_WholeBoardOccupied_ReturnsEmptyVector, GetValidMovesFixture)
		{
			piece->IsInPlayReturnValue = true;
			piece->GetLocationReturnValue = Location(Location::e4);
			Location::for_each( [&](const Location& current){
				board->HasPieceAtLocationReturnValue[current] = true;
			});
			const vector<Location>& validMoves = knightMoveLogic.GetValidMoves();
			BOOST_CHECK_EQUAL(validMoves.size(), 0);
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()