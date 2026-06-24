#include <bits/stdc++.h>
// #include "Model/RubiksCube3dArray.cpp"
// #include "Model/RubiksCube1dArray.cpp"
// #include "Model/RubiksCubeBitboard.cpp"
// #include "Solver/DFSSolver.h"
// #include "Solver/BFSSolver.h"
// #include "Solver/IDDFSSolver.h"
#include "Solver/IDAstarSolver.h"
// #include "PatternDatabases/CornerPatternDatabase.h"
#include "PatternDatabases/CornerDBMaker.h"
#include "PatternDatabases/CornerDBMaker.cpp"
#include "PatternDatabases/CornerPatternDatabase.cpp"
#include "PatternDatabases/PatternDatabase.cpp"
#include "PatternDatabases/NibbleArray.cpp"
#include "PatternDatabases/math.cpp"
#include "Model/RubiksCube.cpp"
// #include "Model/RubiksCubeBitboard.cpp"

using namespace std;

int main()
{
    //    RubiksCube3dArray object3DArray;
    //    RubiksCube1dArray object1dArray;
    //    RubiksCubeBitboard objectBitboard;
    //
    //    object3DArray.print();
    //
    //    if (object3DArray.isSolved()) cout << "SOLVED\n\n";
    //    else cout << "NOT SOLVED\n\n";
    //
    //    if (object1dArray.isSolved()) cout << "SOLVED\n\n";
    //    else cout << "NOT SOLVED\n\n";
    //
    //    if (objectBitboard.isSolved()) cout << "SOLVED\n\n";
    //    else cout << "NOT SOLVED\n\n";
    //
    //    objectBitboard.u();
    //    object3DArray.u();
    //    object1dArray.u();
    //    objectBitboard.print();
    //    object3DArray.print();
    //    object1dArray.print();
    //
    //    objectBitboard.l();
    //    object3DArray.l();
    //    object1dArray.l();
    //    objectBitboard.print();
    //    object3DArray.print();
    //    object1dArray.print();
    //
    //    objectBitboard.f();
    //    object3DArray.f();
    //    object1dArray.f();
    //    objectBitboard.print();
    //    object3DArray.print();
    //    object1dArray.print();
    //
    //    objectBitboard.r();
    //    object3DArray.r();
    //    object1dArray.r();
    //    objectBitboard.print();
    //    object3DArray.print();
    //    object1dArray.print();
    //
    //    objectBitboard.b();
    //    object3DArray.b();
    //    object1dArray.b();
    //    objectBitboard.print();
    //    object3DArray.print();
    //    object1dArray.print();
    //
    //    objectBitboard.d();
    //    object3DArray.d();
    //    object1dArray.d();
    //    objectBitboard.print();
    //    object3DArray.print();
    //    object1dArray.print();
    //
    //    if (object3DArray.isSolved()) cout << "SOLVED\n\n";
    //    else cout << "NOT SOLVED\n\n";
    //
    //    if (object1dArray.isSolved()) cout << "SOLVED\n\n";
    //    else cout << "NOT SOLVED\n\n";
    //
    //    if (objectBitboard.isSolved()) cout << "SOLVED\n\n";
    //    else cout << "NOT SOLVED\n\n";
    //
    //    objectBitboard.dPrime();
    //    object3DArray.dPrime();
    //    object1dArray.dPrime();
    //    objectBitboard.print();
    //    object3DArray.print();
    //    object1dArray.print();
    //
    //    objectBitboard.bPrime();
    //    object3DArray.bPrime();
    //    object1dArray.bPrime();
    //    objectBitboard.print();
    //    object3DArray.print();
    //    object1dArray.print();
    //
    //    objectBitboard.rPrime();
    //    object3DArray.rPrime();
    //    object1dArray.rPrime();
    //    objectBitboard.print();
    //    object3DArray.print();
    //    object1dArray.print();
    //
    //    objectBitboard.fPrime();
    //    object3DArray.fPrime();
    //    object1dArray.fPrime();
    //    objectBitboard.print();
    //    object3DArray.print();
    //    object1dArray.print();
    //
    //    objectBitboard.lPrime();
    //    object3DArray.lPrime();
    //    object1dArray.lPrime();
    //    objectBitboard.print();
    //    object3DArray.print();
    //    object1dArray.print();
    //
    //    objectBitboard.uPrime();
    //    object3DArray.uPrime();
    //    object1dArray.uPrime();
    //    objectBitboard.print();
    //    object3DArray.print();
    //    object1dArray.print();
    //
    //    if (object3DArray.isSolved()) cout << "SOLVED\n\n";
    //    else cout << "NOT SOLVED\n\n";
    //
    //    if (object1dArray.isSolved()) cout << "SOLVED\n\n";
    //    else cout << "NOT SOLVED\n\n";
    //
    //    if (objectBitboard.isSolved()) cout << "SOLVED\n\n";
    //    else cout << "NOT SOLVED\n\n";

    // Create two Cubes ------------------------------------------------------------------------------------------

    //    RubiksCube3dArray cube1;
    //    RubiksCube3dArray cube2;

    //    RubiksCube1dArray cube1;
    //    RubiksCube1dArray cube2;

    //    RubiksCubeBitboard cube1;
    //    RubiksCubeBitboard cube2;

    //  Equality and assignment of cubes --------------------------------------------------------------------------

    //    if(cube1 == cube2) cout << "Is equal\n";
    //    else cout << "Not Equal\n";
    //
    //    cube1.randomShuffleCube(1);
    //
    //    if(cube1 == cube2) cout << "Is equal\n";
    //    else cout << "Not Equal\n";
    //
    //    cube2 = cube1;
    //
    //    if(cube1 == cube2) cout << "Is equal\n";
    //    else cout << "Not Equal\n";

    //  Unordered_map of Cubes  ------------------------------------------------------------------------------------

    //    unordered_map<RubiksCube3dArray, bool, Hash3d> mp1;

    //    unordered_map<RubiksCube1dArray, bool, Hash1d> mp1;

    //    unordered_map<RubiksCubeBitboard, bool, HashBitboard> mp1;
    //
    //    mp1[cube1] = true;
    //    cube2.randomShuffleCube(8);
    //    if (mp1[cube1]) cout << "Cube1 is present\n";
    //    else cout << "Cube1 is not present\n";
    //
    //    if (mp1[cube2]) cout << "Cube2 is present\n";
    //    else cout << "Cube2 is not present\n";
    //

    // DFS Solver Testing __________________________________________________________________________________________
    //    RubiksCube3dArray cube;
    //    cube.print();
    //
    //    vector<RubiksCube::MOVE> shuffle_moves = cube.randomShuffleCube(6);
    //    for (auto move: shuffle_moves) cout << cube.getMove(move) << " ";
    //    cout << "\n";
    //    cube.print();
    //
    //    DFSSolver<RubiksCube3dArray, Hash3d> dfsSolver(cube, 8);
    //    vector<RubiksCube::MOVE> solve_moves = dfsSolver.solve();
    //
    //    for (auto move: solve_moves) cout << cube.getMove(move) << " ";
    //    cout << "\n";
    //    dfsSolver.rubiksCube.print();

    // BFS Solver -----------------------------------------------------------------------------------------------------
    //     RubiksCubeBitboard cube;
    //     cube.print();
    //
    //     vector<RubiksCube::MOVE> shuffle_moves = cube.randomShuffleCube(6);
    //     for(auto move: shuffle_moves) cout << cube.getMove(move) << " ";
    //     cout << "\n";
    //     cube.print();
    //
    //     BFSSolver<RubiksCubeBitboard, HashBitboard> bfsSolver(cube);
    //     vector<RubiksCube::MOVE> solve_moves = bfsSolver.solve();
    //
    //     for(auto move: solve_moves) cout << cube.getMove(move) << " ";
    //     cout << "\n";
    //     bfsSolver.rubiksCube.print();

    // IDDFS Solver ----------------------------------------------------------------------------------------------------
    //    RubiksCubeBitboard cube;
    //    cube.print();
    //
    //    vector<RubiksCube::MOVE> shuffle_moves = cube.randomShuffleCube(7);
    //    for (auto move: shuffle_moves) cout << cube.getMove(move) << " ";
    //    cout << "\n";
    //    cube.print();
    //
    //    IDDFSSolver<RubiksCubeBitboard, HashBitboard> iddfsSolver(cube, 7);
    //    vector<RubiksCube::MOVE> solve_moves = iddfsSolver.solve();
    //
    //    for (auto move: solve_moves) cout << cube.getMove(move) << " ";
    //    cout << "\n";
    //    iddfsSolver.rubiksCube.print();

    // IDA* SOLVER ---------------------------------------------------------------------------------------------------
    // RubiksCubeBitboard cube;
    // cube.print();

    // vector<RubiksCube::MOVE> shuffle_moves = cube.randomShuffleCube(5);
    // for (auto move : shuffle_moves)
    //     cout << cube.getMove(move) << " ";
    // cout << "\n";
    // cube.print();

    // IDAstarSolver<RubiksCubeBitboard, HashBitboard> idAstarSolver(cube);
    // vector<RubiksCube::MOVE> solve_moves = idAstarSolver.solve();
    // for (auto move : solve_moves)
    //     cout << cube.getMove(move) << " ";
    // cout << "\n";
    // idAstarSolver.rubiksCube.print();

    // CornerPatternDatabase Testing ---------------------------------------------------------------------------------

    // CornerPatternDatabase cornerDB;
    // RubiksCubeBitboard cube;
    // cube.print();

    // cout << (int)cornerDB.getNumMoves(cube) << "\n";

    // cornerDB.setNumMoves(cube, 5);

    // cout << (int)cornerDB.getNumMoves(cube) << "\n";

    // cube.randomShuffleCube(1);
    // cube.print();
    // cout << (int)cornerDB.getNumMoves(cube) << "\n";

    // cornerDB.setNumMoves(cube, 6);

    // cout << (int)cornerDB.getNumMoves(cube) << "\n";

    // // CornerDBMaker Testing --------------------------------------------------------------------------
    // string fileName = "C:\\Users\\user\\CLionProjects\\rubiks-cube-solver\\Databases\\cornerDepth5V1.txt";

    //    Code to create Corner Database
    // CornerDBMaker dbMaker("cornerDepth5V1.txt", 0x99);
    // dbMaker.bfsAndStore();

    RubiksCubeBitboard cube;
    auto shuffleMoves = cube.randomShuffleCube(13);
    cube.print();
    for (auto move : shuffleMoves)
        cout << cube.getMove(move) << " ";
    cout << "\n";

    IDAstarSolver<RubiksCubeBitboard, HashBitboard> idaStarSolver(cube, "cornerDepth5V1.txt");
    auto moves = idaStarSolver.solve();

    idaStarSolver.rubiksCube.print();
    for (auto move : moves)
        cout << cube.getMove(move) << " ";
    cout << "\n";

    return 0;
} // #include <bits/stdc++.h>
// // #include "PatternDatabases/CornerDBMaker.cpp"
// #include "PatternDatabases/CornerPatternDatabase.cpp"
// #include "PatternDatabases/PatternDatabase.cpp"
// #include "PatternDatabases/NibbleArray.cpp"
// #include "PatternDatabases/math.cpp"
// #include "Model/RubiksCube.cpp"
// #include "Model/RubiksCubeBitboard.cpp"

