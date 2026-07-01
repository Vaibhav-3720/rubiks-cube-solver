#ifndef RUBIKSCUBE_H
#define RUBIKSCUBE_H

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

class RubiksCube
{
public:
    enum class FACE
    {
        UP,
        LEFT,
        FRONT,
        RIGHT,
        BACK,
        DOWN
    };
    enum class COLOR
    {
        WHITE,
        GREEN,
        RED,
        BLUE,
        ORANGE,
        YELLOW
    };
    enum class MOVE
    {
        L,
        LPRIME,
        L2,
        R,
        RPRIME,
        R2,
        U,
        UPRIME,
        U2,
        D,
        DPRIME,
        D2,
        F,
        FPRIME,
        F2,
        B,
        BPRIME,
        B2
    };
    virtual COLOR getColor(FACE face, unsigned row, unsigned col) const = 0;
    static char getColorLetter(COLOR color);
    virtual bool isSolved() const = 0;
    static std::string getMove(MOVE moves);
    void print() const;
    std::vector<MOVE> randomShuffleCube(unsigned int move);
    RubiksCube &move(MOVE move);
    RubiksCube &invert(MOVE move);
    virtual RubiksCube &f() = 0;
    virtual RubiksCube &b() = 0;
    virtual RubiksCube &u() = 0;
    virtual RubiksCube &d() = 0;
    virtual RubiksCube &l() = 0;
    virtual RubiksCube &r() = 0;
    virtual RubiksCube &fPrime() = 0;
    virtual RubiksCube &bPrime() = 0;
    virtual RubiksCube &uPrime() = 0;
    virtual RubiksCube &dPrime() = 0;
    virtual RubiksCube &lPrime() = 0;
    virtual RubiksCube &rPrime() = 0;
    virtual RubiksCube &f2() = 0;
    virtual RubiksCube &b2() = 0;
    virtual RubiksCube &u2() = 0;
    virtual RubiksCube &d2() = 0;
    virtual RubiksCube &l2() = 0;
    virtual RubiksCube &r2() = 0;
    std::string getCornerColorString(uint8_t index) const;
    uint8_t getCornerIndex(uint8_t index) const;
    uint8_t getCornerOrientation(uint8_t index) const;
    virtual ~RubiksCube() = default;
};

#endif