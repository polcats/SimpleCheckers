#include "Game.hpp"

int main()
{
    Game game {};
    game.showBoard();

    game.movePiece(Move(0, 0, 5, 5));


    std::cout << moves.size();

    return 0;
}