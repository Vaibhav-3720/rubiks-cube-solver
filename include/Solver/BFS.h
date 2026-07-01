#pragma once

#include "Model/RubiksCube.h"
#include "Model/RubiksCube3dArray.h"

#include <queue>
#include <unordered_map>
#include <vector>

class BFS
{
private:
    std::vector<RubiksCube::MOVE> moves;

    std::unordered_map<RubiksCube3dArray, bool, Hash3d> visited;
    std::unordered_map<RubiksCube3dArray, RubiksCube::MOVE, Hash3d> moveDone;

    RubiksCube3dArray rubiksCube;

    RubiksCube3dArray bfs();

public:
    explicit BFS(const RubiksCube3dArray &cube);

    std::vector<RubiksCube::MOVE> solve();
};