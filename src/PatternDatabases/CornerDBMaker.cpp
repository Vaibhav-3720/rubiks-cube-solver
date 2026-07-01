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

        if (currentDepth == 9)
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