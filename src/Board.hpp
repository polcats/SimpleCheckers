#pragma once

#include <memory>
#include "Character.hpp"

class Board
{
public:
    Board(Character* image) : image(image), tiles()
    {
    	set();
    }

    ~Board()
    {
    	clear();
    }

    void set()
    {
    	clear();
        initBoard();
		setPieces(BLACK_START, BLACK_END, BLACK, NORMAL);
        setPieces(WHITE_START, WHITE_END, WHITE, NORMAL);
    }

    void showBoard()
    {
        std::cout << "\n";

        for (auto y = 0u; y < 8; ++y)
        {
            for (auto x = 0u; x < 8; ++x)
            {

                if (tiles[y][x]->pieceOnTop)
                {
                    std::cout << image->getImage(tiles[y][x]->pieceOnTop) << " ";
                }
                else
                {
					std::cout << image->getTile(tiles[y][x]->color) << " ";
                }

            	if (7 == x)
            	{
                    std::cout << y;
            	}
            }
        	std::cout << "\n";
        }
    }

    void movePiece(Move m)
    {
        if (tiles[m.des.x][m.des.y]->pieceOnTop)
        {
            removePiece(m.des);
        }

        std::swap(tiles[m.src.x][m.src.y]->pieceOnTop, tiles[m.des.x][m.des.y]->pieceOnTop);
    }

    void removePiece(Coordinate c)
    {
        auto& piece = tiles[c.x][c.y]->pieceOnTop;
        removedPieces.push_back(std::move(piece));
    }

    void setPiece(Coordinate c, Color color, Rank rank)
    {
        tiles[c.x][c.y]->pieceOnTop = std::make_unique<Piece>(color, rank);
    }


private:
    void clear()
    {
    	tiles = {};
    	removedPieces.clear();
    }

    void initBoard()
    {
        for (auto x = 0u; x < 8; ++x)
        {
            for (auto y = 0u; y < 8; ++y)
            {
                tiles[x][y] = std::make_unique<Tile>(Coordinate(x, y));
                auto& tile = tiles[x][y];

                if (0 == (y % 2)) // even row
                {
                    if (0 == (x % 2)) // even col
                    {
                        tile->color = WHITE;

                        continue;
                    }

                    tile->color = BLACK;

                    continue;
                }

                if (0 == (x % 2))
                {
                    tile->color = BLACK;

                    continue;
                }

                tile->color = WHITE;
            }
        }
    }

    void setPieces(const uint8_t ymin, const uint8_t ymax, Color color, Rank rank)
    {
        for (auto y = ymin; y < ymax; ++y)
        {
            for (auto x = 0u; x < 8; ++x)
            {
                if (1 == (y % 2) && 0 == (x %2 ))
                {
                    setPiece(Coordinate(y, x), color, rank);

                    continue;
                }

                if (0 == (y % 2) && 1 == (x % 2))
                {
                    setPiece(Coordinate(y, x), color, rank);
                }
            }
        }
    }

    Character* image;
    std::vector<std::unique_ptr<Piece>> removedPieces;
    std::array<std::array<std::unique_ptr<Tile>, 8>, 8> tiles;
};
