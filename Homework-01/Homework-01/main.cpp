#include <iostream>
#include <vector>

using namespace std;

const int kTotalElements = 40;

// Returns the sum of all the integers in elements.
inline int sum(const vector<int>& elements)
{
    int total = 0;
    for (auto element : elements)
    {
        total += element;
    }

    return total;
}

int main()
{
    vector<int> data;
    for (int i = 0; i < kTotalElements; ++i)
    {
        data.push_back(i);
    }

    const auto accum = sum(data);

    cout << "Sum is " << accum << endl;

    return 0;
}