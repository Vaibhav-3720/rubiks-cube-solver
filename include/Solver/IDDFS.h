#pragma once

#include "Model/RubiksCube3dArray.h"
#include "Solver/DFS.h"

#include <vector>

class IDDFS
{
private:
    int maxSearchDepth;

    std::vector<RubiksCube::MOVE> moves;

    RubiksCube3dArray rubiksCube;

public:
    IDDFS(const RubiksCube3dArray &cube, int maxDepth);

    std::vector<RubiksCube::MOVE> solve();
    const RubiksCube3dArray& getCube() const;
};