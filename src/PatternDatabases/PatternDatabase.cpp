#include "PatternDatabases/PatternDatabase.h"

#include <fstream>
#include <stdexcept>

//-------------------------------------
// Constructors
//-------------------------------------

PatternDatabase::PatternDatabase(std::size_t size)
    : database(size, 0xFF),
      size(size),
      numItems(0)
{
}

PatternDatabase::PatternDatabase(std::size_t size,
                                 uint8_t initialValue)
    : database(size, initialValue),
      size(size),
      numItems(0)
{
}

//-------------------------------------
// Database Operations
//-------------------------------------

bool PatternDatabase::setNumMoves(uint32_t index,
                                  uint8_t numMoves)
{
    const uint8_t oldMoves = getNumMoves(index);

    if (oldMoves == 0xF)
    {
        ++numItems;
    }

    if (oldMoves > numMoves)
    {
        database.set(index, numMoves);
        return true;
    }

    return false;
}

bool PatternDatabase::setNumMoves(const RubiksCube &cube,
                                  uint8_t numMoves)
{
    return setNumMoves(getDatabaseIndex(cube), numMoves);
}

uint8_t PatternDatabase::getNumMoves(uint32_t index) const
{
    return database.get(index);
}

uint8_t PatternDatabase::getNumMoves(const RubiksCube &cube) const
{
    return getNumMoves(getDatabaseIndex(cube));
}

//-------------------------------------
// Information
//-------------------------------------

std::size_t PatternDatabase::getSize() const
{
    return size;
}

std::size_t PatternDatabase::getNumItems() const
{
    return numItems;
}

bool PatternDatabase::isFull() const
{
    return numItems == size;
}

//-------------------------------------
// File Operations
//-------------------------------------

void PatternDatabase::toFile(const std::string &filePath) const
{
    std::ofstream writer(
        filePath,
        std::ios::binary | std::ios::trunc);

    if (!writer)
    {
        throw std::runtime_error(
            "Failed to open database file for writing.");
    }

    writer.write(
        reinterpret_cast<const char *>(database.data()),
        database.storageSize());
}

bool PatternDatabase::fromFile(const std::string &filePath)
{
    std::ifstream reader(
        filePath,
        std::ios::binary | std::ios::ate);

    if (!reader)
    {
        return false;
    }

    const std::size_t fileSize =
        static_cast<std::size_t>(reader.tellg());

    if (fileSize != database.storageSize())
    {
        throw std::runtime_error(
            "Database file is corrupted.");
    }

    reader.seekg(0, std::ios::beg);

    reader.read(
        reinterpret_cast<char *>(database.data()),
        database.storageSize());

    numItems = size;

    return true;
}

//-------------------------------------
// Utility
//-------------------------------------

std::vector<uint8_t> PatternDatabase::inflate() const
{
    std::vector<uint8_t> inflated;

    database.inflate(inflated);

    return inflated;
}

void PatternDatabase::reset()
{
    if (numItems == 0)
    {
        return;
    }

    database.reset(0xFF);
    numItems = 0;
}