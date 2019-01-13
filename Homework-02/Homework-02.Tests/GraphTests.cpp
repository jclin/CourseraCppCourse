#pragma once
#include "pch.h"
#include "../Homework-02/Graph.h"

namespace Homework { namespace Tests
{
    using namespace testing;
    using namespace Homework::ShortestPath;

    class GraphTest final : Test
    {
    protected:
        GraphTest()
        {
        }

        ~GraphTest()
        {
        }
    };

    TEST(GraphTest, GetNumVertices)
    {
        Graph graph(10);
        const auto vertices = graph.GetNumVertices();

        ASSERT_EQ(vertices, 10);
    }

    TEST(GraphTest, GetNumEdges)
    {
        Graph graph(10);

        ASSERT_EQ(graph.GetNumEdges(), 0);

        graph.AddEdge(0, 9, 100);
        graph.AddEdge(0, 8, 200);

        ASSERT_EQ(graph.GetNumEdges(), 2);
    }

    TEST(GraphTest, AreAdjacent)
    {
        Graph graph(3);

        graph.AddEdge(0, 1, 100);
        graph.AddEdge(1, 2, 200);

        ASSERT_TRUE(graph.AreAdjacent(0, 1));
        ASSERT_TRUE(graph.AreAdjacent(1, 0));

        ASSERT_TRUE(graph.AreAdjacent(1, 2));
        ASSERT_TRUE(graph.AreAdjacent(2, 1));

        ASSERT_FALSE(graph.AreAdjacent(0, 2));
        ASSERT_FALSE(graph.AreAdjacent(2, 0));
    }

    TEST(GraphTest, AreAdjacentInvalidNodes)
    {
        Graph graph(3);

        graph.AddEdge(0, 1, 100);
        graph.AddEdge(1, 2, 200);

        ASSERT_THROW(graph.AreAdjacent(0, 3), std::exception);
        ASSERT_THROW(graph.AreAdjacent(3, 0), std::exception);
    }

    TEST(GraphTest, Neighbors)
    {
        Graph graph(3);

        graph.AddEdge(0, 1, 100);
        graph.AddEdge(1, 2, 200);

        auto neighbors = graph.Neighbors(0);
        ASSERT_EQ(neighbors->size(), 1);
        ASSERT_EQ(*(neighbors->begin()), 1);

        neighbors = graph.Neighbors(1);
        ASSERT_EQ(neighbors->size(), 2);
        ASSERT_EQ(*(neighbors->begin()), 0);
        ASSERT_EQ(*(neighbors->find(2)), 2);

        neighbors = graph.Neighbors(2);
        ASSERT_EQ(neighbors->size(), 1);
        ASSERT_EQ(*(neighbors->begin()), 1);
    }

    TEST(GraphTest, AddLoop)
    {
        Graph graph(1);

        ASSERT_THROW(graph.AddEdge(1, 1, 100), std::exception);
    }

    TEST(GraphTest, AddEdgeMultipleTimes)
    {
        Graph graph(2);

        ASSERT_NO_THROW(graph.AddEdge(0, 1, 100));
        ASSERT_THROW(graph.AddEdge(0, 1, 200), std::exception);
    }

    TEST(GraphTest, AddEdgeToInvalidNode)
    {
        Graph graph(2);

        ASSERT_THROW(graph.AddEdge(0, graph.GetNumVertices(), 100), std::exception);
        ASSERT_THROW(graph.AddEdge(graph.GetNumVertices(), 0, 100), std::exception);
    }

    TEST(GraphTest, GetEdgeValue)
    {
        Graph graph(3);

        graph.AddEdge(0, 1, 100);
        graph.AddEdge(1, 2, 200);

        ASSERT_EQ(graph.GetEdgeValue(0, 1), 100);
        ASSERT_EQ(graph.GetEdgeValue(1, 0), 100);

        ASSERT_EQ(graph.GetEdgeValue(1, 2), 200);
        ASSERT_EQ(graph.GetEdgeValue(2, 1), 200);
    }

    TEST(GraphTest, GetEdgeValueInvalidNode)
    {
        Graph graph(3);

        graph.AddEdge(0, 1, 100);
        graph.AddEdge(1, 2, 200);

        ASSERT_THROW(graph.GetEdgeValue(0, 3), std::exception);
        ASSERT_THROW(graph.GetEdgeValue(3, 0), std::exception);
    }

    TEST(GraphTest, GetNonExistentEdgeValue)
    {
        Graph graph(3);

        graph.AddEdge(0, 1, 100);
        graph.AddEdge(1, 2, 200);

        ASSERT_THROW(graph.GetEdgeValue(0, 2), std::exception);
        ASSERT_THROW(graph.GetEdgeValue(2, 0), std::exception);
    }
} /* Tests */ } /* Homework */
