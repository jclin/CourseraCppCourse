#pragma once
#include "pch.h"
#include <memory>
#include "../Homework-02/ShortestPathCalculator.h"
#include "../Homework-02/ShortestPath.h"
#include "../Homework-02/Graph.h"

namespace Homework { namespace Tests
{
    using namespace testing;
    using namespace Homework::ShortestPath;

    class ShortestPathCalculatorTest final : Test
    {
    protected:
        ShortestPathCalculatorTest()
        {
        }

        ~ShortestPathCalculatorTest()
        {
        }
    };

    TEST(ShortestPathCalculatorTest, StartEqualsEnd)
    {
        shared_ptr<Graph> graph = make_shared<Graph>(1);

        ShortestPathCalculator calculator(graph);
        auto shortestPath = calculator.Calculate(0, 0);

        ASSERT_EQ(shortestPath, nullptr);
    }

    TEST(ShortestPathCalculatorTest, Unconnected)
    {
        shared_ptr<Graph> graph = make_shared<Graph>(10);

        ShortestPathCalculator calculator(graph);
        auto shortestPath = calculator.Calculate(0, 5);

        ASSERT_EQ(shortestPath, nullptr);
    }

    TEST(ShortestPathCalculatorTest, NoPath)
    {
        shared_ptr<Graph> graph = make_shared<Graph>(5);

        graph->AddEdge(0, 1, 2); // Edge: (0, 1) -> Weight: 2
        graph->AddEdge(0, 2, 4); // Edge: (0, 2) -> Weight: 4
        graph->AddEdge(0, 3, 3); // Edge: (0, 3) -> Weight: 3
        graph->AddEdge(1, 2, 1); // Edge: (1, 2) -> Weight: 1

        ShortestPathCalculator calculator(graph);
        auto shortestPath = calculator.Calculate(0, 4);

        ASSERT_EQ(shortestPath, nullptr);
    }

    TEST(ShortestPathCalculatorTest, MultiplePaths)
    {
        const auto expectedTotalDistance = 3llu;

        shared_ptr<Graph> graph = make_shared<Graph>(5);

        graph->AddEdge(0, 1, 2); // Edge: (0, 1) -> Weight: 2
        graph->AddEdge(0, 2, 4); // Edge: (0, 2) -> Weight: 4
        graph->AddEdge(0, 3, 3); // Edge: (0, 3) -> Weight: 3
        graph->AddEdge(1, 2, 1); // Edge: (1, 2) -> Weight: 1

        ShortestPathCalculator calculator(graph);
        auto shortestPath = calculator.Calculate(0, 2);

        ASSERT_NE(shortestPath, nullptr);
        ASSERT_EQ(shortestPath->TotalDistance(), expectedTotalDistance);

        ASSERT_EQ(shortestPath->Length(), 2);

        auto totalDistance = 0llu;

        // TODO: Get GoogleMocks linked to take advantage of container matching
        auto iterator = shortestPath->begin();
        totalDistance += (*iterator).Weight;
        ASSERT_EQ((*iterator).From, 0);
        ASSERT_EQ((*iterator).To, 1);
        ASSERT_EQ((*iterator).Weight, 2llu);
        iterator++;

        totalDistance += (*iterator).Weight;
        ASSERT_EQ((*iterator).From, 1);
        ASSERT_EQ((*iterator).To, 2);
        ASSERT_EQ((*iterator).Weight, 1llu);
        iterator++;

        ASSERT_EQ(totalDistance, expectedTotalDistance);
    }
} /* Tests */ } /* Homework */
