#pragma once

#include "Board.hpp"

class Game
{
public:
    Game() : board(&rank)
    {
    }

    void reset()
    {
        board.set();
    }

    void showBoard()
    {
        board.showBoard();
    }

    void movePiece(Move m)
    {
        board.movePiece(m);
    }

    void setPiece(Coordinate c, Color color, Rank rank)
    {
 		board.setPiece(c, color, rank);
    }

private:
	Color turn;
    Character rank;
    Board board;
};
