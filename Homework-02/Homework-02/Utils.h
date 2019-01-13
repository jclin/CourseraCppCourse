#pragma once
#include <memory>
#include <unordered_map>
#include <vector>
#include <set>

namespace Homework { namespace ShortestPath { namespace Utils
{
    using namespace std;

    typedef unsigned long edge_key;
    typedef unordered_map<edge_key, unsigned int> edge_map;

    typedef unsigned int node;
    typedef set<node> node_set;
    typedef shared_ptr<node_set> shared_nodes_set_ptr;
    typedef vector<shared_nodes_set_ptr> node_neighbors_vector;

    typedef unsigned long long distance_from_start;
    typedef std::pair<node, distance_from_start> node_and_weight;

    typedef unsigned long long distance_from_prev;
    typedef std::pair<node, distance_from_prev> node_and_edge_weight;
} /* Utils */ } /* ShortestPath */ } /* Homework */
