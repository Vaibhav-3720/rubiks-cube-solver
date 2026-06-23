#include<bits/stdc++.h>
#include "../Model/RubiksCube.h"
#include "../Model/RubiksCube3dArray.cpp"

class DFSSolver
{
private:

    vector<RubiksCube::MOVE> moves;
    int max_search_depth;
    bool dfs(int dep)
    {
        if(rubikscube.isSolved())
        {
            return true;
        }
        if(dep>=max_search_depth)
        {
            return false;
        }
        for(int i=0;i<18;i++)
        {
            rubikscube.move(RubiksCube::MOVE(i));
            moves.push_back(RubiksCube::MOVE(i));
            if (dfs(dep + 1)) return true;
            moves.pop_back();
            rubikscube.invert(RubiksCube::MOVE(i));
        }
        return false;
    }

public:
    RubiksCube3dArray rubikscube;

    DFSSolver(RubiksCube3dArray cube, int depth)
    {
        rubikscube = cube;
        max_search_depth = depth;
    }

    vector<RubiksCube::MOVE> solve() {
        moves.clear();
        if(dfs(0)){
        return moves;
        }
        return {};
    }

};