#pragma once
#include "pch.h"

#include "../Homework-02/Utils.h"
#include "../Homework-02/ShortestPath.h"
#include "../Homework-02/ShortestPathCalculator.h"
#include "../Homework-02/Graph.h"

#include <iostream>
#include <iomanip>
#include <memory>
#include <random>
#include <vector>

using namespace std;
using namespace Homework::ShortestPath;

typedef unsigned int edge_weight;

static default_random_engine Generator;

node PickNodeIndex(unsigned int numNodes)
{
    uniform_int_distribution<unsigned int> distribution(0, numNodes - 1);
    return distribution(Generator);
}

edge_weight PickEdgeWeight(std::pair<edge_weight, edge_weight> edgeWeightRange)
{
    uniform_int_distribution<edge_weight> distribution(edgeWeightRange.first, edgeWeightRange.second);
    return distribution(Generator);
}

shared_ptr<Graph> BuildGraph(unsigned int numNodes, double density, std::pair<edge_weight, edge_weight> edgeWeightRange)
{
    // NOTE: I originally populated the edges by calculating the probability
    // of an edge based on `density` as discussed in the lectures and reading
    // modules. This was implemented using `uniform_int_distribution`.
    // However, for reasons unknown to me, many more edges were added
    // than intended.
    //
    // For example, in a graph of 50 nodes with density 0.2, there should be
    // 245 edges out of a possible 1,225. Adding an edge based on a probability
    // was yielding up to ~470 edges for me.
    //
    // This hack is a workaround. It always adds the number of possible edges
    // based on `density`, but randomly picks potential node-pairs until
    // no more edges can be added. It is potentially very slow as node-pairs
    // can be picked multiple times.

    shared_ptr<Graph> graph = make_shared<Graph>(numNodes);

    // See: https://stackoverflow.com/questions/5058406/what-is-the-maximum-number-of-edges-in-a-directed-graph-with-n-nodes
    const auto maxPossibleEdges = (numNodes * (numNodes - 1)) / 2;
    auto numEdges = density * maxPossibleEdges;

    vector<vector<bool>> edgeMatrix(numNodes, vector<bool>(numNodes, false));
    while (numEdges > 0)
    {
        const node iFirst  = PickNodeIndex(numNodes);
        const node iSecond = PickNodeIndex(numNodes);

        if (iFirst == iSecond)
        {
            // Disallow loops
            edgeMatrix[iFirst][iSecond] = true;
            continue;
        }

        if (edgeMatrix[iFirst][iSecond])
        {
            // This pair has been visited
            continue;
        }

        const auto edgeWeight = PickEdgeWeight(edgeWeightRange);
        graph->AddEdge(iFirst, iSecond, edgeWeight);

        // Mark this pair as visited
        edgeMatrix[iFirst][iSecond] = true;
        edgeMatrix[iSecond][iFirst] = true;

        numEdges--;
    }

    return std::move(graph);
}

inline double Average(const vector<shared_ptr<const ShortestPath>>& shortestPaths)
{
    distance_from_start totalDistances = 0;
    for (auto shortestPath : shortestPaths)
    {
        totalDistances += shortestPath->TotalDistance();
    }

    return totalDistances / static_cast<double>(shortestPaths.size());
}

vector<shared_ptr<const ShortestPath>> FindShortestPaths(unsigned int numNodes, double density, std::pair<edge_weight, edge_weight> edgeWeightRange)
{
    auto graph = BuildGraph(numNodes, density, edgeWeightRange);

    vector<shared_ptr<const ShortestPath>> shortestPaths;

    const node startNode = 0;
    for (node endNode = startNode + 1; endNode < numNodes; endNode++)
    {
        ShortestPathCalculator calculator(graph);
        auto shortestPath = calculator.Calculate(startNode, endNode);
        if (shortestPath == nullptr)
        {
            continue;
        }

        shortestPaths.push_back(shortestPath);
    }

    return std::move(shortestPaths);
}

void PrintStats(unsigned int numNodes, double density, std::pair<edge_weight, edge_weight> edgeWeightRange, const vector<shared_ptr<const ShortestPath>>& shortestPaths)
{
    cout << std::fixed;
    cout << std::setprecision(2);

    cout << std::left  << std::setw(20) << "SUMMARY:" << endl;
    cout << std::left  << std::setw(20) << "Nodes:"
         << std::right << std::setw(10) << numNodes << endl;

    cout << std::left  << std::setw(20) << "Density:"
         << std::right << std::setw(10) << density << endl;

    cout << std::left  << std::setw(20) << "Edge weights:"
         << std::right << std::setw(7) << edgeWeightRange.first << "-" << edgeWeightRange.second << endl;

    cout << std::left  << std::setw(20) << "Avg path dist:"
         << std::right << std::setw(10) << Average(shortestPaths) << endl;

    cout << endl;

    // Uncomment the following lines to see the actual
    // travel path from the start to the end.
    //for (const auto shortestPath : shortestPaths)
    //{
    //    cout << shortestPath->ToString();
    //}

    cout << std::left << "==============================" << endl;
    cout << endl;
}

int main()
{
    const auto numNodes = 50;
    const auto edgeWeightRange = std::make_pair<edge_weight>(1, 10);

    auto shortestPaths = FindShortestPaths(numNodes, 0.2, edgeWeightRange);
    PrintStats(numNodes, 0.2, edgeWeightRange, shortestPaths);

    shortestPaths = FindShortestPaths(numNodes, 0.4, edgeWeightRange);
    PrintStats(numNodes, 0.4, edgeWeightRange, shortestPaths);

    return 0;
}
