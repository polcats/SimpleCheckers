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

    void const showBoard() const
    {
        board.showBoard();
    }

    void movePiece(Move const& m)
    {
        board.movePiece(m);
    }

    void removePiece(Coordinate const& c)
    {
        board.removePiece(c);
    }

    std::vector<Move> const getMoves(Coordinate const& c)
    {
        return board.getMoves(c);
    }

    void setPiece(Coordinate const&c, Color const& color, Rank const& rank)
    {
 		board.setPiece(c, color, rank);
    }

private:
	Color turn;
    Character rank;
    Board board;
};
