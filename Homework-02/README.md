# Homework 02 - Dijkstra's Algorithm

This is my solution for the [second homework assignment](https://www.coursera.org/learn/c-plus-plus-a/peer/1WzYR/homework-2-implement-dijkstras-algorithm) of the "C++ For C Programmers, Part A" class on Coursera.

## Getting Started

The code was written with Visual Studio 2017, so it's highly recommended you compile the code with it.

## Project Structure

The solution is split into three projects:
* `Homework-02` is a static library that implements the core logic for the assignment.
* `Homework-02.App` is a Windows console app that runs calculation and printing of the average shortest path distances described in the assignment's requirements.
* `Homework-02.Tests` tests the logic in `Homework-02` with the GoogleTest unit testing APIs.

## For Graders

Graders will be interested in reviewing the following files/classes:

* `Graph.h/.cpp`: As the name implies, this class represents an undirected graph.
* `ShortestPath.h/.cpp`: This represents the shortest path calculated from a start and end node.
* `ShortestPathCalculator.h/.cpp`: This class will calculate and return the `ShortestPath` from a start node to an end node of a given `Graph`; `nullptr` is returned if no path exists. It is really an implementation of Dijkstra's algorithm.
* `Homework-02.App.cpp`: The Windows console app that runs the logic described in the spec for the assignment.