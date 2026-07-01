#include "PatternDatabases/NibbleArray.h"

#include <algorithm>
#include <cassert>

NibbleArray::NibbleArray(std::size_t size, uint8_t value)
    : size(size),
      dataArray(size / 2 + 1, value)
{
}

uint8_t NibbleArray::get(std::size_t position) const
{
    assert(position < size);

    const std::size_t index = position / 2;
    const uint8_t value = dataArray.at(index);

    if (position % 2 == 0)
    {
        return value >> 4;
    }

    return value & 0x0F;
}

void NibbleArray::set(std::size_t position, uint8_t value)
{
    assert(position < size);

    const std::size_t index = position / 2;
    uint8_t currentValue = dataArray.at(index);

    if (position % 2 == 0)
    {
        dataArray.at(index) =
            (currentValue & 0x0F) | (value << 4);
    }
    else
    {
        dataArray.at(index) =
            (currentValue & 0xF0) | (value & 0x0F);
    }
}

unsigned char *NibbleArray::data()
{
    return dataArray.data();
}

const unsigned char *NibbleArray::data() const
{
    return dataArray.data();
}

std::size_t NibbleArray::storageSize() const
{
    return dataArray.size();
}

void NibbleArray::inflate(std::vector<uint8_t> &destination) const
{
    destination.reserve(size);

    for (std::size_t i = 0; i < size; i++)
    {
        destination.push_back(get(i));
    }
}

void NibbleArray::reset(uint8_t value)
{
    std::fill(dataArray.begin(), dataArray.end(), value);
}