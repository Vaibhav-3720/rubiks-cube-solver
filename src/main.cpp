#include <iostream>
#include "Model/RubiksCube3dArray.h"
#include "Model/RubiksCubeBitboard.h"
#include "Solver/BFS.h"
#include "Solver/DFS.h"
#include "Solver/IDDFS.h"
#include <cassert>
using namespace std;

bool equalCube(const RubiksCube &a, const RubiksCube &b);
int main()
{
    // vector<RubiksCube::MOVE> moves;

    // for (int i = 0; i < 18; i++)
    //     moves.push_back((RubiksCube::MOVE)i);

    // cout << "==============================" << endl;
    // cout << "MOVE VALIDATION" << endl;
    // cout << "==============================" << endl;

    // for (auto move : moves)
    // {
    //     cout << "\nTesting "
    //          << RubiksCube::getMove(move)
    //          << endl;

    //     //-------------------------------
    //     // Single Move
    //     //-------------------------------

    //     RubiksCube3dArray c1;
    //     RubiksCubeBitboard c2;

    //     c1.move(move);
    //     c2.move(move);

    //     cout << "Single Move        : "
    //          << (equalCube(c1, c2) ? "PASS" : "FAIL")
    //          << endl;

    //     //-------------------------------
    //     // Move + Inverse
    //     //-------------------------------

    //     c1.invert(move);
    //     c2.invert(move);

    //     bool ok =
    //         equalCube(c1, c2) &&
    //         c1.isSolved() &&
    //         c2.isSolved();

    //     cout << "Inverse            : "
    //          << (ok ? "PASS" : "FAIL")
    //          << endl;

    //     //-------------------------------
    //     // Four Turns
    //     //-------------------------------

    //     RubiksCube3dArray c3;
    //     RubiksCubeBitboard c4;

    //     for (int i = 0; i < 4; i++)
    //     {
    //         c3.move(move);
    //         c4.move(move);
    //     }

    //     ok =
    //         equalCube(c3, c4) &&
    //         c3.isSolved() &&
    //         c4.isSolved();

    //     cout << "Four Turns         : "
    //          << (ok ? "PASS" : "FAIL")
    //          << endl;
    // }

    // return 0;

    //     int total=0;

    // for(int i=0;i<18;i++)
    // {
    //     for(int j=0;j<18;j++)
    //     {
    //         RubiksCube3dArray c1;
    //         RubiksCubeBitboard c2;

    //         c1.move((RubiksCube::MOVE)i);
    //         c1.move((RubiksCube::MOVE)j);

    //         c2.move((RubiksCube::MOVE)i);
    //         c2.move((RubiksCube::MOVE)j);

    //         total++;

    //         if(!equalCube(c1,c2))
    //         {
    //             cout<<"FAILED\n";

    //             cout<<"Move 1 : "
    //                 <<RubiksCube::getMove((RubiksCube::MOVE)i)
    //                 <<endl;

    //             cout<<"Move 2 : "
    //                 <<RubiksCube::getMove((RubiksCube::MOVE)j)
    //                 <<endl;

    //             return 0;
    //         }
    //     }
    // }

    // cout<<"All "<<total<<" Tests Passed"<<endl;
    RubiksCube3dArray a;
    RubiksCubeBitboard b;

    a.r();
    b.r();

    a.print();
    cout << "-----------------\n";
    b.print();
}

bool equalCube(const RubiksCube &a, const RubiksCube &b)
{
    for (int f = 0; f < 6; f++)
        for (int r = 0; r < 3; r++)
            for (int c = 0; c < 3; c++)
                if (a.getColor((RubiksCube::FACE)f, r, c) !=
                    b.getColor((RubiksCube::FACE)f, r, c))
                    return false;

    return true;
}