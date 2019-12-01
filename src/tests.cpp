#include "Game.hpp"
#include <cassert>
#include <iostream>

template<typename Param>
void expectEQ(std::string testName, Param first, Param second)
{
	// std::cout << "\n";
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
	auto moves = game.getMoves(Coordinate(6, 5));
	uint8_t expectedSize = 2;
	uint8_t actualSize = moves.size();
	expectEQ("White_Normal_2_Moves", expectedSize, actualSize);

	expectedSize = 0;
	actualSize = game.getMoves(Coordinate(7, 6)).size();
	expectEQ("White_Normal_0_Move_Blocked", expectedSize, actualSize);

	expectedSize = 1;
	actualSize = game.getMoves(Coordinate(0, 5)).size();
	expectEQ("White_Normal_1_Move_Right", expectedSize, actualSize);
}

int main()
{
    Game game {};
    game.showBoard();


	testMoves(game);
}