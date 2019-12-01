#include "Game.hpp"
#include <cassert>
#include <iostream>

template<typename Param>
void expectEQ(std::string testName, Param first, Param second)
{
	if (first == second)
	{
		std::cout << "Success: ";
	}
	else
	{
		std::cout << "Failure: ";
	}
	std::cout << first << " == " << second << " " << testName  << "";
}

void testMoves(Game& game)
{
    // Test get move for normal white piece
	auto moves = game.getMoves(Coordinate(7, 7));
	uint8_t expectedSize = 0;
	uint8_t actualSize = moves.size();
	expectEQ("No_Move_No_Piece", expectedSize, actualSize);

	expectedSize = 2;
	actualSize = game.getMoves(Coordinate(6, 5)).size();
	expectEQ("White_Normal_2_Moves", expectedSize, actualSize);

	expectedSize = 1;
	actualSize = game.getMoves(Coordinate(0, 5)).size();
	expectEQ("White_Normal_1_Move_Right", expectedSize, actualSize);

	expectedSize = 0;
	actualSize = game.getMoves(Coordinate(7, 6)).size();
	expectEQ("White_Normal_0_Move_Blocked", expectedSize, actualSize);

	expectedSize = 2;
	actualSize = game.getMoves(Coordinate(1, 2)).size();
	expectEQ("Black_Normal_2_Moves", expectedSize, actualSize);

	expectedSize = 1;
	actualSize = game.getMoves(Coordinate(7, 2)).size();
	expectEQ("Black_Normal_1_Move_Left", expectedSize, actualSize);

	expectedSize = 0;
	actualSize = game.getMoves(Coordinate(0, 7)).size();
	expectEQ("Black_Normal_0_Move_Blocked", expectedSize, actualSize);
}

int main()
{
    Game game {};
	testMoves(game);
    game.showBoard();
}