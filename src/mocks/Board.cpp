#include "mocks/Board.hpp"
#include "mocks/Piece.hpp"
#include <algorithm>

namespace Chess
{	
namespace Mocks
{
	using namespace std;

	Board::Board()
		:	GetPieceAtLocationReturnValue(new Mocks::Piece())
	{
		HasPieceAtLocationParams = new std::vector<Location>();
		GetPieceAtLocationParams = new std::vector<Location>();
		AddPieceAtLocationParams = new std::vector<std::tuple<std::shared_ptr<IPiece>, Location>>;
	}

	Board::~Board()
	{
		delete HasPieceAtLocationParams;
		delete GetPieceAtLocationParams;
		delete AddPieceAtLocationParams;
	}
	
	/* IBoard methods */

	bool Board::HasPieceAtLocation(const Location& location) const
	{
		HasPieceAtLocationParams->push_back(location);
		const auto& itr = HasPieceAtLocationReturnValue.find(location);
		if(itr != HasPieceAtLocationReturnValue.end())
			return itr->second;
		else
			return false;
	}


	IPiece& Board::GetPieceAtLocation(const Location& location) const
	{
		GetPieceAtLocationParams->push_back(Location(location));
		return *GetPieceAtLocationReturnValue;
	}

	int Board::AddPieceAtLocationCalls(const IPlayer::Color& color, const IPiece::Type& type, const Location& locationComp)
	{
		return count_if(
			AddPieceAtLocationParams->begin(),
			AddPieceAtLocationParams->end(), 
			[color, type, locationComp](tuple<shared_ptr<IPiece>, Location>& tuple)
			{
				IPiece& piece = *(get<0>(tuple));
				Location& location = get<1>(tuple); 
				return piece.GetPlayer().GetColor() == color && piece.GetType() == type && location == locationComp;
			});
	}

	void Board::AddPieceAtLocation(std::shared_ptr<IPiece> piece, const Location& location)
	{
		AddPieceAtLocationParams->push_back(make_tuple(piece, location));
	}

	void Board::MovePieceToLocation(std::shared_ptr<IPiece> piece, const Location& location)
	{

	}

	/* IObservableBoard methods */
	void Board::AddListener(IObservableBoardObservor &observor)
	{

	}

	void Board::AddListenerForSquare(IObservableBoardObservor &observor, const Location& location)
	{

	}
	
	void Board::RemoveListener(IObservableBoardObservor &observor)
	{

	}
	
	void Board::RemoveListenerForSquare(IObservableBoardObservor &observor, const Location& location)
	{

	}
}
}