#ifndef IDDFSSOLVER_H
#define IDDFSSOLVER_H
#include<bits/stdc++.h>
#include "../Model/RubiksCube.h"
#include "DFSSolver.h"

class IDDFSSolver
{
private:
    int max_search_depth;
    vector<RubiksCube::MOVE> moves;

public:
    RubiksCube3dArray rubikscube;
    IDDFSSolver(RubiksCube3dArray cube, int max_depth)
    {
        rubikscube=cube;
        max_search_depth=max_depth;
    }
    vector<RubiksCube::MOVE> solve()
    {
        moves.clear();
        for (int i = 1; i <= max_search_depth; i++) 
        {
            DFSSolver dfsSolver(rubikscube, i);
            moves = dfsSolver.solve();
            if (dfsSolver.rubikscube.isSolved()) {
                rubikscube = dfsSolver.rubikscube;
                return moves;
            }
        }
        return {};
    }
};
#endif