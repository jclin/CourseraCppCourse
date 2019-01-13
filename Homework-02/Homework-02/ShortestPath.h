#pragma once

#include "Utils.h"
#include "Graph.h"
#include "Edge.h"

#include <deque>
#include <vector>
#include <string>

namespace Homework { namespace ShortestPath
{
    using namespace std;
    using namespace Homework::ShortestPath::Utils;

    class ShortestPath final : deque<node_and_edge_weight>
    {
    public:
        // Client functionality
        ShortestPath(deque<Edge>& pathTraveled, distance_from_start totalDistance)
            : pathTraveled(std::move(pathTraveled))
            , totalDistance(totalDistance)
        {
        }

        ~ShortestPath()
        {
        }

        inline unsigned int Length() const
        {
            return pathTraveled.size();
        }

        inline distance_from_start TotalDistance() const
        {
            return totalDistance;
        }

        std::string ToString() const;

    private:
        const deque<Edge> pathTraveled;
        const distance_from_start totalDistance;

    public:
        // Iterator related
        using const_iterator = deque<Edge>::const_iterator;

        const_iterator begin() const
        {
            return pathTraveled.begin();
        }

        const_iterator end() const
        {
            return pathTraveled.end();
        }

        const_iterator cbegin() const
        {
            return pathTraveled.cbegin();
        }

        const_iterator cend() const
        {
            return pathTraveled.cend();
        }
    };
} /* ShortestPath */ } /* Homework */