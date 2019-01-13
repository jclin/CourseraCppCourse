#include "Graph.h"
#include "ShortestPathCalculator.h"
#include "ShortestPath.h"
#include "Edge.h"

#include <vector>
#include <limits>
#include <queue>
#include <deque>

using namespace Homework::ShortestPath;

const distance_from_start Infinity = numeric_limits<distance_from_start>::max();

struct Compare
{
    bool operator()(const node_and_weight& left, const node_and_weight& right)
    {
        distance_from_start leftWeight;
        distance_from_start rightWeight;

        std::tie(std::ignore, leftWeight)  = left;
        std::tie(std::ignore, rightWeight) = right;

        return leftWeight > rightWeight;
    }
};

ShortestPathCalculator::ShortestPathCalculator(weak_ptr<Graph> graph)
    : weakGraph(graph)
{
}

ShortestPathCalculator::~ShortestPathCalculator()
{
}

// Attempts to findd the shortest path from `startNode` to `endNode`. This method
// implements Dijkstra's Algorithm using a min priority queue.
const shared_ptr<const ShortestPath> ShortestPathCalculator::Calculate(node startNode, node endNode)
{
    auto graph = weakGraph.lock();
    if (graph == nullptr)
    {
        throw std::exception("The graph is expired!");
    }

    vector<distance_from_start> distancesFromStart(graph->GetNumVertices());
    priority_queue<node_and_weight, vector<node_and_weight>, Compare> priorityQueue;
    vector<node_and_edge_weight> traveledFrom(graph->GetNumVertices());

    // Push the start node into the queue with
    // distance 0 to ensure it is visited first.
    distancesFromStart[startNode] = 0;
    priorityQueue.push(make_pair(startNode, distancesFromStart[startNode]));

    for (node currNode : *graph)
    {
        if (currNode != startNode)
        {
            distancesFromStart[currNode] = Infinity;
        }
    }

    while (!priorityQueue.empty())
    {
        node currNode;
        distance_from_start currWeight;
        tie(currNode, currWeight) = priorityQueue.top();
        priorityQueue.pop();

        if (currNode == endNode)
        {
            // The destination has been reached.
            break;
        }

        if (currWeight > distancesFromStart[currNode])
        {
            // This node+weight pair was deprecated by
            // a pair with a smaller weight cost.
            continue;
        }

        auto neighborNodes = graph->Neighbors(currNode);
        for (auto neighborNode : *neighborNodes)
        {
            const auto edgeValue = graph->GetEdgeValue(currNode, neighborNode);
            const auto proposedTotalNeighborDistance = distancesFromStart[currNode] + edgeValue;
            if (proposedTotalNeighborDistance >= distancesFromStart[neighborNode])
            {
                continue;
            }

            distancesFromStart[neighborNode] = proposedTotalNeighborDistance;
            priorityQueue.push(std::make_pair(neighborNode, proposedTotalNeighborDistance));
            traveledFrom[neighborNode] = std::make_pair(currNode, edgeValue);
        }
    }

    return Create(startNode, endNode, traveledFrom, distancesFromStart[endNode]);
}

shared_ptr<ShortestPath> ShortestPathCalculator::Create(const node startNode, const node endNode, const vector<node_and_edge_weight>& precedingNodes, const distance_from_start totalDistance)
{
    if (startNode == endNode)
    {
        // Didn't travel anywhere.
        return nullptr;
    }

    if (totalDistance == Infinity)
    {
        // Couldn't reach `endNode`.
        return nullptr;
    }

    // Walk backwards through `preceding` to build up `pathTraveled`,
    // which can be iterated in a forward fashion.
    deque<Edge> pathTraveled;
    pathTraveled.push_front(std::move(Edge(precedingNodes[endNode].first, endNode, precedingNodes[endNode].second)));

    auto nodeAndWeight = precedingNodes[endNode];
    while (nodeAndWeight.first != startNode)
    {
        // Grab the weight of the edge that connected
        // this node to the one that immediately preceded it.
        auto preceding = precedingNodes[nodeAndWeight.first];
        pathTraveled.push_front(std::move(Edge(preceding.first, nodeAndWeight.first, preceding.second)));

        nodeAndWeight = preceding;
    }

    return make_shared<ShortestPath>(pathTraveled, totalDistance);
}