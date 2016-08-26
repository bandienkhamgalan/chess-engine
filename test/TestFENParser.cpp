#include "FENParser.hpp"
#include "mocks/FENParserDelegate.hpp"
#include <boost/test/unit_test.hpp>
#include <tuple>
#include <string>

BOOST_AUTO_TEST_SUITE(FENParser_)

	using namespace std;
	using namespace Chess;
	using namespace Chess::IO;

	BOOST_AUTO_TEST_SUITE(Pre_Validation)

		BOOST_AUTO_TEST_CASE(ErrorsGiveSelfPointer)
		{
			Mocks::FENParserDelegate delegate;
			FENParser parser { delegate, "!@#$$^&*()!@#$$^&*()!@#$" };
			parser.BeginParsing();
			BOOST_REQUIRE_EQUAL(delegate.FENParserErrorParams.size(), 1);
			BOOST_CHECK_EQUAL(get<0>(delegate.FENParserErrorParams[0]), &parser);
		}
	
		BOOST_AUTO_TEST_CASE(LengthCheck)
		{
			Mocks::FENParserDelegate delegate;
			FENParser parser { delegate, "!@#$$^&*()!@#$$^&*()!@#$" };
			parser.BeginParsing();
			BOOST_CHECK_EQUAL(delegate.FENParserErrorParams.size(), 1);
			BOOST_CHECK(get<1>(delegate.FENParserErrorParams[0]).find("length check") != string::npos);
		}
	
		BOOST_AUTO_TEST_CASE(CharacterSetCheck)
		{
			Mocks::FENParserDelegate delegate;
			FENParser parser { delegate, "!@#$$^&*()!@#$$^&*()!@#$^&*" };
			parser.BeginParsing();
			BOOST_CHECK_EQUAL(delegate.FENParserErrorParams.size(), 1);
			BOOST_CHECK(get<1>(delegate.FENParserErrorParams[0]).find("character set check") != string::npos);
		}
	
		BOOST_AUTO_TEST_CASE(ComponentCountCheckTooFew)
		{
			Mocks::FENParserDelegate delegate;
			FENParser parser { delegate, "wwwww wwwww wwwww wwwww wwwww" };
			parser.BeginParsing();
			BOOST_CHECK_EQUAL(delegate.FENParserErrorParams.size(), 1);
			BOOST_CHECK(get<1>(delegate.FENParserErrorParams[0]).find("component count check") != string::npos);
		}
	
		BOOST_AUTO_TEST_CASE(ComponentCountCheckTooMany)
		{
			Mocks::FENParserDelegate delegate;
			FENParser parser { delegate, "wwwww wwwww wwww wwwww wwwww wwwww wwwww" };
			parser.BeginParsing();
			BOOST_CHECK_EQUAL(delegate.FENParserErrorParams.size(), 1);
			BOOST_CHECK(get<1>(delegate.FENParserErrorParams[0]).find("component count check") != string::npos);
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(PiecePlacementComponent)
	
		BOOST_AUTO_TEST_CASE(EmptyChessBoard_Success)
		{
			Mocks::FENParserDelegate delegate;
			FENParser parser { delegate, "8/8/8/8/8/8/8/8 w - - 0 1" };
			parser.BeginParsing();
			BOOST_CHECK_EQUAL(delegate.FENParserErrorParams.size(), 0);
			BOOST_CHECK_EQUAL(delegate.FENParserPieceParams.size(), 0);
		}
	
		BOOST_AUTO_TEST_CASE(OnePiece_Success)
		{
			Mocks::FENParserDelegate delegate;
			FENParser parser { delegate, "8/8/8/4p3/8/8/8/8 w - - 0 1" };
			parser.BeginParsing();
			BOOST_CHECK_EQUAL(delegate.FENParserErrorParams.size(), 0);
			BOOST_CHECK_EQUAL(delegate.FENParserPieceParams.size(), 1);
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()