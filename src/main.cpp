#include "ISquareFactory.hpp"
#include "SimpleSquareFactory.hpp"
#include "Board.hpp"
#include <iostream>

using namespace std;
using namespace Chess;

int main(int argc, char** argv)
{
	unique_ptr<ISquareFactory> squareFactory { new SimpleSquareFactory() };
	unique_ptr<Board> board { new Board(*squareFactory) };
}