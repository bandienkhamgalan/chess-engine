#include <array>
#include <tuple>
#include <string>
#include <stdexcept>
#include <algorithm>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "FENParser.hpp"
#include "mocks/FENParserDelegate.hpp"

using namespace std;
using namespace Chess;
using namespace Chess::IO;
using testing::_;
using testing::Eq;
using testing::AllOf;
using testing::NiceMock;

TEST(FENParser_SetDelegate, NullDelegate_ThrowsInvalidArgumentException)
{
	FENParser parser { "!@#$$^&*()!@#$$^&*()!@#$" };
	EXPECT_THROW(parser.SetDelegate(shared_ptr<IFENParserDelegate>(nullptr)), invalid_argument);
}

MATCHER_P(AddressEq, pointer, "")
{
	return &arg == pointer;
}

TEST(FENParser_SetDelegate, NonNullDelegate_SetsDelegate)
{
	auto delegate = make_shared<NiceMock<IO::Mocks::FENParserDelegate>>();
	FENParser parser { "pppppppp/pppppppp/pppppppp/pppppppp/pppppppp/pppppppp/pppppppp/pppppppp w - - 0 1" };
	EXPECT_CALL(*delegate, FENParserPiece(AddressEq(&parser), _, _, Eq(IPiece::Pawn)))
		.Times(64);

	parser.SetDelegate(delegate);
	parser.BeginParsing();
}

TEST(FENParser_PreValidation, NoDelegate_ThrowsRuntimeError)
{
	FENParser parser { "!@#$$^&*()!@#$$^&*()!@#$" };
	EXPECT_THROW(parser.BeginParsing(), runtime_error);
}

TEST(FENParser_PreValidation, ErrorsGiveSelfPointer)
{
	auto delegate = make_shared<NiceMock<IO::Mocks::FENParserDelegate>>();
	FENParser parser { "!@#$$^&*()!@#$$^&*()!@#$" , delegate };
	EXPECT_CALL(*delegate, FENParserError(AddressEq(&parser), _))
		.Times(1);
	parser.BeginParsing();	
}

MATCHER_P(Contains, string, "")
{
	return arg.find(string) != string::npos;
}

TEST(FENParser_PreValidation, LengthCheck)
{
	auto delegate = make_shared<NiceMock<IO::Mocks::FENParserDelegate>>();
	FENParser parser { "!@#$$^&*()!@#$$^&*()!@#$" , delegate };
	EXPECT_CALL(*delegate, FENParserError(AddressEq(&parser), Contains("length check")))
		.Times(1);
	parser.BeginParsing();
}

TEST(FENParser_PreValidation, CharacterSetCheck)
{
	auto delegate = make_shared<NiceMock<IO::Mocks::FENParserDelegate>>();
	FENParser parser { "!@#$$^&*()!@#$$^&*()!@#$^&*" , delegate };
	EXPECT_CALL(*delegate, FENParserError(AddressEq(&parser), Contains("character set check")))
		.Times(1);
	parser.BeginParsing();
}

TEST(FENParser_PreValidation, ComponentCountCheckTooFew)
{
	auto delegate = make_shared<NiceMock<IO::Mocks::FENParserDelegate>>();
	FENParser parser { "wwwww wwwww wwwww wwwww wwwww" , delegate };
	EXPECT_CALL(*delegate, FENParserError(AddressEq(&parser), Contains("component count check")))
		.Times(1);
	parser.BeginParsing();
}

TEST(FENParser_PreValidation, ComponentCountCheckTooMany)
{
	auto delegate = make_shared<NiceMock<IO::Mocks::FENParserDelegate>>();
	FENParser parser { "wwwww wwwww wwww wwwww wwwww wwwww wwwww" , delegate };
	EXPECT_CALL(*delegate, FENParserError(AddressEq(&parser), Contains("component count check")))
		.Times(1);
	parser.BeginParsing();
}

TEST(FENParser_PieceCodeParserAndLocationLogic_Invalid, InvalidDigitNine_Fails)
{
	auto delegate = make_shared<NiceMock<IO::Mocks::FENParserDelegate>>();
	FENParser parser { "8/8/8/8/8/8/8/9 w - - 0 1" , delegate };
	EXPECT_CALL(*delegate, FENParserError(AddressEq(&parser), Contains("only use numbers 1 through 8")))
		.Times(1);
	parser.BeginParsing();
}

