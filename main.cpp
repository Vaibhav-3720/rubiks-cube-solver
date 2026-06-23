#include <bits/stdc++.h>
#include "Model/RubiksCube.cpp"
#include "Model/RubiksCube3dArray.cpp"
using namespace std;

int main()
{
    RubiksCube3dArray cube1;
    cube1.print();
    if (cube1.isSolved())
    {
        cout << "SOLVED" << "\n";
    }
    else
    {
        cout << "NOT SOLVED" << "\n";
    }

    // cube1.l();
    // cube1.print();

    vector<RubiksCube::MOVE> moveToShuffle = cube1.randomShuffleCube(10);
    for (auto a : moveToShuffle)
    {
        cout << cube1.getMove(a) << " ";
    }
    cout << "\n";
    cube1.print();
    if (cube1.isSolved())
    {
        cout << "SOLVED" << "\n";
    }
    else
    {
        cout << "NOT SOLVED" << "\n";
    }
}