#include "PatternDatabases/CornerPatternDatabase.h"

//-------------------------------------
// Constructors
//-------------------------------------

// 8! permutations x 3^7 independent corner orientations = 88,179,840
// distinct reachable corner states.
namespace
{
    constexpr std::size_t kCornerDatabaseSize = 88179840;
}

CornerPatternDatabase::CornerPatternDatabase()
    : PatternDatabase(kCornerDatabaseSize)
{
}

CornerPatternDatabase::CornerPatternDatabase(uint8_t initialValue)
    : PatternDatabase(kCornerDatabaseSize, initialValue)
{
}

//-------------------------------------
// Database Index
//-------------------------------------

uint32_t CornerPatternDatabase::getDatabaseIndex(
    const RubiksCube &cube) const
{
    const std::array<uint8_t, 8> cornerPermutation = {
        cube.getCornerIndex(0),
        cube.getCornerIndex(1),
        cube.getCornerIndex(2),
        cube.getCornerIndex(3),
        cube.getCornerIndex(4),
        cube.getCornerIndex(5),
        cube.getCornerIndex(6),
        cube.getCornerIndex(7)
    };

    const uint32_t rank =
        permutationIndexer.rank(cornerPermutation);

    const std::array<uint8_t, 7> cornerOrientations = {
        cube.getCornerOrientation(0),
        cube.getCornerOrientation(1),
        cube.getCornerOrientation(2),
        cube.getCornerOrientation(3),
        cube.getCornerOrientation(4),
        cube.getCornerOrientation(5),
        cube.getCornerOrientation(6)
    };

    const uint32_t orientationIndex =
          cornerOrientations[0] * 729
        + cornerOrientations[1] * 243
        + cornerOrientations[2] * 81
        + cornerOrientations[3] * 27
        + cornerOrientations[4] * 9
        + cornerOrientations[5] * 3
        + cornerOrientations[6];

    return (rank * 2187) + orientationIndex;
}