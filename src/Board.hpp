#pragma once

#include <iostream>
#include <vector>
#include "Character.hpp"

constexpr uint8_t BLACK_START = 0;
constexpr uint8_t BLACK_END = 3;
constexpr uint8_t WHITE_START = 5;
constexpr uint8_t WHITE_END = 8;

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
        removePiece(m.des);
        std::swap(getPiece(m.src), getPiece(m.des));
    }

    void removePiece(Coordinate c)
    {
        auto& piece = getPiece(c);
        if (!piece)
        {
            return;
        }

        removedPieces.push_back(std::move(piece));
    }

    void setPiece(Coordinate c, Color color, Rank rank)
    {
        getPiece(c) = std::make_unique<Piece>(color, rank);
    }

    std::vector<Move> getMoves(Coordinate origin)
    {
        std::vector<Move> pieceMoves {};
        auto& currentPiece = getPiece(origin);
        if (!currentPiece)
        {
            // std::cout << "\nNO PIECE ";
            return pieceMoves;
        }
        std::cout << "\n";
        if (WHITE == currentPiece->color)
        {
            if (NORMAL == currentPiece->rank)
            {
                addNormalMoves(pieceMoves, origin, origin.getTopRight(), currentPiece->color);
                addNormalMoves(pieceMoves, origin, origin.getTopLeft(), currentPiece->color);
            }
        }
        else
        {
            if (NORMAL == currentPiece->rank)
            {
                addNormalMoves(pieceMoves, origin, origin.getBottomRight(), currentPiece->color);
                addNormalMoves(pieceMoves, origin, origin.getBottomLeft(), currentPiece->color);
            }
        }

        return pieceMoves;
    }

    void addNormalMoves(std::vector<Move>& pieceMoves, Coordinate origin, Coordinate c, Color color)
    {
        if (c.isValid()) // check if not out of bounds
        {
            auto& targetPiece = getPiece(c);
            if (!targetPiece) // add if empty tile
            {
                pieceMoves.push_back(Move(origin, c));
            }

            if (targetPiece && color != targetPiece->color) // enemy color
            {
                if (TOP_LEFT == c.dir)
                {
                    auto move = Move(origin, c.getTopLeft());
                    pieceMoves.push_back(Move(c, c));
                }

                if (TOP_RIGHT == c.dir)
                {
                    auto move = Move(origin, c.getTopRight());
                    pieceMoves.push_back(Move(c, c));
                }

                if (BOTTOM_RIGHT == c.dir)
                {
                    auto move = Move(origin, c.getBottomRight());
                    pieceMoves.push_back(Move(c, c));
                }

                if (BOTTOM_LEFT == c.dir)
                {
                    auto move = Move(origin, c.getBottomLeft());
                    pieceMoves.push_back(Move(c, c));
                }
            }
        }
    }

    std::unique_ptr<Piece>& getPiece(Coordinate c)
    {
        return tiles[c.y][c.x]->pieceOnTop;
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
                tiles[y][x] = std::make_unique<Tile>(Coordinate(x, y));
                auto& tile = tiles[y][x];

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
                    setPiece(Coordinate(x, y), color, rank);

                    continue;
                }

                if (0 == (y % 2) && 1 == (x % 2))
                {
                    setPiece(Coordinate(x, y), color, rank);
                }
            }
        }
    }

    Character* image;
    std::vector<std::unique_ptr<Piece>> removedPieces;
    std::array<std::array<std::unique_ptr<Tile>, 8>, 8> tiles;
};
