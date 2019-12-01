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

void assertMoveSize(Game& game, Coordinate c, uint8_t expectedSize, std::string name)
{
	auto moves = game.getMoves(c);
	uint8_t actualSize = moves.size();
	expectEQ(name, expectedSize, actualSize);
}

void testStaticMoves(Game& game)
{
	std::cout << "\n === testStaticMoves \n";

	// Yea magic numbers!
	assertMoveSize(game, Coordinate(7, 7), 0, "No_Move_No_Piece");
	assertMoveSize(game, Coordinate(6, 5), 2, "White_Normal_2_Moves");
	assertMoveSize(game, Coordinate(0, 5), 1, "White_Normal_1_Move_Right");
	assertMoveSize(game, Coordinate(7, 6), 0, "White_Normal_0_Move_Blocked");
	assertMoveSize(game, Coordinate(1, 2), 2, "Black_Normal_2_Moves");
	assertMoveSize(game, Coordinate(7, 2), 1, "Black_Normal_1_Move_Left");
	assertMoveSize(game, Coordinate(0, 7), 0, "Black_Normal_0_Move_Blocked");
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