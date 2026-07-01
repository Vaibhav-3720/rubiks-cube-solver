#include "Model/RubiksCubeBitboard.h"

#include <functional>
#include <string>

//-------------------------------------
// Helper Functions
//-------------------------------------

void RubiksCubeBitboard::rotateFace(int face)
{
    uint64_t side = bitboard[face];
    side >>= (8 * 6);

    bitboard[face] = (bitboard[face] << 16) | side;
}

void RubiksCubeBitboard::rotateSide(
    int s1, int s1_1, int s1_2, int s1_3,
    int s2, int s2_1, int s2_2, int s2_3)
{
    uint64_t clr1 = (bitboard[s2] & (one_8 << (8 * s2_1))) >> (8 * s2_1);

    uint64_t clr2 = (bitboard[s2] & (one_8 << (8 * s2_2))) >> (8 * s2_2);

    uint64_t clr3 = (bitboard[s2] & (one_8 << (8 * s2_3))) >> (8 * s2_3);

    bitboard[s1] = (bitboard[s1] & ~(one_8 << (8 * s1_1))) | (clr1 << (8 * s1_1));

    bitboard[s1] = (bitboard[s1] & ~(one_8 << (8 * s1_2))) | (clr2 << (8 * s1_2));

    bitboard[s1] = (bitboard[s1] & ~(one_8 << (8 * s1_3))) | (clr3 << (8 * s1_3));
}

int RubiksCubeBitboard::get5bitCorner(const std::string &corner)
{
    int ret = 0;
    std::string actualStr;

    for (char c : corner)
    {
        if (c != 'W' && c != 'Y')
            continue;

        actualStr.push_back(c);

        if (c == 'Y')
            ret |= (1 << 2);
    }

    for (char c : corner)
    {
        if (c != 'R' && c != 'O')
            continue;

        if (c == 'O')
            ret |= (1 << 1);
    }

    for (char c : corner)
    {
        if (c != 'B' && c != 'G')
            continue;

        if (c == 'G')
            ret |= (1 << 0);
    }

    if (corner[1] == actualStr[0])
    {
        ret |= (1 << 3);
    }
    else if (corner[2] == actualStr[0])
    {
        ret |= (1 << 4);
    }

    return ret;
}

//-------------------------------------
// Constructor
//-------------------------------------

RubiksCubeBitboard::RubiksCubeBitboard()
{
    for (int side = 0; side < 6; side++)
    {
        uint64_t color = 1ULL << side;

        bitboard[side] = 0;

        for (int faceIndex = 0; faceIndex < 8; faceIndex++)
        {
            bitboard[side] |= color << (8 * faceIndex);
        }

        solved_side_config[side] = bitboard[side];
    }
}

//-------------------------------------
// Cube State
//-------------------------------------

RubiksCube::COLOR RubiksCubeBitboard::getColor(
    FACE face,
    unsigned row,
    unsigned col) const
{
    int index = arr[row][col];

    if (index == 8)
        return static_cast<COLOR>(face);

    uint64_t side = bitboard[static_cast<int>(face)];
    uint64_t color = (side >> (8 * index)) & one_8;

    int bitPosition = 0;

    while (color)
    {
        color >>= 1;
        bitPosition++;
    }

    return static_cast<COLOR>(bitPosition - 1);
}

bool RubiksCubeBitboard::isSolved() const
{
    for (int i = 0; i < 6; i++)
    {
        if (bitboard[i] != solved_side_config[i])
            return false;
    }

    return true;
}

//-------------------------------------
// U Moves
//-------------------------------------

RubiksCube &RubiksCubeBitboard::u()
{
    rotateFace(static_cast<int>(FACE::UP));

    uint64_t temp = bitboard[2] & one_24;

    bitboard[2] =
        (bitboard[2] & ~one_24) |
        (bitboard[3] & one_24);

    bitboard[3] =
        (bitboard[3] & ~one_24) |
        (bitboard[4] & one_24);

    bitboard[4] =
        (bitboard[4] & ~one_24) |
        (bitboard[1] & one_24);

    bitboard[1] =
        (bitboard[1] & ~one_24) |
        temp;

    return *this;
}

RubiksCube &RubiksCubeBitboard::uPrime()
{
    u();
    u();
    u();

    return *this;
}

RubiksCube &RubiksCubeBitboard::u2()
{
    u();
    u();

    return *this;
}
//-------------------------------------
// L Moves
//-------------------------------------

RubiksCube &RubiksCubeBitboard::l()
{
    rotateFace(static_cast<int>(FACE::LEFT));

    uint64_t clr1 = (bitboard[2] & (one_8 << (8 * 0))) >> (8 * 0);
    uint64_t clr2 = (bitboard[2] & (one_8 << (8 * 6))) >> (8 * 6);
    uint64_t clr3 = (bitboard[2] & (one_8 << (8 * 7))) >> (8 * 7);

    rotateSide(2, 0, 7, 6, 0, 0, 7, 6);
    rotateSide(0, 0, 7, 6, 4, 4, 3, 2);
    rotateSide(4, 4, 3, 2, 5, 0, 7, 6);

    bitboard[5] = (bitboard[5] & ~(one_8 << (8 * 0))) | (clr1 << (8 * 0));
    bitboard[5] = (bitboard[5] & ~(one_8 << (8 * 6))) | (clr2 << (8 * 6));
    bitboard[5] = (bitboard[5] & ~(one_8 << (8 * 7))) | (clr3 << (8 * 7));

    return *this;
}

