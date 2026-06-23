#include<bits/stdc++.h>
#include "../Model/RubiksCube.h"
#include "../Model/RubiksCube3dArray.cpp"

class BFSSolver
{
private:

    vector<RubiksCube::MOVE> moves;
    unordered_map<RubiksCube3dArray,bool,Hash3d> vis;
    unordered_map<RubiksCube3dArray, RubiksCube::MOVE, Hash3d> move_done;
    RubiksCube3dArray bfs()
    {
        queue<RubiksCube3dArray> q;
        q.push(rubikscube);
        vis[rubikscube]=true;
        while(!q.empty())
        {
            RubiksCube3dArray node = q.front();
            q.pop();
            if (node.isSolved()) {
                return node;
            }
            for (int i = 0; i < 18; i++) {
                auto curr_move = RubiksCube::MOVE(i);
                node.move(curr_move);
                if (!vis[node]) {
                    vis[node] = true;
                    move_done[node] = curr_move;
                    q.push(node);
                }
                node.invert(curr_move);
            }
        }
        return rubikscube;
    }

public:
    RubiksCube3dArray rubikscube;
    BFSSolver(RubiksCube3dArray cube)
    {
        rubikscube = cube;
    }
    vector<RubiksCube::MOVE> solve()
    {
        RubiksCube3dArray solved_cube = bfs();
        assert(solved_cube.isSolved());
        RubiksCube3dArray curr_cube = solved_cube;
        while (!(curr_cube == rubikscube)) {
            RubiksCube::MOVE curr_move = move_done[curr_cube];
            moves.push_back(curr_move);
            curr_cube.invert(curr_move);
        }
        rubikscube = solved_cube;
        reverse(moves.begin(), moves.end());
        return moves;
    }
};