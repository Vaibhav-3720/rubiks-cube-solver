#include "Model/RubiksCube3dArray.h"

#include <functional>
#include <string>

void RubiksCube3dArray::rotateFace(int face)
{
    char temp[3][3];

    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            temp[row][col] = cube[face][row][col];
        }
    }

    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            cube[face][row][col] = temp[2 - col][row];
        }
    }
}
RubiksCube3dArray::RubiksCube3dArray()
{
    for (int face = 0; face < 6; face++)
    {
        for (int row = 0; row < 3; row++)
        {
            for (int col = 0; col < 3; col++)
            {
                cube[face][row][col] =
                    getColorLetter(static_cast<COLOR>(face));
            }
        }
    }
}

RubiksCube::COLOR RubiksCube3dArray::getColor(
    FACE face,
    unsigned row,
    unsigned col) const
{
    const char color = cube[static_cast<int>(face)][row][col];

    switch (color)
    {
    case 'B':
        return COLOR::BLUE;

    case 'G':
        return COLOR::GREEN;

    case 'R':
        return COLOR::RED;

    case 'O':
        return COLOR::ORANGE;

    case 'Y':
        return COLOR::YELLOW;

    default:
        return COLOR::WHITE;
    }
}
bool RubiksCube3dArray::isSolved() const
{
    for (int face = 0; face < 6; face++)
    {
        const char expected =
            getColorLetter(static_cast<COLOR>(face));

        for (int row = 0; row < 3; row++)
        {
            for (int col = 0; col < 3; col++)
            {
                if (cube[face][row][col] != expected)
                    return false;
            }
        }
    }

    return true;
}
RubiksCube &RubiksCube3dArray::u()
{
    rotateFace(0);

    char temp[3];

    for (int i = 0; i < 3; i++)
        temp[i] = cube[4][0][2 - i];

    for (int i = 0; i < 3; i++)
        cube[4][0][2 - i] = cube[1][0][2 - i];

    for (int i = 0; i < 3; i++)
        cube[1][0][2 - i] = cube[2][0][2 - i];

    for (int i = 0; i < 3; i++)
        cube[2][0][2 - i] = cube[3][0][2 - i];

    for (int i = 0; i < 3; i++)
        cube[3][0][2 - i] = temp[i];

    return *this;
}

RubiksCube &RubiksCube3dArray::uPrime()
{
    u();
    u();
    u();

    return *this;
}

RubiksCube &RubiksCube3dArray::u2()
{
    u();
    u();

    return *this;
}

RubiksCube &RubiksCube3dArray::l()
{
    rotateFace(1);

    char temp[3];

    for (int i = 0; i < 3; i++)
        temp[i] = cube[0][i][0];

    for (int i = 0; i < 3; i++)
        cube[0][i][0] = cube[4][2 - i][2];

    for (int i = 0; i < 3; i++)
        cube[4][2 - i][2] = cube[5][i][0];

    for (int i = 0; i < 3; i++)
        cube[5][i][0] = cube[2][i][0];

    for (int i = 0; i < 3; i++)
        cube[2][i][0] = temp[i];

    return *this;
}

RubiksCube &RubiksCube3dArray::lPrime()
{
    l();
    l();
    l();

    return *this;
}

RubiksCube &RubiksCube3dArray::l2()
{
    l();
    l();

    return *this;
}

RubiksCube &RubiksCube3dArray::f()
{
    rotateFace(2);

    char temp[3];

    for (int i = 0; i < 3; i++)
        temp[i] = cube[0][2][i];

    for (int i = 0; i < 3; i++)
        cube[0][2][i] = cube[1][2 - i][2];

    for (int i = 0; i < 3; i++)
        cube[1][2 - i][2] = cube[5][0][2 - i];

    for (int i = 0; i < 3; i++)
        cube[5][0][2 - i] = cube[3][i][0];

    for (int i = 0; i < 3; i++)
        cube[3][i][0] = temp[i];

    return *this;
}

