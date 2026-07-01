#pragma once

#include "Model/RubiksCube.h"
#include "Model/RubiksCube3dArray.h"

#include <vector>

class DFS
{
private:
    std::vector<RubiksCube::MOVE> moves;

    RubiksCube3dArray rubiksCube;

    int maxSearchDepth;

    bool dfs(int depth);

public:
    DFS(const RubiksCube3dArray &cube, int depth);
    const RubiksCube3dArray &getCube() const;

    std::vector<RubiksCube::MOVE> solve();
};