TEST(FENParser_PieceCodeParserAndLocationLogic_Invalid, InvalidDigitZero_Fails)
{
	auto delegate = make_shared<NiceMock<IO::Mocks::FENParserDelegate>>();
	FENParser parser { "8/8/8/8/8/8/8/0 w - - 0 1" , delegate };
	EXPECT_CALL(*delegate, FENParserError(AddressEq(&parser), Contains("only use numbers 1 through 8")))
		.Times(1);
	parser.BeginParsing();
}

TEST(FENParser_PieceCodeParserAndLocationLogic_Invalid_TooManyFiles, TooManyFilesNumber_Fails)
{
	auto delegate = make_shared<NiceMock<IO::Mocks::FENParserDelegate>>();
	FENParser parser { "8/8/8/8/8/4p8/8/8 w - - 0 1" , delegate };
	EXPECT_CALL(*delegate, FENParserError(AddressEq(&parser), Contains("did not have 8 files")))
		.Times(1);
	parser.BeginParsing();
}

TEST(FENParser_PieceCodeParserAndLocationLogic_Invalid_TooManyFiles, TooManyFilesPiecesWithNumbersBeforePieces_Fails)
{
	auto delegate = make_shared<NiceMock<IO::Mocks::FENParserDelegate>>();
	FENParser parser { "8/8/8/8/8/pppp7/8/8 w - - 0 1" , delegate };
	EXPECT_CALL(*delegate, FENParserError(AddressEq(&parser), Contains("did not have 8 files")))
		.Times(1);
	parser.BeginParsing();
}

TEST(FENParser_PieceCodeParserAndLocationLogic_Invalid_TooManyFiles, TooManyFilesPiecesWithNumbersAfterPieces_Fails)
{
	auto delegate = make_shared<NiceMock<IO::Mocks::FENParserDelegate>>();
	FENParser parser { "8/8/8/8/8/7pppp/8/8 w - - 0 1" , delegate };
	EXPECT_CALL(*delegate, FENParserError(AddressEq(&parser), Contains("did not have 8 files")))
		.Times(1);
	parser.BeginParsing();
}

TEST(FENParser_PieceCodeParserAndLocationLogic_Invalid_TooManyFiles, TooManyFilesPieces_Fails)
{
	auto delegate = make_shared<NiceMock<IO::Mocks::FENParserDelegate>>();
	FENParser parser { "8/8/8/8/8/ppppppppppppp/8/8 w - - 0 1" , delegate };
	EXPECT_CALL(*delegate, FENParserError(AddressEq(&parser), Contains("did not have 8 files")))
		.Times(1);
	parser.BeginParsing();
}

TEST(FENParser_PieceCodeParserAndLocationLogic_Invalid_TooFewFiles, TooFewFilesEmpty_Fails)
{
	auto delegate = make_shared<NiceMock<IO::Mocks::FENParserDelegate>>();
	FENParser parser { "8/8/8/8/7p//8/8 w - - 0 1" , delegate };
	EXPECT_CALL(*delegate, FENParserError(AddressEq(&parser), Contains("did not have 8 files")))
		.Times(1);
	parser.BeginParsing();
}

TEST(FENParser_PieceCodeParserAndLocationLogic_Invalid_TooFewFiles, TooFewFilesNumber_Fails)
{
	auto delegate = make_shared<NiceMock<IO::Mocks::FENParserDelegate>>();
	FENParser parser { "8/8/8/8/8/7/8/8 w - - 0 1" , delegate };
	EXPECT_CALL(*delegate, FENParserError(AddressEq(&parser), Contains("did not have 8 files")))
		.Times(1);
	parser.BeginParsing();
}

TEST(FENParser_PieceCodeParserAndLocationLogic_Invalid_TooFewFiles, TooFewFilesPiecesWithNumbersBeforePieces_Fails)
{
	auto delegate = make_shared<NiceMock<IO::Mocks::FENParserDelegate>>();
	FENParser parser { "8/8/8/8/8/pppp1/8/8 w - - 0 1" , delegate };
	EXPECT_CALL(*delegate, FENParserError(AddressEq(&parser), Contains("did not have 8 files")))
		.Times(1);
	parser.BeginParsing();
}

TEST(FENParser_PieceCodeParserAndLocationLogic_Invalid_TooFewFiles, TooFewFilesPiecesWithNumbersAfterPieces_Fails)
{
	auto delegate = make_shared<NiceMock<IO::Mocks::FENParserDelegate>>();
	FENParser parser { "8/8/8/8/8/6p/8/8 w - - 0 1" , delegate };
	EXPECT_CALL(*delegate, FENParserError(AddressEq(&parser), Contains("did not have 8 files")))
		.Times(1);
	parser.BeginParsing();
}

