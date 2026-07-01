#pragma once

#include "PatternDatabases/Math.h"

#include <array>
#include <bitset>
#include <cstddef>
#include <cstdint>

template <std::size_t N, std::size_t K = N>
class PermutationIndexer
{
private:
    // Lookup table storing the number of set bits for each N-bit value.
    std::array<uint32_t, (1u << N) - 1> onesCountLookup;

    // Precomputed factorial/pick values.
    std::array<uint32_t, K> factorials;

public:
    PermutationIndexer()
    {
        for (uint32_t i = 0; i < (1u << N) - 1; ++i)
        {
            std::bitset<N> bits(i);
            onesCountLookup[i] = bits.count();
        }

        for (uint32_t i = 0; i < K; ++i)
        {
            factorials[i] = pick(N - 1 - i, K - 1 - i);
        }
    }

    uint32_t rank(const std::array<uint8_t, K> &permutation) const
    {
        std::array<uint32_t, K> lehmerCode{};
        std::bitset<N> seen;

        lehmerCode[0] = permutation[0];
        seen[N - 1 - permutation[0]] = true;

        for (uint32_t i = 1; i < K; ++i)
        {
            seen[N - 1 - permutation[i]] = true;

            uint32_t numSeen =
                onesCountLookup[
                    seen.to_ulong() >> (N - permutation[i])];

            lehmerCode[i] = permutation[i] - numSeen;
        }

        uint32_t index = 0;

        for (uint32_t i = 0; i < K; ++i)
        {
            index += lehmerCode[i] * factorials[i];
        }

        return index;
    }
};