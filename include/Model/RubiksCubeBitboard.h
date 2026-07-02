#pragma once

#include "Model/RubiksCube.h"

#include <cstdint>
#include <cstddef>

struct HashBitboard;

class RubiksCubeBitboard : public RubiksCube
{
    friend struct HashBitboard;

private:
    uint64_t solved_side_config[6]{};

    uint64_t bitboard[6]{};

    int arr[3][3] = {
        {0, 1, 2},
        {7, 8, 3},
        {6, 5, 4}
    };

    uint64_t one_8 = (1ULL << 8) - 1;
    uint64_t one_24 = (1ULL << 24) - 1;

    void rotateFace(int face);

    void rotateSide(
        int s1, int s1_1, int s1_2, int s1_3,
        int s2, int s2_1, int s2_2, int s2_3);

    int get5bitCorner(const std::string &corner);

public:
    RubiksCubeBitboard();
    RubiksCubeBitboard(const RubiksCubeBitboard &other) = default;

    // Cube State
    COLOR getColor(FACE face, unsigned row, unsigned col) const override;
    bool isSolved() const override;

    // Clockwise
    RubiksCube &u() override;
    RubiksCube &l() override;
    RubiksCube &f() override;
    RubiksCube &r() override;
    RubiksCube &b() override;
    RubiksCube &d() override;

    // Counter Clockwise
    RubiksCube &uPrime() override;
    RubiksCube &lPrime() override;
    RubiksCube &fPrime() override;
    RubiksCube &rPrime() override;
    RubiksCube &bPrime() override;
    RubiksCube &dPrime() override;

    // Double Turns
    RubiksCube &u2() override;
    RubiksCube &l2() override;
    RubiksCube &f2() override;
    RubiksCube &r2() override;
    RubiksCube &b2() override;
    RubiksCube &d2() override;

    bool operator==(const RubiksCubeBitboard &other) const;
    RubiksCubeBitboard &operator=(const RubiksCubeBitboard &other);

    uint64_t getCorners();
};

struct HashBitboard
{
    std::size_t operator()(const RubiksCubeBitboard &cube) const;
};