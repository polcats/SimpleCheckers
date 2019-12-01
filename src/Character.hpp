#pragma once

#include "enums.hpp"
#include "structs.hpp"

class Character
{
public:
    std::string const getTile(Color c) const
    {
        if (c)
        {
            return "\u2610";
        }

        return "\u25FC";
    }

    std::string const getImage(std::unique_ptr<Piece>& p) const
    {
        Rank& rank = p->rank;
        Color& color = p->color;

        switch (rank)
        {
            case NORMAL:
            {
                if (color)
                {
                    return "\u2688";
                }

                return "\u2686";
            }
            case UPGRADED:
            {
                if (color)
                {
                    return "\u2689";
                }

                return "\u2587";
            }
            default:
            {
                return "";
            }
        }
    }
};