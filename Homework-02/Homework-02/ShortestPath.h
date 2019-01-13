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

    // Represents the shortest path found from one node to another of a graph.
    class ShortestPath final
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

        // Returns the number of edges traveled.
        inline unsigned int Length() const
        {
            return pathTraveled.size();
        }

        // Returns the total distance of the path.
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