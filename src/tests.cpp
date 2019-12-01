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

void testStaticMoves(Game& game)
{
	std::cout << "\n === testStaticMoves \n";

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

void testEliminationMoves(Game& game)
{
	std::cout << "\n\n === testEliminationMoves";
	game.reset();
	game.movePiece(Move(6, 5, 7, 4)); // w
	game.movePiece(Move(7, 2, 6, 3)); // b
	game.movePiece(Move(5, 2, 4, 3)); // b
	// game.showBoard();

	auto moves = game.getMoves(Coordinate(7, 4));
	uint8_t expectedSize = 1;
	uint8_t actualSize = moves.size();
	expectEQ("White_1_Elim_Move", expectedSize, actualSize);

	game.movePiece(Move(2, 5, 3, 4)); // w
	game.movePiece(Move(4, 5, 5, 4)); // w
	// game.showBoard();

	expectedSize = 2;
	actualSize = game.getMoves(Coordinate(4, 3)).size();
	expectEQ("Black_2_Elim_Moves", expectedSize, actualSize);

	// game.showBoard();
}

int main()
{
    Game game {};
	testStaticMoves(game);
	testEliminationMoves(game);
}