// #include "Solver/IDAstarSolver.h"
// using namespace std;

// int main()
// {

//     RubiksCubeBitboard cube;
//     cube.print();

//     vector<RubiksCube::MOVE> shuffleMoves = cube.randomShuffleCube(10);
//     cout << "Scramble:\n";

//     for (auto move : shuffleMoves)
//     {
//         cout << RubiksCube::getMove(move) << " ";
//     }

//     cout << "\n\n";
//     cube.print();

//     IDAstarSolver<RubiksCubeBitboard, HashBitboard> solver(cube, "cornerDepth5V1.txt");
//     vector<RubiksCube::MOVE> solution = solver.solve();
//     cout << "Solved = " << solver.rubiksCube.isSolved() << "\n";
//     cout << "\nSolution Length = " << solution.size() << "\n";

//     // cout << "\nSolution: ";
//     solver.rubiksCube.print();
//     for (auto move : solution)
//     {
//         cout << RubiksCube::getMove(move) << " ";
//     }

//     // CornerDBMaker maker(
//     //     "cornerDepth5V1.txt",
//     //     15);
//     // cout << "Started BFS\n";
//     // maker.bfsAndStore();

//     // return 0;
//     // cout << "Scramble: ";
//     // for (auto m : scramble)
//     // {
//     //     cout << cube1.getMove(m) << " ";
//     // }
//     // cout << "\n\n";

