#pragma once
#include <memory>
#include <queue>
#include "Utils.h"

namespace Homework { namespace ShortestPath
{
    using namespace std;
    using namespace Homework::ShortestPath::Utils;

    class Graph;
    class ShortestPath;

    // Calculates the shortest path from one node to another for a specified `graph`.
    class ShortestPathCalculator final
    {
    public:
        ShortestPathCalculator(weak_ptr<Graph> graph);
        ~ShortestPathCalculator();

        const shared_ptr<const ShortestPath> Calculate(node startNode, node endNode);

    private:
        shared_ptr<ShortestPath> Create(const node startNode, const node endNode, const vector<node_and_edge_weight>& precedingNodes, const distance_from_start totalDistance);

        const weak_ptr<Graph> weakGraph;
    };
} /* ShortestPath */ } /* Homework */
