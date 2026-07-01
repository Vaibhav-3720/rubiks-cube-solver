#include "Solver/DFS.h"

//-------------------------------------
// Constructor
//-------------------------------------

DFS::DFS(const RubiksCube3dArray &cube, int depth)
    : rubiksCube(cube),
      maxSearchDepth(depth)
{
}

//-------------------------------------
// Depth First Search
//-------------------------------------

bool DFS::dfs(int depth)
{
    if (rubiksCube.isSolved())
    {
        return true;
    }

    if (depth >= maxSearchDepth)
    {
        return false;
    }

    for (int i = 0; i < 18; i++)
    {
        auto currentMove = static_cast<RubiksCube::MOVE>(i);

        rubiksCube.move(currentMove);
        moves.push_back(currentMove);

        if (dfs(depth + 1))
        {
            return true;
        }

        moves.pop_back();
        rubiksCube.invert(currentMove);
    }

    return false;
}
const RubiksCube3dArray &DFS::getCube() const
{
    return rubiksCube;
}
//-------------------------------------
// Solve
//-------------------------------------

std::vector<RubiksCube::MOVE> DFS::solve()
{
    moves.clear();

    if (dfs(0))
    {
        return moves;
    }

    return {};
}