TEST(FENParser_PieceCodeParserAndLocationLogic_Invalid_TooFewFiles, TooFewFilesPieces_Fails)
{
	auto delegate = make_shared<NiceMock<IO::Mocks::FENParserDelegate>>();
	FENParser parser { "8/8/8/8/8/pp/8/8 w - - 0 1" , delegate };
	EXPECT_CALL(*delegate, FENParserError(AddressEq(&parser), Contains("did not have 8 files")))
		.Times(1);
	parser.BeginParsing();
}

TEST(FENParser_PieceCodeParserAndLocationLogic_Invalid, TooManyRanks_Fails)
{
	auto delegate = make_shared<NiceMock<IO::Mocks::FENParserDelegate>>();
	FENParser parser { "8/8/8/8/8/8/8/8/8 w - - 0 1" , delegate };
	EXPECT_CALL(*delegate, FENParserError(AddressEq(&parser), Contains("unexpected contents after last rank")))
		.Times(1);
	parser.BeginParsing();
}

TEST(FENParser_PieceCodeParserAndLocationLogic_Invalid, TooFewRanks_Fails)
{
	auto delegate = make_shared<NiceMock<IO::Mocks::FENParserDelegate>>();
	FENParser parser { "pppppppp/8/8/8/8 w - - 0 1" , delegate };
	EXPECT_CALL(*delegate, FENParserError(AddressEq(&parser), Contains("did not have 8 ranks")))
		.Times(1);
	parser.BeginParsing();
}

TEST(FENParser_PieceCodeParserAndLocationLogic_Valid, NoPieces_Success)
{
	auto delegate = make_shared<NiceMock<IO::Mocks::FENParserDelegate>>();
	FENParser parser { "8/8/8/8/8/8/8/8 w - - 0 1" , delegate };
	EXPECT_CALL(*delegate, FENParserError(_, _))
		.Times(0);
	EXPECT_CALL(*delegate, FENParserPiece(_, _, _, _))
		.Times(0);
	parser.BeginParsing();
}

TEST(FENParser_PieceCodeParserAndLocationLogic_Valid, FullPieces_Success)
{
	auto delegate = make_shared<NiceMock<IO::Mocks::FENParserDelegate>>();
	FENParser parser { "pppppppp/pppppppp/pppppppp/pppppppp/pppppppp/pppppppp/pppppppp/pppppppp w - - 0 1" , delegate };
	EXPECT_CALL(*delegate, FENParserError(_, _))
		.Times(0);
	EXPECT_CALL(*delegate, FENParserPiece(AddressEq(&parser), _, Eq(IPlayer::Black), Eq(IPiece::Pawn)))
		.Times(64);
	parser.BeginParsing();
}

TEST(FENParser_PieceCodeParserAndLocationLogic_Valid, OneWhitePieceAtA8_Success)
{
	string pieceCodes = "PRKQBN";
	array<IPiece::Type, 6> types {{IPiece::Pawn, IPiece::Rook, IPiece::King, IPiece::Queen, IPiece::Bishop, IPiece::Knight}};
	for(auto i = 0 ; i < pieceCodes.length() ; i++)
	{
		auto delegate = make_shared<NiceMock<IO::Mocks::FENParserDelegate>>();
		FENParser parser { string(1, pieceCodes[i]) + "7/8/8/8/8/8/8/8 w - - 0 1" , delegate };
		EXPECT_CALL(*delegate, FENParserError(_, _))
			.Times(0);
		EXPECT_CALL(*delegate, FENParserPiece(AddressEq(&parser), Eq(Location::a8), Eq(IPlayer::White), Eq(types[i])))
			.Times(1);
		parser.BeginParsing();
	}
}

TEST(FENParser_PieceCodeParserAndLocationLogic_Valid, OneBlackPieceAtE5_Success)
{
	string pieceCodes = "prkqbn";
	array<IPiece::Type, 6> types {{IPiece::Pawn, IPiece::Rook, IPiece::King, IPiece::Queen, IPiece::Bishop, IPiece::Knight}};
	for(auto i = 0 ; i < pieceCodes.length() ; i++)
	{
		auto delegate = make_shared<NiceMock<IO::Mocks::FENParserDelegate>>();
		FENParser parser { "8/8/8/4" + string(1, pieceCodes[i]) + "3/8/8/8/8 w - - 0 1" , delegate };
		EXPECT_CALL(*delegate, FENParserError(_, _))
			.Times(0);
		EXPECT_CALL(*delegate, FENParserPiece(AddressEq(&parser), Eq(Location::e5), Eq(IPlayer::Black), Eq(types[i])))
			.Times(1);
		parser.BeginParsing();
	}
}

