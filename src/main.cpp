#include <iostream>
#include "Model/RubiksCube3dArray.h"
#include "Model/RubiksCubeBitboard.h"
#include "Solver/BFS.h"
#include "Solver/DFS.h"
#include "Solver/IDDFS.h"
#include "Solver/IDAStar.h"
#include "PatternDatabases/NibbleArray.h"
#include "PatternDatabases/PatternDatabase.h"
#include "PatternDatabases/PermutationIndexer.h"
#include "PatternDatabases/CornerPatternDatabase.h"
#include "PatternDatabases/CornerDBMaker.h"
#include <cassert>
#include <vector>
#include <iostream>
#include <chrono>
#include <random>
#include <cstdlib>
#include <ctime>
using namespace std;
using namespace std::chrono;
// bool equalCube(const RubiksCube &a, const RubiksCube &b);

int main()
{

    // srand(time(nullptr));
    // dfs test------

    // RubiksCube3dArray cube;
    // cube.print();

    // vector<RubiksCube::MOVE> shuffle_moves = cube.randomShuffleCube(6);
    // for (auto move : shuffle_moves)
    //     cout << cube.getMove(move) << " ";
    // cout << "\n";
    // cube.print();

    // DFS dfs(cube, 8);
    // vector<RubiksCube::MOVE> solve_moves = dfs.solve();

    // for (auto move : solve_moves)
    //     cout << cube.getMove(move) << " ";
    // cout << "\n";
    // dfs.getCube().print();

    // bfs test------

    // RubiksCube3dArray cube;
    // cube.print();

    // vector<RubiksCube::MOVE> shuffle_moves = cube.randomShuffleCube(6);
    // for (auto move : shuffle_moves)
    //     cout << cube.getMove(move) << " ";
    // cout << "\n";
    // cube.print();

    // BFS bfs(cube);
    // vector<RubiksCube::MOVE> solve_moves = bfs.solve();

    // for (auto move : solve_moves)
    //     cout << cube.getMove(move) << " ";
    // cout << "\n";
    // bfs.getCube().print();

    // iddfs test------

    // RubiksCube3dArray cube;
    // cube.print();

    // vector<RubiksCube::MOVE> shuffle_moves = cube.randomShuffleCube(7);
    // for (auto move : shuffle_moves)
    //     cout << cube.getMove(move) << " ";
    // cout << "\n";
    // cube.print();

    // IDDFS iddfs(cube, 7);
    // vector<RubiksCube::MOVE> solve_moves = iddfs.solve();

    // for (auto move : solve_moves)
    //     cout << cube.getMove(move) << " ";
    // cout << "\n";
    // iddfs.getCube().print();

    // ida* test------
    // string fileName = "data/cornerPatternDB.bin";
    // RubiksCubeBitboard cube;
    // auto shuffleMoves = cube.randomShuffleCube(12);
    // cube.print();
    // for (auto move : shuffleMoves)
    //     cout << cube.getMove(move) << " ";
    // cout << "\n";

    // IDAstarSolver<RubiksCubeBitboard, HashBitboard> idaStarSolver(cube, fileName);
    // auto moves = idaStarSolver.solve();

    // idaStarSolver.rubiksCube.print();
    // for (auto move : moves)
    //     cout << cube.getMove(move) << " ";
    // cout << "\n";
}
// bool equalCube(const RubiksCube &a, const RubiksCube &b)
// {
//     for (int face = 0; face < 6; face++)
//     {
//         for (int row = 0; row < 3; row++)
//         {
//             for (int col = 0; col < 3; col++)
//             {
//                 if (a.getColor(
//                         static_cast<RubiksCube::FACE>(face),
//                         row,
//                         col) !=
//                     b.getColor(
//                         static_cast<RubiksCube::FACE>(face),
//                         row,
//                         col))
//                 {
//                     return false;
//                 }
//             }
//         }
//     }

//     return true;
// }
// // Rubik's Cube Solver — demo / benchmark driver.
// //
// // Scrambles a cube to increasing depths and times how long the IDA*
// // solver (guided by a corner pattern database) takes to solve it back,
// // verifying every solution actually restores the cube before reporting.

// #include "Model/RubiksCubeBitboard.h"
// #include "Solver/IDAStar.h"

// #include <chrono>
// #include <iostream>
// #include <vector>

// namespace
// {
//     constexpr const char *kCornerDatabasePath = "data/cornerPatternDB.bin";
//     constexpr int kMinScrambleDepth = 1;
//     // The corner pattern database only has exact values up to depth 8
//     // (see CornerDBMaker); beyond that the heuristic weakens and both
//     // search time and memory use grow quickly (and can vary a lot
//     // between individual scrambles). Depth 9 keeps every trial in this
//     // demo fast and memory-bounded on modest hardware. Raise this if you
//     // have RAM/time to spare, or extend the pattern database's BFS depth
//     // for a stronger heuristic that scales further.
//     constexpr int kMaxScrambleDepth = 15;
//     constexpr int kTrialsPerDepth = 1;

//     void printMoves(const std::vector<RubiksCube::MOVE> &moves)
//     {
//         for (auto m : moves)
//             std::cout << RubiksCube::getMove(m) << " ";
//     }
// }

// int main()
// {
//     for (int depth = kMinScrambleDepth; depth <= kMaxScrambleDepth; depth++)
//     {
//         long long totalTimeMs = 0;
//         long long totalSolutionLength = 0;

//         std::cout << "=============================\n";
//         std::cout << "Scramble Depth : " << depth << '\n';

//         for (int trial = 1; trial <= kTrialsPerDepth; trial++)
//         {
//             RubiksCubeBitboard cube;
//             auto scramble = cube.randomShuffleCube(depth);

//             if (trial == 1)
//             {
//                 std::cout << "Example Scramble : ";
//                 printMoves(scramble);
//                 std::cout << "\n";
//             }

//             const auto start = std::chrono::high_resolution_clock::now();

//             IDAstarSolver<RubiksCubeBitboard, HashBitboard> solver(
//                 cube, kCornerDatabasePath);
//             auto solution = solver.solve();

//             const auto end = std::chrono::high_resolution_clock::now();

//             totalTimeMs += std::chrono::duration_cast<
//                                std::chrono::milliseconds>(end - start)
//                                .count();
//             totalSolutionLength += static_cast<long long>(solution.size());

//             RubiksCubeBitboard verify = cube;
//             for (auto m : solution)
//                 verify.move(m);

//             if (!verify.isSolved())
//             {
//                 std::cout << "\nFAILED on trial " << trial << '\n';

//                 std::cout << "Scramble : ";
//                 printMoves(scramble);

//                 std::cout << "\nSolution : ";
//                 printMoves(solution);

//                 std::cout << std::endl;
//                 return 1;
//             }
//         }

//         std::cout << "Average Time            : "
//                   << static_cast<double>(totalTimeMs) / kTrialsPerDepth
//                   << " ms\n";
//         std::cout << "Average Solution Length : "
//                   << static_cast<double>(totalSolutionLength) / kTrialsPerDepth
//                   << "\n\n";
//     }

//     return 0;
// }