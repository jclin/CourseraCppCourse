#include "ShortestPath.h"

#include <sstream>
#include <iomanip>

using namespace std;
using namespace Homework::ShortestPath;

std::string ShortestPath::ToString() const
{
    stringstream stringStream;

    stringStream << std::left  << std::setw(20) << "From-To:"
                 << std::right << std::setw(8) << pathTraveled.front().From << "-" << pathTraveled.back().To << endl;

    stringStream << std::left  << std::setw(20) << "Hops:"
                 << std::right << std::setw(8) << Length() << endl;

    stringStream << std::left  << std::setw(20) << "Distance:"
                 << std::right << std::setw(8) << TotalDistance() << endl;

    stringStream << endl;

    for (auto edge : pathTraveled)
    {
        stringStream << std::left << std::setw(2)  << edge.From
                     << std::left << std::setw(2)  << "->"
                     << std::left << std::setw(2)  << edge.To
                     << std::left << std::setw(3)  << " : "
                     << std::left << std::setw(10) <<  edge.Weight << endl;
    }

    stringStream << endl;

    return std::move(stringStream.str());
}