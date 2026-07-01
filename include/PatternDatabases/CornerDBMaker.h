#pragma once

#include "Model/RubiksCubeBitboard.h"
#include "PatternDatabases/CornerPatternDatabase.h"

#include <cstdint>
#include <string>

class CornerDBMaker
{
private:
    std::string fileName;

    CornerPatternDatabase cornerDatabase;

public:
    explicit CornerDBMaker(const std::string &fileName);

    CornerDBMaker(const std::string &fileName,
                  uint8_t initialValue);

    bool bfsAndStore();
};