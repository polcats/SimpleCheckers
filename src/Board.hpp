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

    void const showBoard() const
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

    std::vector<Move> getMoves(Coordinate& origin)
    {
        std::vector<Move> pieceMoves {};
        auto const& currentPiece = getPiece(origin);
        if (!currentPiece)
        {
            return pieceMoves;
        }

        if (WHITE == currentPiece->color)
        {
            if (NORMAL == currentPiece->rank)
            {
                addNormalMoves(pieceMoves, origin, origin.getTopRight(), currentPiece->color);
                addNormalMoves(pieceMoves, origin, origin.getTopLeft(), currentPiece->color);
            }

            return pieceMoves;
        }

        if (NORMAL == currentPiece->rank)
        {
            addNormalMoves(pieceMoves, origin, origin.getBottomRight(), currentPiece->color);
            addNormalMoves(pieceMoves, origin, origin.getBottomLeft(), currentPiece->color);
        }

        return pieceMoves;
    }

    void addNormalMoves(std::vector<Move>& pieceMoves, Coordinate& origin, Coordinate destination, Color const color)
    {
        if (destination.isValid()) // check if not out of bounds
        {
            auto const& targetPiece = getPiece(destination);

            if (!targetPiece)  // if destination is an empty tile
            {
                pieceMoves.push_back(Move(origin, destination));
                return;
            }

            if (targetPiece && color != targetPiece->color) // if destination has an enemy piece
            {
                if (TOP_LEFT == destination.dir)
                {
                    auto const& nextMove = destination.getTopLeft();
                    if (nextMove.isValid())
                    {
                        pieceMoves.push_back(Move(origin, nextMove));
                    }
                }

                if (TOP_RIGHT == destination.dir)
                {
                    auto const& nextMove = destination.getTopRight();
                    if (nextMove.isValid())
                    {
                        pieceMoves.push_back(Move(origin, nextMove));
                    }
                }

                if (BOTTOM_RIGHT == destination.dir)
                {
                    auto const& nextMove = destination.getBottomRight();
                    if (nextMove.isValid())
                    {
                        pieceMoves.push_back(Move(origin, nextMove));
                    }
                }

                if (BOTTOM_LEFT == destination.dir)
                {
                    auto const& nextMove = destination.getBottomLeft();
                    if (nextMove.isValid())
                    {
                        pieceMoves.push_back(Move(origin, nextMove));
                    }
                }
            }
        }
    }

    std::unique_ptr<Piece>& getPiece(Coordinate& c)
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
                if (0 == (y % 2)) // even row
                {
                    if (0 == (x % 2)) // even col
                    {
                        tiles[y][x] = std::make_unique<Tile>(Coordinate(x, y), WHITE);
                        continue;
                    }

                    tiles[y][x] = std::make_unique<Tile>(Coordinate(x, y), BLACK);
                    continue;
                }

                if (0 == (x % 2))
                {
                    tiles[y][x] = std::make_unique<Tile>(Coordinate(x, y), BLACK);
                    continue;
                }

                tiles[y][x] = std::make_unique<Tile>(Coordinate(x, y), WHITE);
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
