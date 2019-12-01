#pragma once

#include "enums.hpp"
#include "structs.hpp"

#include <memory>
class Character
{
public:
    std::string const getTile(Color const& c) const
    {
        if (c)
        {
            return "[ ]"; //\u2610
        }

        return "[_]"; //\u25FC
    }

    std::string const getImage(std::unique_ptr<Piece> const& p) const
    {
        Rank& rank = p->rank;
        Color& color = p->color;

        switch (rank)
        {
            case NORMAL:
            {
                if (color)
                {
                    return "(1)"; //\u2688
                }

                return "{1}"; //\u2686
            }
            case UPGRADED:
            {
                if (color)
                {
                    return "(2)"; // \u2689
                }

                return "{2}"; // \u2587
            }
            default:
            {
                return "";
            }
        }
    }
};