//     // cout << "Before IDDFSS:\n";
//     // cube1.print();

//     // // RubiksCube3dArray cube2;
//     // // cube2.u();
//     // // cube2.fPrime();
//     // // cube2.r();
//     // // cube2.print();
//     // // cube2.rPrime();
//     // // cube2.f();
//     // // cube2.uPrime();
//     // // cube2.print();

//     // IDDFSSolver solver(cube1, 6);

//     // vector<RubiksCube::MOVE> solution = solver.solve();

//     // // cout << "\nSolution: ";
//     // solver.rubiksCube.print();
//     // for (auto move : solution)
//     // {
//     //     cout << RubiksCube::getMove(move) << " ";
//     // }
//     // for (auto m : solution)
//     // {
//     //     cout << cube1.getMove(m) << " ";
//     // }

//     cout << "\n\n";

//     // cout << "After IDDFSS:\n";
//     // solver.rubikscube.print();

//     // cout << "Solved = "
//     //      << solver.rubikscube.isSolved()
//     //      << "\n";
//     // //----
//     //     RubiksCube3dArray cube1;
//     //     cube1.print();
//     //     // if (cube1.isSolved())
//     //     // {
//     //     //     cout << "SOLVED" << "\n";
//     //     // }
//     //     // else
//     //     // {
//     //     //     cout << "NOT SOLVED" << "\n";
//     //     // }

//     //     // cube1.l();
//     //     // cube1.print();

//     //     vector<RubiksCube::MOVE> moveToShuffle = cube1.randomShuffleCube(3);
//     //     cube1.print();
//     //     for (auto a : moveToShuffle)
//     //     {
//     //         cout << cube1.getMove(a) << " ";
//     //     }
//     //     cout << "\n";

//     //     DFSSolver solver(cube1, 5);
//     //     vector<RubiksCube::MOVE> moveToSolve = solver.solve();
//     //     solver.rubikscube.print();
//     //     for (auto a : moveToSolve)
//     //     {
//     //         cout << cube1.getMove(a) << " ";
//     //     }
//     //     cout << "\n";
//     //     // cube1.print();
//     //     // if (cube1.isSolved())
//     //     // {
//     //     //     cout << "SOLVED" << "\n";
//     //     // }
//     //     // else
//     //     // {
//     //     //     cout << "NOT SOLVED" << "\n";
//     //     // }
//     return 0;
// }
