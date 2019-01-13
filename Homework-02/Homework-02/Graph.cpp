#include "Graph.h"

#include <memory>
#include <algorithm>
#include <sstream>

using namespace Homework::ShortestPath;

// This implements Szudzik's pairing function to map `first` and `second` into a unique value of type `edge_key`.
// Doing so makes it possible to quickly find the edge of a given pair of nodes, if one exists.
// See: https://stackoverflow.com/questions/919612/mapping-two-integers-to-one-in-a-unique-and-deterministic-way
inline edge_key ComputeEdgeKey(node first, node second)
{
    // Always use the function that assumes `a` >= `b`
    // as the edges of the graph are undirected.
    const auto a = max(first, second);
    const auto b = min(first, second);

    return a * a + a + b;
}

inline bool ContainsKey(const edge_map& map, edge_key key)
{
    return map.find(key) != map.end();
}

inline void ThrowIfLoop(node first, node second)
{
    if (first == second)
    {
        stringstream errorMsg;
        errorMsg << "Attempted a loop for " << first;
        throw std::exception(errorMsg.str().c_str());
    }
}

inline void ThrowIfPastEnd(node last, node value)
{
    if (value <= last)
    {
        return;
    }

    stringstream errorMsg;
    errorMsg << value << " is past the last node, which is " << last;
    throw std::exception(errorMsg.str().c_str());
}

inline void ThrowIfEdgeExists(const edge_map& edgeMap, node first, node second)
{
    const auto edgeKey = ComputeEdgeKey(first, second);
    if (ContainsKey(edgeMap, edgeKey))
    {
        stringstream errorMsg;
        errorMsg << "Nodes (" << first << ", " << second << ") already have an edge" << endl;
        throw std::exception(errorMsg.str().c_str());
    }
}

Graph::Graph(unsigned int numVertices)
    : edgeMap()
    , nodeNeighbors()
{
    for (node iNode = 0; iNode < numVertices; iNode++)
    {
        nodeNeighbors.push_back(make_shared<node_set>());
    }
}

Graph::~Graph()
{
}

unsigned int Graph::GetNumVertices() const
{
    return nodeNeighbors.size();
}

unsigned int Graph::GetNumEdges() const
{
    return edgeMap.size();
}

bool Graph::AreAdjacent(node first, node second) const
{
    ThrowIfPastEnd(nodeNeighbors.size() - 1, first);
    ThrowIfPastEnd(nodeNeighbors.size() - 1, second);

    const auto edgeKey = ComputeEdgeKey(first, second);
    return ContainsKey(edgeMap, edgeKey);
}

const shared_ptr<const node_set> Graph::Neighbors(node node) const
{
    return nodeNeighbors[node];
}

void Graph::AddEdge(node first, node second, unsigned int value)
{
    ThrowIfLoop(first, second);
    ThrowIfPastEnd(nodeNeighbors.size() - 1, first);
    ThrowIfPastEnd(nodeNeighbors.size() - 1, second);
    ThrowIfEdgeExists(edgeMap, first, second);

    const auto edgeKey = ComputeEdgeKey(first, second);
    edgeMap.insert(make_pair(edgeKey, value));

    nodeNeighbors[first]->insert(second);
    nodeNeighbors[second]->insert(first);
}

unsigned int Graph::GetEdgeValue(node first, node second)
{
    const auto edgeKey = ComputeEdgeKey(first, second);
    if (!AreAdjacent(first, second))
    {
        stringstream errorMsg;
        errorMsg << "Nodes (" << first << ", " << second << ") are not connected" << endl;
        throw std::exception(errorMsg.str().c_str());
    }

    return edgeMap[edgeKey];
}