RubiksCube &RubiksCubeBitboard::lPrime()
{
    l();
    l();
    l();
    return *this;
}

RubiksCube &RubiksCubeBitboard::l2()
{
    l();
    l();
    return *this;
}

//-------------------------------------
// F Moves
//-------------------------------------

RubiksCube &RubiksCubeBitboard::f()
{
    rotateFace(static_cast<int>(FACE::FRONT));

    uint64_t clr1 = (bitboard[0] & (one_8 << (8 * 4))) >> (8 * 4);
    uint64_t clr2 = (bitboard[0] & (one_8 << (8 * 5))) >> (8 * 5);
    uint64_t clr3 = (bitboard[0] & (one_8 << (8 * 6))) >> (8 * 6);

    rotateSide(0, 4, 5, 6, 1, 2, 3, 4);
    rotateSide(1, 2, 3, 4, 5, 0, 1, 2);
    rotateSide(5, 0, 1, 2, 3, 6, 7, 0);

    bitboard[3] = (bitboard[3] & ~(one_8 << (8 * 6))) | (clr1 << (8 * 6));
    bitboard[3] = (bitboard[3] & ~(one_8 << (8 * 7))) | (clr2 << (8 * 7));
    bitboard[3] = (bitboard[3] & ~(one_8 << (8 * 0))) | (clr3 << (8 * 0));

    return *this;
}

RubiksCube &RubiksCubeBitboard::fPrime()
{
    f();
    f();
    f();
    return *this;
}

RubiksCube &RubiksCubeBitboard::f2()
{
    f();
    f();
    return *this;
}

//-------------------------------------
// R Moves
//-------------------------------------

RubiksCube &RubiksCubeBitboard::r()
{
    rotateFace(static_cast<int>(FACE::RIGHT));

    uint64_t clr1 = (bitboard[0] & (one_8 << (8 * 2))) >> (8 * 2);
    uint64_t clr2 = (bitboard[0] & (one_8 << (8 * 3))) >> (8 * 3);
    uint64_t clr3 = (bitboard[0] & (one_8 << (8 * 4))) >> (8 * 4);

    rotateSide(0, 2, 3, 4, 2, 2, 3, 4);
    rotateSide(2, 2, 3, 4, 5, 2, 3, 4);
    rotateSide(5, 2, 3, 4, 4, 7, 6, 0);

    bitboard[4] = (bitboard[4] & ~(one_8 << (8 * 0))) | (clr1 << (8 * 0));
    bitboard[4] = (bitboard[4] & ~(one_8 << (8 * 7))) | (clr2 << (8 * 7));
    bitboard[4] = (bitboard[4] & ~(one_8 << (8 * 6))) | (clr3 << (8 * 6));

    return *this;
}

RubiksCube &RubiksCubeBitboard::rPrime()
{
    r();
    r();
    r();
    return *this;
}

RubiksCube &RubiksCubeBitboard::r2()
{
    r();
    r();
    return *this;
}

//-------------------------------------
// B Moves
//-------------------------------------

RubiksCube &RubiksCubeBitboard::b()
{
    rotateFace(static_cast<int>(FACE::BACK));

    uint64_t clr1 = (bitboard[0] & (one_8 << (8 * 0))) >> (8 * 0);
    uint64_t clr2 = (bitboard[0] & (one_8 << (8 * 1))) >> (8 * 1);
    uint64_t clr3 = (bitboard[0] & (one_8 << (8 * 2))) >> (8 * 2);

    rotateSide(0, 0, 1, 2, 3, 2, 3, 4);
    rotateSide(3, 2, 3, 4, 5, 4, 5, 6);
    rotateSide(5, 4, 5, 6, 1, 6, 7, 0);

    bitboard[1] = (bitboard[1] & ~(one_8 << (8 * 6))) | (clr1 << (8 * 6));
    bitboard[1] = (bitboard[1] & ~(one_8 << (8 * 7))) | (clr2 << (8 * 7));
    bitboard[1] = (bitboard[1] & ~(one_8 << (8 * 0))) | (clr3 << (8 * 0));

    return *this;
}

RubiksCube &RubiksCubeBitboard::bPrime()
{
    b();
    b();
    b();
    return *this;
}

RubiksCube &RubiksCubeBitboard::b2()
{
    b();
    b();
    return *this;
}
//-------------------------------------
// D Moves
//-------------------------------------

