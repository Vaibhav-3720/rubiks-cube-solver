#include "Solver/BFS.h"

#include <algorithm>
#include <cassert>

//-------------------------------------
// Constructor
//-------------------------------------

BFS::BFS(const RubiksCube3dArray &cube)
    : rubiksCube(cube)
{
}

//-------------------------------------
// Breadth First Search
//-------------------------------------

RubiksCube3dArray BFS::bfs()
{
    std::queue<RubiksCube3dArray> queue;

    queue.push(rubiksCube);
    visited[rubiksCube] = true;

    while (!queue.empty())
    {
        RubiksCube3dArray node = queue.front();
        queue.pop();

        if (node.isSolved())
        {
            return node;
        }

        for (int i = 0; i < 18; i++)
        {
            auto currentMove = static_cast<RubiksCube::MOVE>(i);

            node.move(currentMove);

            if (!visited[node])
            {
                visited[node] = true;
                moveDone[node] = currentMove;

                queue.push(node);
            }

            node.invert(currentMove);
        }
    }

    return rubiksCube;
}

//-------------------------------------
// Solve
//-------------------------------------

std::vector<RubiksCube::MOVE> BFS::solve()
{
    RubiksCube3dArray solvedCube = bfs();

    assert(solvedCube.isSolved());

    RubiksCube3dArray currentCube = solvedCube;

    while (!(currentCube == rubiksCube))
    {
        RubiksCube::MOVE currentMove = moveDone[currentCube];

        moves.push_back(currentMove);

        currentCube.invert(currentMove);
    }

    rubiksCube = solvedCube;

    std::reverse(moves.begin(), moves.end());

    return moves;
}