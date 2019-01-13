#pragma once

#include "Utils.h"

namespace Homework { namespace ShortestPath
{
    using namespace Homework::ShortestPath::Utils;

    class Edge final
    {
    public:
        Edge(node from, node to, distance_from_prev weight)
            : From(from)
            , To(to)
            , Weight(weight)
        {
        }

        ~Edge()
        {
        }

        const node From;
        const node To;
        const distance_from_prev Weight;
    };
} /* ShortestPath*/ } /* Homework */