RubiksCube &RubiksCubeBitboard::d()
{
    rotateFace(static_cast<int>(FACE::DOWN));

    uint64_t clr1 = (bitboard[2] & (one_8 << (8 * 4))) >> (8 * 4);
    uint64_t clr2 = (bitboard[2] & (one_8 << (8 * 5))) >> (8 * 5);
    uint64_t clr3 = (bitboard[2] & (one_8 << (8 * 6))) >> (8 * 6);

    rotateSide(2, 4, 5, 6, 1, 4, 5, 6);
    rotateSide(1, 4, 5, 6, 4, 4, 5, 6);
    rotateSide(4, 4, 5, 6, 3, 4, 5, 6);

    bitboard[3] = (bitboard[3] & ~(one_8 << (8 * 4))) | (clr1 << (8 * 4));
    bitboard[3] = (bitboard[3] & ~(one_8 << (8 * 5))) | (clr2 << (8 * 5));
    bitboard[3] = (bitboard[3] & ~(one_8 << (8 * 6))) | (clr3 << (8 * 6));

    return *this;
}

RubiksCube &RubiksCubeBitboard::dPrime()
{
    d();
    d();
    d();

    return *this;
}

RubiksCube &RubiksCubeBitboard::d2()
{
    d();
    d();

    return *this;
}

//-------------------------------------
// Operators
//-------------------------------------

bool RubiksCubeBitboard::operator==(const RubiksCubeBitboard &other) const
{
    for (int i = 0; i < 6; i++)
    {
        if (bitboard[i] != other.bitboard[i])
            return false;
    }

    return true;
}

RubiksCubeBitboard &
RubiksCubeBitboard::operator=(const RubiksCubeBitboard &other)
{
    if (this == &other)
        return *this;

    for (int i = 0; i < 6; i++)
    {
        bitboard[i] = other.bitboard[i];
    }

    return *this;
}

//-------------------------------------
// Corner Encoding
//-------------------------------------

uint64_t RubiksCubeBitboard::getCorners()
{
    uint64_t ret = 0;

    std::string topFrontRight;
    topFrontRight += getColorLetter(getColor(FACE::UP, 2, 2));
    topFrontRight += getColorLetter(getColor(FACE::FRONT, 0, 2));
    topFrontRight += getColorLetter(getColor(FACE::RIGHT, 0, 0));

    std::string topFrontLeft;
    topFrontLeft += getColorLetter(getColor(FACE::UP, 2, 0));
    topFrontLeft += getColorLetter(getColor(FACE::FRONT, 0, 0));
    topFrontLeft += getColorLetter(getColor(FACE::LEFT, 0, 2));

    std::string topBackRight;
    topBackRight += getColorLetter(getColor(FACE::UP, 0, 2));
    topBackRight += getColorLetter(getColor(FACE::BACK, 0, 0));
    topBackRight += getColorLetter(getColor(FACE::RIGHT, 0, 2));

    std::string topBackLeft;
    topBackLeft += getColorLetter(getColor(FACE::UP, 0, 0));
    topBackLeft += getColorLetter(getColor(FACE::BACK, 0, 2));
    topBackLeft += getColorLetter(getColor(FACE::LEFT, 0, 0));

    std::string bottomFrontRight;
    bottomFrontRight += getColorLetter(getColor(FACE::DOWN, 0, 2));
    bottomFrontRight += getColorLetter(getColor(FACE::FRONT, 2, 2));
    bottomFrontRight += getColorLetter(getColor(FACE::RIGHT, 2, 0));

    std::string bottomFrontLeft;
    bottomFrontLeft += getColorLetter(getColor(FACE::DOWN, 0, 0));
    bottomFrontLeft += getColorLetter(getColor(FACE::FRONT, 2, 0));
    bottomFrontLeft += getColorLetter(getColor(FACE::LEFT, 2, 2));

    std::string bottomBackRight;
    bottomBackRight += getColorLetter(getColor(FACE::DOWN, 2, 2));
    bottomBackRight += getColorLetter(getColor(FACE::BACK, 2, 0));
    bottomBackRight += getColorLetter(getColor(FACE::RIGHT, 2, 2));

    std::string bottomBackLeft;
    bottomBackLeft += getColorLetter(getColor(FACE::DOWN, 2, 0));
    bottomBackLeft += getColorLetter(getColor(FACE::BACK, 2, 2));
    bottomBackLeft += getColorLetter(getColor(FACE::LEFT, 2, 0));

    ret |= get5bitCorner(topFrontRight);
    ret <<= 5;

    ret |= get5bitCorner(topFrontLeft);
    ret <<= 5;

    ret |= get5bitCorner(topBackRight);
    ret <<= 5;

    ret |= get5bitCorner(topBackLeft);
    ret <<= 5;

    ret |= get5bitCorner(bottomFrontRight);
    ret <<= 5;

    ret |= get5bitCorner(bottomFrontLeft);
    ret <<= 5;

    ret |= get5bitCorner(bottomBackRight);
    ret <<= 5;

    ret |= get5bitCorner(bottomBackLeft);

    return ret;
}

//-------------------------------------
// Hash
//-------------------------------------

std::size_t HashBitboard::operator()(const RubiksCubeBitboard &cube) const
{
    uint64_t hash = cube.bitboard[0];

    for (int i = 1; i < 6; i++)
    {
        hash ^= cube.bitboard[i];
    }

    return static_cast<std::size_t>(hash);
}