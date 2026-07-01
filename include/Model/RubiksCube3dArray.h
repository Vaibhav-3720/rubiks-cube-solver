#pragma once

#include "Model/RubiksCube.h"

class RubiksCube3dArray : public RubiksCube
{
    friend struct Hash3d;
private:
    char cube[6][3][3];

    void rotateFace(int face);

public:
    RubiksCube3dArray();

    COLOR getColor(FACE face, unsigned row, unsigned col) const override;
    bool isSolved() const override;

    RubiksCube &u() override;
    RubiksCube &uPrime() override;
    RubiksCube &u2() override;

    RubiksCube &l() override;
    RubiksCube &lPrime() override;
    RubiksCube &l2() override;

    RubiksCube &f() override;
    RubiksCube &fPrime() override;
    RubiksCube &f2() override;

    RubiksCube &r() override;
    RubiksCube &rPrime() override;
    RubiksCube &r2() override;

    RubiksCube &b() override;
    RubiksCube &bPrime() override;
    RubiksCube &b2() override;

    RubiksCube &d() override;
    RubiksCube &dPrime() override;
    RubiksCube &d2() override;

    bool operator==(const RubiksCube3dArray &other) const;
    RubiksCube3dArray &operator=(const RubiksCube3dArray &other);
};

struct Hash3d
{
    std::size_t operator()(const RubiksCube3dArray &cube) const;
};