#pragma once

#include <memory>
#include "enums.hpp"

struct Piece
{
    Piece(Color const color, Rank const rank) :
        color(color),
        rank(rank)
    {}

    Color color;
    Rank rank;
};

struct Coordinate
{
    Coordinate(int8_t const x, int8_t const y) :
        x(x),
        y(y)
    {}

    Coordinate(int8_t const x, int8_t const y, Direction const dir) :
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

    bool const operator==(Coordinate const& other) const
    {
        return (x == other.x && y == other.y);
    }
};

struct Move
{
    Move(uint8_t const sx, uint8_t const sy, uint8_t const dx, uint8_t const dy) :
        src(sx, sy),
        des(dx, dy)
    {}
    Move(Coordinate const& src, Coordinate const& des) :
        src(src),
        des(des)
    {}
    Coordinate src;
    Coordinate des;
};

struct Tile
{
    Tile(Coordinate const& c, Color const col) : coord(c), color(col) {}
    std::unique_ptr<Piece> pieceOnTop;
    Coordinate coord;
    Color color;
};