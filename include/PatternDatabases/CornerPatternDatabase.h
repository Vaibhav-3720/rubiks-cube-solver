#pragma once

#include "Model/RubiksCube.h"
#include "PatternDatabases/PatternDatabase.h"
#include "PatternDatabases/PermutationIndexer.h"

#include <cstdint>

class CornerPatternDatabase : public PatternDatabase
{
private:
    using Face = RubiksCube::FACE;

    PermutationIndexer<8> permutationIndexer;

public:
    CornerPatternDatabase();

    explicit CornerPatternDatabase(uint8_t initialValue);

    uint32_t getDatabaseIndex(const RubiksCube &cube) const override;
};