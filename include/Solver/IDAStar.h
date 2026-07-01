#pragma once

#include "Model/RubiksCube.h"
#include "PatternDatabases/CornerPatternDatabase.h"

#include <algorithm>
#include <cassert>
#include <queue>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

template <typename T, typename H>
class IDAstarSolver
{
private:
    struct Node
    {
        T cube;
        int depth;
        int estimate;

        Node(T cube, int depth, int estimate)
            : cube(cube),
              depth(depth),
              estimate(estimate)
        {
        }
    };

    struct CompareNode
    {
        bool operator()(const std::pair<Node, int> &lhs,
                        const std::pair<Node, int> &rhs) const
        {
            const Node &left = lhs.first;
            const Node &right = rhs.first;

            if (left.depth + left.estimate ==
                right.depth + right.estimate)
            {
                return left.estimate > right.estimate;
            }

            return (left.depth + left.estimate) >
                   (right.depth + right.estimate);
        }
    };

    CornerPatternDatabase cornerDatabase;

    std::vector<RubiksCube::MOVE> moves;

    std::unordered_map<T, RubiksCube::MOVE, H> moveDone;

    std::unordered_map<T, bool, H> visited;

    void resetStructure();

    std::pair<T, int> IDAstar(int bound);

public:
    T rubiksCube;

    IDAstarSolver(const T &cube,
                  const std::string &fileName);

    std::vector<RubiksCube::MOVE> solve();
};