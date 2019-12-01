#pragma once

#include "Board.hpp"
#include <limits>

class Game
{
public:
    Game() :
        board(&rank),
        turn(WHITE)
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

    void setPiece(Coordinate const&c, Color const color, Rank const rank)
    {
 		board.setPiece(c, color, rank);
    }

    void switchTurn()
    {
        turn = (turn == BLACK ? WHITE : BLACK);
        std::cout << "Turn of : " << turn << "\n";
    }

    void start()
    {
        int k = 5;
        while (k--)
        {

            if (WHITE == turn)
            {
                Move m(0,0,0,0);
                std::string f;
                std::cout << "Enter move:";
                std::cin >> m.src.x >> m.src.y >> m.des.x >> m.des.y;
                movePiece(m);
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            switchTurn();
        }
    }

private:
	Color turn;
    Character rank;
    Board board;
};
