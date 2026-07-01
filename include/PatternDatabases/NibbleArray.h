#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

class NibbleArray
{
private:
    std::size_t size;

    std::vector<uint8_t> dataArray;

public:
    explicit NibbleArray(std::size_t size,
                         uint8_t value = 0xFF);

    uint8_t get(std::size_t position) const;

    void set(std::size_t position,
             uint8_t value);

    unsigned char *data();

    const unsigned char *data() const;

    std::size_t storageSize() const;

    void inflate(std::vector<uint8_t> &destination) const;

    void reset(uint8_t value = 0xFF);
};