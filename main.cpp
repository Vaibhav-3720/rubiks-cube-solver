#include <bits/stdc++.h>
#include "Model/RubiksCube.cpp"
#include "Solver/DFSSolver.h"
using namespace std;

int main()
{
    RubiksCube3dArray cube1;
    // cube1.print();
    // cube1.f();
    // cube1.u();
    // cube1.l();
    // cube1.print();

    vector<RubiksCube::MOVE> scramble = cube1.randomShuffleCube(3);

    cout << "Scramble: ";
    for (auto m : scramble)
    {
        cout << cube1.getMove(m) << " ";
    }
    cout << "\n\n";

    cout << "Before DFS:\n";
    cube1.print();

    // RubiksCube3dArray cube2;
    // cube2.u();
    // cube2.fPrime();
    // cube2.r();
    // cube2.print();
    // cube2.rPrime();
    // cube2.f();
    // cube2.uPrime();
    // cube2.print();

    // DFSSolver solver(cube1, 5);

    // vector<RubiksCube::MOVE> solution = solver.solve();

    // cout << "\nSolution: ";
    // for (auto m : solution)
    // {
    //     cout << cube1.getMove(m) << " ";
    // }

    // cout << "\n\n";

    // cout << "After DFS:\n";
    // solver.rubikscube.print();

    // cout << "Solved = "
    //      << solver.rubikscube.isSolved()
    //      << "\n";
    //----
    //     RubiksCube3dArray cube1;
//     cube1.print();
//     // if (cube1.isSolved())
//     // {
//     //     cout << "SOLVED" << "\n";
//     // }
//     // else
//     // {
//     //     cout << "NOT SOLVED" << "\n";
//     // }

//     // cube1.l();
//     // cube1.print();

//     vector<RubiksCube::MOVE> moveToShuffle = cube1.randomShuffleCube(3);
//     cube1.print();
//     for (auto a : moveToShuffle)
//     {
//         cout << cube1.getMove(a) << " ";
//     }
//     cout << "\n";

//     DFSSolver solver(cube1, 5);
//     vector<RubiksCube::MOVE> moveToSolve = solver.solve();
//     solver.rubikscube.print();
//     for (auto a : moveToSolve)
//     {
//         cout << cube1.getMove(a) << " ";
//     }
//     cout << "\n";
//     // cube1.print();
//     // if (cube1.isSolved())
//     // {
//     //     cout << "SOLVED" << "\n";
//     // }
//     // else
//     // {
//     //     cout << "NOT SOLVED" << "\n";
//     // }
}