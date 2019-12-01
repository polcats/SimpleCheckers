#pragma once

#include <memory>
#include "enums.hpp"

struct Piece
{
    Piece(Color color, Rank rank) :
        color(color),
        rank(rank)
    {}

    Color color;
    Rank rank;
};

struct Coordinate
{
    Coordinate(int8_t x, int8_t y) :
        x(x),
        y(y)
    {}

    Coordinate(int8_t x, int8_t y, Direction dir) :
        x(x),
        y(y),
        dir(dir)
    {}

    int8_t x;
    int8_t y;
    Direction dir;

    Coordinate const getTopRight() const
    {
        return Coordinate(x + 1, y - 1, TOP_RIGHT);
    }

    Coordinate const getTopLeft() const
    {
        return Coordinate(x - 1, y - 1, TOP_LEFT);
    }

    Coordinate const getBottomRight() const
    {
        return Coordinate(x + 1, y + 1, BOTTOM_RIGHT);
    }

    Coordinate const getBottomLeft() const
    {
        return Coordinate(x - 1, y + 1, BOTTOM_LEFT);
    }

    bool const isValid() const
    {
        if (x > 7 || x == -1 || y > 7 || y == -1)
        {
            return false;
        }

        return true;
    }

    bool const operator==(const Coordinate& other) const
    {
        return (x == other.x && y == other.y);
    }
};

struct Move
{
    Move(uint8_t sx, uint8_t sy, uint8_t dx, uint8_t dy) :
        src(sx, sy),
        des(dx, dy)
    {}
    Move(Coordinate src, Coordinate des) :
        src(src),
        des(des)
    {}
    Coordinate src;
    Coordinate des;
};

struct Tile
{
    Tile(Coordinate c, Color col) : coord(c), color(col) {}
    std::unique_ptr<Piece> pieceOnTop;
    Coordinate coord;
    Color color;
};