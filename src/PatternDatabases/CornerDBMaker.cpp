#include "PatternDatabases/CornerDBMaker.h"

#include <iostream>
#include <queue>

//-------------------------------------
// Constructors
//-------------------------------------

CornerDBMaker::CornerDBMaker(const std::string &fileName)
    : fileName(fileName)
{
}

CornerDBMaker::CornerDBMaker(const std::string &fileName,
                             uint8_t initialValue)
    : fileName(fileName),
      cornerDatabase(initialValue)
{
}

//-------------------------------------
// Generate Corner Pattern Database
//-------------------------------------

bool CornerDBMaker::bfsAndStore()
{
    // A full breadth-first exploration of the corner state space (up to
    // depth 11) requires holding tens of millions of cube objects in the
    // BFS frontier simultaneously, which comfortably exceeds a few GB of
    // RAM. Capping at depth 8 covers ~31% of all reachable corner states
    // (the states most likely to be encountered early in a solve) while
    // keeping generation fast and memory-bounded. States beyond this
    // depth still get a safe (if less informative) heuristic value from
    // PatternDatabase's sentinel "unknown" entries.
    constexpr int kMaxDepth = 8;

    RubiksCubeBitboard cube;

    std::queue<RubiksCubeBitboard> queue;
    queue.push(cube);

    cornerDatabase.setNumMoves(cube, 0);

    int currentDepth = 0;

    while (!queue.empty())
    {
        const int levelSize = static_cast<int>(queue.size());

        currentDepth++;

        std::cout << "Depth = " << currentDepth
                  << " | Queue Size = "
                  << levelSize
                  << '\n';

        if (currentDepth > kMaxDepth)
        {
            break;
        }

        for (int i = 0; i < levelSize; i++)
        {
            RubiksCubeBitboard node = queue.front();
            queue.pop();

            for (int move = 0; move < 18; move++)
            {
                const auto currentMove =
                    static_cast<RubiksCube::MOVE>(move);

                node.move(currentMove);

                if (cornerDatabase.getNumMoves(node) > currentDepth)
                {
                    cornerDatabase.setNumMoves(node, currentDepth);
                    queue.push(node);
                }

                node.invert(currentMove);
            }
        }
    }

    cornerDatabase.toFile(fileName);

    return true;
}