TEST(FENParser_PieceCodeParserAndLocationLogic_Valid, OneWhitePieceAtH1_Success)
{
	string pieceCodes = "PRKQBN";
	array<IPiece::Type, 6> types {{IPiece::Pawn, IPiece::Rook, IPiece::King, IPiece::Queen, IPiece::Bishop, IPiece::Knight}};
	for(auto i = 0 ; i < pieceCodes.length() ; i++)
	{
		auto delegate = make_shared<NiceMock<IO::Mocks::FENParserDelegate>>();
		FENParser parser { "8/8/8/8/8/8/8/7" + string(1, pieceCodes[i]) + " w - - 0 1" , delegate };
		EXPECT_CALL(*delegate, FENParserError(_, _))
			.Times(0);
		EXPECT_CALL(*delegate, FENParserPiece(AddressEq(&parser), Eq(Location::h1), Eq(IPlayer::White), Eq(types[i])))
			.Times(1);
		parser.BeginParsing();
	}
}

TEST(FENParser_PieceCodeParserAndLocationLogic_Valid, DefaultChessSetup_Success)
{
	auto delegate = make_shared<NiceMock<IO::Mocks::FENParserDelegate>>();
	FENParser parser { "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1" , delegate };
	EXPECT_CALL(*delegate, FENParserError(_, _))
		.Times(0);
	IPiece::Type types[] = { IPiece::Rook, IPiece::Knight, IPiece::Bishop, IPiece::Queen, IPiece::King, IPiece::Bishop, IPiece::Knight, IPiece::Rook };
	for(int file = 1 ; file <= 8 ; file++)
	{
		EXPECT_CALL(*delegate, FENParserPiece(AddressEq(&parser), Eq(Location(file, 8)), Eq(IPlayer::Black), Eq(types[file - 1])))
			.Times(1);
		EXPECT_CALL(*delegate, FENParserPiece(AddressEq(&parser), Eq(Location(file, 7)), Eq(IPlayer::Black), Eq(IPiece::Pawn)))
			.Times(1); 

		for(int rank = 6 ; rank >= 3 ; rank--)
			EXPECT_CALL(*delegate, FENParserPiece(_, Eq(Location(file, rank)), _, _))
				.Times(0);
		
		EXPECT_CALL(*delegate, FENParserPiece(AddressEq(&parser), Eq(Location(file, 2)), Eq(IPlayer::White), Eq(IPiece::Pawn)))
			.Times(1); 
		EXPECT_CALL(*delegate, FENParserPiece(AddressEq(&parser), Eq(Location(file, 1)), Eq(IPlayer::White), Eq(types[file - 1])))
			.Times(1); 
	}
	
	parser.BeginParsing();
}

TEST(FENParser_ActiveColor, InvalidLength_Fails)
{
	auto delegate = make_shared<NiceMock<IO::Mocks::FENParserDelegate>>();
	FENParser parser { "8/8/8/8/8/8/8/8 ww - - 0 1" , delegate };
	EXPECT_CALL(*delegate, FENParserError(AddressEq(&parser), AllOf(Contains("ACTIVE COLOR"), Contains("length check"))))
		.Times(1);
	
	parser.BeginParsing();
}

TEST(FENParser_ActiveColor, InvalidCharacter_Fails)
{
	auto delegate = make_shared<NiceMock<IO::Mocks::FENParserDelegate>>();
	FENParser parser { "8/8/8/8/8/8/8/8 p - - 0 1" , delegate };
	EXPECT_CALL(*delegate, FENParserError(AddressEq(&parser), AllOf(Contains("ACTIVE COLOR"), Contains("expected 'w' or 'b'"))))
		.Times(1);
	
	parser.BeginParsing();
}

TEST(FENParser_ActiveColor, Success)
{
	string colorCodes = "wWbB";
	IPlayer::Color colors[] = { IPlayer::White, IPlayer::White, IPlayer::Black, IPlayer::Black };
	for(int index = 0 ; index < 4 ; index++)
	{
		auto delegate = make_shared<NiceMock<IO::Mocks::FENParserDelegate>>();
		FENParser parser { "8/8/8/8/8/8/8/8 " + string(1, colorCodes[index]) + " - - 0 1" , delegate };
		EXPECT_CALL(*delegate, FENParserError(_, _))
			.Times(0);
		EXPECT_CALL(*delegate, FENParserActiveColor(AddressEq(&parser), Eq(colors[index])))
			.Times(1);
	
		parser.BeginParsing();
	}
}