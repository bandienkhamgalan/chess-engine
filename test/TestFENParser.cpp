#include "FENParser.hpp"
#include "mocks/FENParserDelegate.hpp"
#include <boost/test/unit_test.hpp>
#include <tuple>
#include <string>
#include <algorithm>

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
	
	BOOST_AUTO_TEST_SUITE(PieceCodeParserAndLocationLogic)

		BOOST_AUTO_TEST_SUITE(Invalid)

			BOOST_AUTO_TEST_CASE(InvalidDigitNine_Fails)
			{
				Mocks::FENParserDelegate delegate;
				FENParser parser { delegate, "8/8/8/8/8/8/8/9 w - - 0 1" };
				parser.BeginParsing();
				BOOST_CHECK_EQUAL(delegate.FENParserErrorParams.size(), 1);
				BOOST_CHECK(get<1>(delegate.FENParserErrorParams[0]).find("only use numbers 1 through 8") != string::npos);
			}

			BOOST_AUTO_TEST_CASE(InvalidDigitZero_Fails)
			{
				Mocks::FENParserDelegate delegate;
				FENParser parser { delegate, "8/8/8/8/8/8/8/0 w - - 0 1" };
				parser.BeginParsing();
				BOOST_CHECK_EQUAL(delegate.FENParserErrorParams.size(), 1);
				BOOST_CHECK(get<1>(delegate.FENParserErrorParams[0]).find("only use numbers 1 through 8") != string::npos);
			}

			BOOST_AUTO_TEST_SUITE(TooManyFiles)

				BOOST_AUTO_TEST_CASE(TooManyFilesNumber_Fails)
				{
					Mocks::FENParserDelegate delegate;
					FENParser parser { delegate, "8/8/8/8/8/4p8/8/8 w - - 0 1" };
					parser.BeginParsing();
					BOOST_CHECK_EQUAL(delegate.FENParserErrorParams.size(), 1);
					BOOST_CHECK(get<1>(delegate.FENParserErrorParams[0]).find("did not have 8 files") != string::npos);
				}

				BOOST_AUTO_TEST_CASE(TooManyFilesPiecesWithNumbersBeforePieces_Fails)
				{
					Mocks::FENParserDelegate delegate;
					FENParser parser { delegate, "8/8/8/8/8/pppp7/8/8 w - - 0 1" };
					parser.BeginParsing();
					BOOST_CHECK_EQUAL(delegate.FENParserErrorParams.size(), 1);
					BOOST_CHECK(get<1>(delegate.FENParserErrorParams[0]).find("did not have 8 files") != string::npos);
				}

				BOOST_AUTO_TEST_CASE(TooManyFilesPiecesWithNumbersAfterPieces_Fails)
				{
					Mocks::FENParserDelegate delegate;
					FENParser parser { delegate, "8/8/8/8/8/7pppp/8/8 w - - 0 1" };
					parser.BeginParsing();
					BOOST_CHECK_EQUAL(delegate.FENParserErrorParams.size(), 1);
					BOOST_CHECK(get<1>(delegate.FENParserErrorParams[0]).find("did not have 8 files") != string::npos);
				}

				BOOST_AUTO_TEST_CASE(TooManyFilesPieces_Fails)
				{
					Mocks::FENParserDelegate delegate;
					FENParser parser { delegate, "8/8/8/8/8/ppppppppppppp/8/8 w - - 0 1" };
					parser.BeginParsing();
					BOOST_CHECK_EQUAL(delegate.FENParserErrorParams.size(), 1);
					BOOST_CHECK(get<1>(delegate.FENParserErrorParams[0]).find("did not have 8 files") != string::npos);
				}

			BOOST_AUTO_TEST_SUITE_END()

			BOOST_AUTO_TEST_SUITE(TooFewFiles)

				BOOST_AUTO_TEST_CASE(TooFewFilesEmpty_Fails)
				{
					Mocks::FENParserDelegate delegate;
					FENParser parser { delegate, "8/8/8/8/7p//8/8 w - - 0 1" };
					parser.BeginParsing();
					BOOST_CHECK_EQUAL(delegate.FENParserErrorParams.size(), 1);
					BOOST_CHECK(get<1>(delegate.FENParserErrorParams[0]).find("did not have 8 files") != string::npos);
				}

				BOOST_AUTO_TEST_CASE(TooFewFilesNumber_Fails)
				{
					Mocks::FENParserDelegate delegate;
					FENParser parser { delegate, "8/8/8/8/8/7/8/8 w - - 0 1" };
					parser.BeginParsing();
					BOOST_CHECK_EQUAL(delegate.FENParserErrorParams.size(), 1);
					BOOST_CHECK(get<1>(delegate.FENParserErrorParams[0]).find("did not have 8 files") != string::npos);
				}

				BOOST_AUTO_TEST_CASE(TooFewFilesPiecesWithNumbersBeforePieces_Fails)
				{
					Mocks::FENParserDelegate delegate;
					FENParser parser { delegate, "8/8/8/8/8/pppp1/8/8 w - - 0 1" };
					parser.BeginParsing();
					BOOST_CHECK_EQUAL(delegate.FENParserErrorParams.size(), 1);
					BOOST_CHECK(get<1>(delegate.FENParserErrorParams[0]).find("did not have 8 files") != string::npos);
				}

				BOOST_AUTO_TEST_CASE(TooManyFilesPiecesWithNumbersAfterPieces_Fails)
				{
					Mocks::FENParserDelegate delegate;
					FENParser parser { delegate, "8/8/8/8/8/6p/8/8 w - - 0 1" };
					parser.BeginParsing();
					BOOST_CHECK_EQUAL(delegate.FENParserErrorParams.size(), 1);
					BOOST_CHECK(get<1>(delegate.FENParserErrorParams[0]).find("did not have 8 files") != string::npos);
				}

				BOOST_AUTO_TEST_CASE(TooManyFilesPieces_Fails)
				{
					Mocks::FENParserDelegate delegate;
					FENParser parser { delegate, "8/8/8/8/8/pp/8/8 w - - 0 1" };
					parser.BeginParsing();
					BOOST_CHECK_EQUAL(delegate.FENParserErrorParams.size(), 1);
					BOOST_CHECK(get<1>(delegate.FENParserErrorParams[0]).find("did not have 8 files") != string::npos);
				}

			BOOST_AUTO_TEST_SUITE_END()

			BOOST_AUTO_TEST_CASE(TooManyRanks_Fails)
			{
				Mocks::FENParserDelegate delegate;
				FENParser parser { delegate, "8/8/8/8/8/8/8/8/8 w - - 0 1" };
				parser.BeginParsing();
				BOOST_CHECK_EQUAL(delegate.FENParserErrorParams.size(), 1);
				BOOST_CHECK(get<1>(delegate.FENParserErrorParams[0]).find("unexpected contents after last rank") != string::npos);
			}

			BOOST_AUTO_TEST_CASE(TooFewRanks_Fails)
			{
				Mocks::FENParserDelegate delegate;
				FENParser parser { delegate, "pppppppp/8/8/8/8 w - - 0 1" };
				parser.BeginParsing();
				BOOST_CHECK_EQUAL(delegate.FENParserErrorParams.size(), 1);
				BOOST_CHECK(get<1>(delegate.FENParserErrorParams[0]).find("did not have 8 ranks") != string::npos);
			}

		BOOST_AUTO_TEST_SUITE_END()
		
		BOOST_AUTO_TEST_CASE(NoPieces_Success)
		{
			Mocks::FENParserDelegate delegate;
			FENParser parser { delegate, "8/8/8/8/8/8/8/8 w - - 0 1" };
			parser.BeginParsing();
			BOOST_CHECK_EQUAL(delegate.FENParserErrorParams.size(), 0);
			BOOST_CHECK_EQUAL(delegate.FENParserPieceParams.size(), 0);
		}

		BOOST_AUTO_TEST_CASE(FullPieces_Success)
		{
			Mocks::FENParserDelegate delegate;
			FENParser parser { delegate, "pppppppp/pppppppp/pppppppp/pppppppp/pppppppp/pppppppp/pppppppp/pppppppp w - - 0 1" };
			parser.BeginParsing();
			BOOST_CHECK_EQUAL(delegate.FENParserErrorParams.size(), 0);
			BOOST_CHECK_EQUAL(delegate.FENParserPieceParams.size(), 64);
			for(auto params : delegate.FENParserPieceParams)
			{
				BOOST_CHECK_EQUAL(get<2>(params), Player::Black);
				BOOST_CHECK_EQUAL(get<3>(params), IPiece::Pawn);
			}
		}

		BOOST_AUTO_TEST_CASE(OneWhitePieceAtA8_Success)
		{
			string pieceCodes = "PRKQBN";
			array<IPiece::Type, 6> types {{IPiece::Pawn, IPiece::Rook, IPiece::King, IPiece::Queen, IPiece::Bishop, IPiece::Knight}};
			for( auto i = 0 ; i < pieceCodes.length() ; i++)
			{
				Mocks::FENParserDelegate delegate;
				FENParser parser { delegate, string(1, pieceCodes[i]) + "7/8/8/8/8/8/8/8 w - - 0 1" };
				parser.BeginParsing();
				BOOST_CHECK_EQUAL(delegate.FENParserErrorParams.size(), 0);
				BOOST_REQUIRE_EQUAL(delegate.FENParserPieceParams.size(), 1);
				auto params = delegate.FENParserPieceParams[0];
				BOOST_CHECK_EQUAL(get<1>(params), Location::a8);
				BOOST_CHECK_EQUAL(get<2>(params), Player::White);
				BOOST_CHECK_EQUAL(get<3>(params), types[i]);
			}
		}
	
		BOOST_AUTO_TEST_CASE(OneBlackPieceAtE5_Success)
		{
			string pieceCodes = "prkqbn";
			array<IPiece::Type, 6> types {{IPiece::Pawn, IPiece::Rook, IPiece::King, IPiece::Queen, IPiece::Bishop, IPiece::Knight}};
			for( auto i = 0 ; i < pieceCodes.length() ; i++)
			{
				Mocks::FENParserDelegate delegate;
				FENParser parser { delegate, "8/8/8/4" + string(1, pieceCodes[i]) + "3/8/8/8/8 w - - 0 1" };
				parser.BeginParsing();
				BOOST_CHECK_EQUAL(delegate.FENParserErrorParams.size(), 0);
				BOOST_REQUIRE_EQUAL(delegate.FENParserPieceParams.size(), 1);
				auto params = delegate.FENParserPieceParams[0];
				BOOST_CHECK_EQUAL(get<1>(params), Location::e5);
				BOOST_CHECK_EQUAL(get<2>(params), Player::Black);
				BOOST_CHECK_EQUAL(get<3>(params), types[i]);
			}
		}
	
		BOOST_AUTO_TEST_CASE(OneWhitePieceAtH1_Success)
		{
			string pieceCodes = "PRKQBN";
			array<IPiece::Type, 6> types {{IPiece::Pawn, IPiece::Rook, IPiece::King, IPiece::Queen, IPiece::Bishop, IPiece::Knight}};
			for( auto i = 0 ; i < pieceCodes.length() ; i++)
			{
				Mocks::FENParserDelegate delegate;
				FENParser parser { delegate, "8/8/8/8/8/8/8/7" + string(1, pieceCodes[i]) + " w - - 0 1" };
				parser.BeginParsing();
				BOOST_CHECK_EQUAL(delegate.FENParserErrorParams.size(), 0);
				BOOST_REQUIRE_EQUAL(delegate.FENParserPieceParams.size(), 1);
				auto params = delegate.FENParserPieceParams[0];
				BOOST_CHECK_EQUAL(get<1>(params), Location::h1);
				BOOST_CHECK_EQUAL(get<2>(params), Player::White);
				BOOST_CHECK_EQUAL(get<3>(params), types[i]);
			}
		}

		BOOST_AUTO_TEST_CASE(DefaultChessSetup_Success)
		{
			Mocks::FENParserDelegate delegate;
			FENParser parser { delegate, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1" };
			parser.BeginParsing();
			BOOST_CHECK_EQUAL(delegate.FENParserErrorParams.size(), 0);
			BOOST_REQUIRE_EQUAL(delegate.FENParserPieceParams.size(), 32);
			auto begin = delegate.FENParserPieceParams.begin();
			auto end = delegate.FENParserPieceParams.end();

			IPiece::Type types[] = { IPiece::Rook, IPiece::Knight, IPiece::Bishop, IPiece::Queen, IPiece::King, IPiece::Bishop, IPiece::Knight, IPiece::Rook };
			for(int file = 1 ; file <= 8 ; file++)
				BOOST_CHECK_EQUAL(count(begin, end, make_tuple(&parser, Location(file, 8), Player::Black, types[file - 1])), 1);
			for(int file = 1 ; file <= 8 ; file++)
				BOOST_CHECK_EQUAL(count(begin, end, make_tuple(&parser, Location(file, 7), Player::Black, IPiece::Pawn)), 1);

			for(int file = 1 ; file <= 8 ; file++)
				BOOST_CHECK_EQUAL(count(begin, end, make_tuple(&parser, Location(file, 1), Player::White, types[file - 1])), 1);
			for(int file = 1 ; file <= 8 ; file++)
				BOOST_CHECK_EQUAL(count(begin, end, make_tuple(&parser, Location(file, 2), Player::White, IPiece::Pawn)), 1);
		}

	BOOST_AUTO_TEST_SUITE_END()
	
	BOOST_AUTO_TEST_SUITE(ActiveColor)

		BOOST_AUTO_TEST_CASE(InvalidLength_Fails)
		{
			Mocks::FENParserDelegate delegate;
			FENParser parser { delegate, "8/8/8/8/8/8/8/8 ww - - 0 1" };
			parser.BeginParsing();
			BOOST_REQUIRE_EQUAL(delegate.FENParserErrorParams.size(), 1);
			BOOST_CHECK_EQUAL(delegate.FENParserActiveColorParams.size(), 0);
			BOOST_CHECK(get<1>(delegate.FENParserErrorParams[0]).find("ACTIVE COLOR") != string::npos);
			BOOST_CHECK(get<1>(delegate.FENParserErrorParams[0]).find("length check") != string::npos);
		}

		BOOST_AUTO_TEST_CASE(InvalidCharacter_Fails)
		{
			Mocks::FENParserDelegate delegate;
			FENParser parser { delegate, "8/8/8/8/8/8/8/8 p - - 0 1" };
			parser.BeginParsing();
			BOOST_REQUIRE_EQUAL(delegate.FENParserErrorParams.size(), 1);
			BOOST_CHECK(get<1>(delegate.FENParserErrorParams[0]).find("ACTIVE COLOR") != string::npos);
			BOOST_CHECK(get<1>(delegate.FENParserErrorParams[0]).find("expected 'w' or 'b'") != string::npos);
		}

		BOOST_AUTO_TEST_CASE(LowercaseW_ParsesAsWhite)
		{
			Mocks::FENParserDelegate delegate;
			FENParser parser { delegate, "8/8/8/8/8/8/8/8 w - - 0 1" };
			parser.BeginParsing();
			BOOST_CHECK_EQUAL(delegate.FENParserErrorParams.size(), 0);
			BOOST_REQUIRE_EQUAL(delegate.FENParserActiveColorParams.size(), 1);
			BOOST_CHECK_EQUAL(get<1>(delegate.FENParserActiveColorParams[0]), Player::White);
		}

		BOOST_AUTO_TEST_CASE(UppercaseW_ParsesAsWhite)
		{
			Mocks::FENParserDelegate delegate;
			FENParser parser { delegate, "8/8/8/8/8/8/8/8 W - - 0 1" };
			parser.BeginParsing();
			BOOST_CHECK_EQUAL(delegate.FENParserErrorParams.size(), 0);
			BOOST_REQUIRE_EQUAL(delegate.FENParserActiveColorParams.size(), 1);
			BOOST_CHECK_EQUAL(get<1>(delegate.FENParserActiveColorParams[0]), Player::White);
		}

		BOOST_AUTO_TEST_CASE(LowercaseB_ParsesAsBlack)
		{
			Mocks::FENParserDelegate delegate;
			FENParser parser { delegate, "8/8/8/8/8/8/8/8 b - - 0 1" };
			parser.BeginParsing();
			BOOST_CHECK_EQUAL(delegate.FENParserErrorParams.size(), 0);
			BOOST_REQUIRE_EQUAL(delegate.FENParserActiveColorParams.size(), 1);
			BOOST_CHECK_EQUAL(get<1>(delegate.FENParserActiveColorParams[0]), Player::Black);
		}

		BOOST_AUTO_TEST_CASE(UppercaseB_ParsesAsBlack)
		{
			Mocks::FENParserDelegate delegate;
			FENParser parser { delegate, "8/8/8/8/8/8/8/8 B - - 0 1" };
			parser.BeginParsing();
			BOOST_CHECK_EQUAL(delegate.FENParserErrorParams.size(), 0);
			BOOST_REQUIRE_EQUAL(delegate.FENParserActiveColorParams.size(), 1);
			BOOST_CHECK_EQUAL(get<1>(delegate.FENParserActiveColorParams[0]), Player::Black);
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()