#pragma once

#include <memory>
#include "enums.hpp"

struct Piece
{
    Piece(Color color, Rank rank) : color(color), rank(rank) {}
    Color color;
    Rank rank;
};

struct Coordinate
{
    Coordinate(uint8_t x, uint8_t y) : x(x), y(y) {}
    int8_t x;
    int8_t y;
};

struct Move
{
    Move(uint8_t sx, uint8_t sy, uint8_t dx, uint8_t dy) : src(sx, sy), des(dx, dy)
    {}
    Move(Coordinate src, Coordinate des) : src(src), des(des)
    {}
    Coordinate src;
    Coordinate des;
};

struct Tile
{
    Tile(Coordinate c) : coord(c) {}
    std::unique_ptr<Piece> pieceOnTop;
    Coordinate coord;
    Color color;
};