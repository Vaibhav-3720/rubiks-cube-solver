#pragma once

#include "Model/RubiksCube.h"
#include "PatternDatabases/NibbleArray.h"

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

class PatternDatabase
{
private:
    NibbleArray database;

    std::size_t size;
    std::size_t numItems;

    PatternDatabase();

public:
    explicit PatternDatabase(std::size_t size);

    PatternDatabase(std::size_t size,
                    uint8_t initialValue);

    virtual uint32_t getDatabaseIndex(const RubiksCube &cube) const = 0;

    virtual bool setNumMoves(const RubiksCube &cube,
                             uint8_t numMoves);

    virtual bool setNumMoves(uint32_t index,
                             uint8_t numMoves);

    virtual uint8_t getNumMoves(const RubiksCube &cube) const;

    virtual uint8_t getNumMoves(uint32_t index) const;

    virtual std::size_t getSize() const;

    virtual std::size_t getNumItems() const;

    virtual bool isFull() const;

    virtual void toFile(const std::string &filePath) const;

    virtual bool fromFile(const std::string &filePath);

    virtual std::vector<uint8_t> inflate() const;

    virtual void reset();

    virtual ~PatternDatabase() = default;
};