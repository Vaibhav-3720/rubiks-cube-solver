#include "Solver/IDDFS.h"

//-------------------------------------
// Constructor
//-------------------------------------

IDDFS::IDDFS(
    const RubiksCube3dArray &cube,
    int maxDepth)
    : maxSearchDepth(maxDepth),
      rubiksCube(cube)
{
}

//-------------------------------------
// Solve
//-------------------------------------

std::vector<RubiksCube::MOVE> IDDFS::solve()
{
    moves.clear();

    for (int depth = 1; depth <= maxSearchDepth; depth++)
    {
        DFS dfs(rubiksCube, depth);

        moves = dfs.solve();

        if (!moves.empty())
        {
            rubiksCube = dfs.getCube();
            return moves;
        }
    }

    return {};
}
const RubiksCube3dArray& IDDFS::getCube() const
{
    return rubiksCube;
}