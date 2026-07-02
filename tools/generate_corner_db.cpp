// Regenerates the corner pattern database used by the IDA* solver as its
// search heuristic.
//
// Usage:
//   generate_corner_db [output_path]
//
// If no path is given, data/cornerPatternDB.bin is (re)written relative
// to the current working directory. This performs a breadth-first search
// over corner permutation+orientation states up to a fixed depth (see
// CornerDBMaker::bfsAndStore) and takes roughly one to two minutes,
// using on the order of a few hundred MB of memory.

#include "PatternDatabases/CornerDBMaker.h"

#include <chrono>
#include <iostream>

int main(int argc, char *argv[])
{
    const std::string outputPath =
        (argc > 1) ? argv[1] : "data/cornerPatternDB.bin";

    std::cout << "Generating corner pattern database -> "
              << outputPath << "\n\n";

    const auto start = std::chrono::steady_clock::now();

    CornerDBMaker maker(outputPath);
    maker.bfsAndStore();

    const auto end = std::chrono::steady_clock::now();
    const auto seconds =
        std::chrono::duration_cast<std::chrono::seconds>(end - start)
            .count();

    std::cout << "\nDone in " << seconds << "s\n";

    return 0;
}