RubiksCube &RubiksCube3dArray::fPrime()
{
    f();
    f();
    f();

    return *this;
}

RubiksCube &RubiksCube3dArray::f2()
{
    f();
    f();

    return *this;
}
RubiksCube &RubiksCube3dArray::r()
{
    rotateFace(3);

    char temp[3];

    for (int i = 0; i < 3; i++)
        temp[i] = cube[0][2 - i][2];

    for (int i = 0; i < 3; i++)
        cube[0][2 - i][2] = cube[2][2 - i][2];

    for (int i = 0; i < 3; i++)
        cube[2][2 - i][2] = cube[5][2 - i][2];

    for (int i = 0; i < 3; i++)
        cube[5][2 - i][2] = cube[4][i][0];

    for (int i = 0; i < 3; i++)
        cube[4][i][0] = temp[i];

    return *this;
}

RubiksCube &RubiksCube3dArray::rPrime()
{
    r();
    r();
    r();

    return *this;
}

RubiksCube &RubiksCube3dArray::r2()
{
    r();
    r();

    return *this;
}

RubiksCube &RubiksCube3dArray::b()
{
    rotateFace(4);

    char temp[3];

    for (int i = 0; i < 3; i++)
        temp[i] = cube[0][0][2 - i];

    for (int i = 0; i < 3; i++)
        cube[0][0][2 - i] = cube[3][2 - i][2];

    for (int i = 0; i < 3; i++)
        cube[3][2 - i][2] = cube[5][2][i];

    for (int i = 0; i < 3; i++)
        cube[5][2][i] = cube[1][i][0];

    for (int i = 0; i < 3; i++)
        cube[1][i][0] = temp[i];

    return *this;
}

RubiksCube &RubiksCube3dArray::bPrime()
{
    b();
    b();
    b();

    return *this;
}

RubiksCube &RubiksCube3dArray::b2()
{
    b();
    b();

    return *this;
}

RubiksCube &RubiksCube3dArray::d()
{
    rotateFace(5);

    char temp[3];

    for (int i = 0; i < 3; i++)
        temp[i] = cube[2][2][i];

    for (int i = 0; i < 3; i++)
        cube[2][2][i] = cube[1][2][i];

    for (int i = 0; i < 3; i++)
        cube[1][2][i] = cube[4][2][i];

    for (int i = 0; i < 3; i++)
        cube[4][2][i] = cube[3][2][i];

    for (int i = 0; i < 3; i++)
        cube[3][2][i] = temp[i];

    return *this;
}

RubiksCube &RubiksCube3dArray::dPrime()
{
    d();
    d();
    d();

    return *this;
}

RubiksCube &RubiksCube3dArray::d2()
{
    d();
    d();

    return *this;
}
bool RubiksCube3dArray::operator==(const RubiksCube3dArray &other) const
{
    for (int face = 0; face < 6; face++)
    {
        for (int row = 0; row < 3; row++)
        {
            for (int col = 0; col < 3; col++)
            {
                if (cube[face][row][col] != other.cube[face][row][col])
                    return false;
            }
        }
    }

    return true;
}
RubiksCube3dArray &RubiksCube3dArray::operator=(const RubiksCube3dArray &other)
{
    if (this == &other)
        return *this;

    for (int face = 0; face < 6; face++)
    {
        for (int row = 0; row < 3; row++)
        {
            for (int col = 0; col < 3; col++)
            {
                cube[face][row][col] = other.cube[face][row][col];
            }
        }
    }

    return *this;
}
std::size_t Hash3d::operator()(const RubiksCube3dArray &cube) const
{
    std::string state;

    state.reserve(54);

    for (int face = 0; face < 6; face++)
    {
        for (int row = 0; row < 3; row++)
        {
            for (int col = 0; col < 3; col++)
            {
                state += cube.cube[face][row][col];
            }
        }
    }

    return std::hash<std::string>{}(state);
}