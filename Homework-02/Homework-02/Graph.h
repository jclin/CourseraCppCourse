#pragma once

#include "Utils.h"

namespace Homework { namespace ShortestPath
{
    using namespace std;
    using namespace Utils;

    // Represents an undirected graph.
    class Graph final
    {
    public:
        // Client functionality
        Graph(unsigned int numVertices = 1);
        ~Graph();

        unsigned int GetNumVertices() const;
        unsigned int GetNumEdges() const;
        bool AreAdjacent(node first, node second) const;
        const shared_ptr<const node_set> Neighbors(node node) const;

        void AddEdge(node first, node second, unsigned int value);
        unsigned int GetEdgeValue(node first, node second);

     private:
        edge_map edgeMap;
        node_neighbors_vector nodeNeighbors;

    public:
        // Iterator related functionality
        class NodeIterator final
        {
        public:
            using value_type = node;
            using reference = node;
            using iterator_category = std::input_iterator_tag;
            using pointer = node*;
            using difference_type = void;

            NodeIterator(Graph const* const owner, node currentNode)
                : owner(owner)
                , currentNode(currentNode)
            {
            }

        node operator*() const
        {
            return currentNode;
        }

        NodeIterator& operator++()
        {
            if (IsPastLastNode(currentNode))
            {
                throw std::exception("Incrementing a past-the-end iterator");
            }

            ++currentNode;
            return *this;
        }

        NodeIterator operator++(int)
        {
            NodeIterator temp(owner, currentNode);
            ++(*this);
            return temp;
        }

        friend bool operator==(NodeIterator const& left, NodeIterator const& right)
        {
            return left.owner == right.owner && left.currentNode == right.currentNode;
        }

        friend bool operator!=(NodeIterator const& left, NodeIterator const& right)
        {
            return !(left == right);
        }

        private:
            inline bool IsPastLastNode(node value)
            {
                return value >= owner->nodeNeighbors.size();
            }

            const Graph* const owner;
            node currentNode;
        };

        NodeIterator begin()
        {
            return NodeIterator(this, 0);
        }

        NodeIterator end()
        {
            return NodeIterator(this, nodeNeighbors.size());
        }
    };
} /* ShortestPath */ } /* Homework */