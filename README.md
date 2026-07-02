# Rubik's Cube Solver

A 3x3 Rubik's Cube solver in modern C++17. It represents the cube as a
compact bitboard, finds optimal-ish solutions with IDA* guided by a
precomputed corner pattern database, and includes a second, simpler cube
model used purely as a correctness reference for testing.

```
Scramble Depth : 9
Example Scramble : L2 R U D2 U2 R2 D' U D2
Average Time            : 218 ms
Average Solution Length : 8.6
```

## Table of contents

- [Quick start](#quick-start)
- [How it works](#how-it-works)
  - [Cube representation](#cube-representation)
  - [Search algorithm](#search-algorithm)
  - [Pattern database](#pattern-database)
- [Project layout](#project-layout)
- [Building](#building)
- [Running](#running)
- [Performance](#performance)
- [The R-move bug](#the-r-move-bug-what-happened-and-how-it-was-found)
- [Other fixes](#other-fixes)
- [Testing / validating changes](#testing--validating-changes)
- [Extending this project](#extending-this-project)
- [Known limitations](#known-limitations)

## Quick start

```bash
cmake -B build
cmake --build build
./build/RubiksCubeSolver
```

Run from the **project root**, not from inside `build/` — the solver
loads `data/cornerPatternDB.bin` using a path relative to the current
working directory. If it can't find the file, it throws a clear
`std::runtime_error` instead of degrading silently.

## How it works

### Cube representation

The cube has two independent implementations behind a shared abstract
interface (`include/Model/RubiksCube.h`), so solvers can be written
generically:

| Class | Storage | Purpose |
|---|---|---|
| `RubiksCubeBitboard` | Six `uint64_t`, one per face, 8 bytes (one per non-center sticker) | Fast — used for all real solving |
| `RubiksCube3dArray` | Plain `char[6][3][3]` | Simple, easy to verify by inspection — used only as a trusted reference for testing |

Every sticker position within a face is numbered 0–8 going clockwise
from the top-left, with 8 reserved for the (never-moving) center:

```
0 1 2
7 8 3
6 5 4
```

A move like `R` (turn the right face clockwise) is implemented as a
handful of bit shifts and masks: rotate the RIGHT face's own byte in
place, then cycle 3-sticker strips between UP, FRONT, DOWN, and BACK.
Because everything is packed into 64-bit integers, a move is a handful
of ALU operations rather than an array-copy loop — this is what makes
20+ move IDA* searches, each trying millions of candidate move
sequences, fast enough to run in milliseconds to low seconds.

`RubiksCube3dArray` performs the same logical rotations but with plain
array indexing, which is much easier to read and verify by hand. It's
never used for real solving (it's noticeably slower), only to
cross-check that the bitboard model's bit-twiddling is doing the right
thing — see [The R-move bug](#the-r-move-bug-what-happened-and-how-it-was-found).

### Search algorithm

The real solver is `IDAstarSolver`
(`include/Solver/IDAStar.h`) — iterative-deepening A*:

1. Start with a bound equal to the heuristic estimate for the scrambled
   cube (how many moves the corners alone need, at minimum).
2. Do a best-first search (ordered by `depth + heuristic`), but abandon
   any branch whose `depth + heuristic` exceeds the current bound.
3. If nothing was found, raise the bound to the smallest `depth +
   heuristic` value seen among abandoned branches, and search again.
4. Repeat until the solved state is found.

Because the heuristic (see below) never overestimates the true
remaining distance within its computed range, the first solution IDA*
finds is provably optimal — no shorter solution exists.

Simpler alternatives also exist for comparison or small scrambles:
`BFS`, `DFS`, `IDDFS` (`include/Solver/`), all operating on
`RubiksCube3dArray`. These don't use the pattern database and are only
practical for shallow scrambles (a handful of moves) before search
space size makes them impractically slow.

### Pattern database

A **pattern database** is a precomputed lookup table: for every
possible state of *some subset* of the cube (here, just the 8 corner
pieces — their positions and orientations, ignoring the 12 edges
entirely), it stores the minimum number of moves needed to solve that
subset in isolation. Because solving the corners alone can never take
*more* moves than solving the whole cube, this number is always a safe
(admissible) lower bound on the true distance-to-solve — which is
exactly the property IDA* needs to prune search branches aggressively
without ever discarding the optimal solution.

It's built once, offline, by `CornerDBMaker::bfsAndStore()`
(`src/PatternDatabases/CornerDBMaker.cpp`): starting from the solved
cube, breadth-first search outward through all 18 possible moves,
recording the first (i.e. shortest) distance at which each corner
state is reached. The result — a distance value from 0 to 8 for every
corner state reachable within 8 moves — is packed 2-per-byte (a nibble
each, since the values are small) into `data/cornerPatternDB.bin`, a
~44 MB file.

Why depth 8 specifically, and not further? See
[Performance](#performance) and [Known limitations](#known-limitations).

## Project layout

```
include/
  Model/                  Cube representations
    RubiksCube.h            Abstract interface (moves, face colors, isSolved, ...)
    RubiksCubeBitboard.h    Fast bitboard implementation — used for solving
    RubiksCube3dArray.h     Simple array implementation — used as test reference
  Solver/                  Search algorithms
    IDAStar.h                The real solver (IDA* + pattern database)
    BFS.h / DFS.h / IDDFS.h  Simpler alternatives, no pattern database
  PatternDatabases/        Corner pattern database machinery
    CornerPatternDatabase.h  Maps a cube state -> an index into the database
    CornerDBMaker.h          Builds the database via breadth-first search
    PatternDatabase.h        Generic on-disk load/store for a database
    PermutationIndexer.h     Ranks a permutation of k-of-n symbols to an integer
    NibbleArray.h             Packs 4-bit values two-per-byte
    Math.h                   factorial / nPk / nCk helpers
src/                       .cpp files matching everything above
tools/
  generate_corner_db.cpp   Standalone executable to (re)build the pattern database
data/
  cornerPatternDB.bin      Prebuilt corner pattern database (checked in, ~44 MB)
CMakeLists.txt
```

## Building

Requires a C++17 compiler and CMake ≥ 3.16.

```bash
cmake -B build
cmake --build build
```

This produces two executables inside `build/`:

- **`RubiksCubeSolver`** — the demo/benchmark. Scrambles a cube to
  increasing depths (1–9 by default) and times how long IDA* takes to
  solve each one back, verifying every returned solution actually
  restores the cube before printing results.
- **`generate_corner_db`** — (re)generates `data/cornerPatternDB.bin`.
  You shouldn't need this day-to-day (the database is already checked
  in and deterministic — rebuilding it reproduces the exact same file
  byte-for-byte), but it's there if you want to experiment with a
  different search depth. See [Extending this project](#extending-this-project).

Rebuilding after a code change is just:

```bash
cmake --build build
```

You never need to `cd` into `build/` — run both the build and the
executable from the project root the whole time (`./build/RubiksCubeSolver`,
`./build/generate_corner_db`), and the relative path to `data/` will
always resolve correctly.

## Running

```bash
./build/RubiksCubeSolver
```

Each depth prints an example scramble plus the average solve time and
solution length across 5 random trials at that depth. If any solution
fails to actually solve the cube when replayed, the program prints the
offending scramble/solution and exits with a non-zero status — this
would indicate a correctness regression, and shouldn't ever happen on
an unmodified checkout.

To regenerate the pattern database (e.g. after changing its search
depth):

```bash
./build/generate_corner_db                      # writes data/cornerPatternDB.bin
./build/generate_corner_db path/to/output.bin    # or a custom path
```

Expect roughly 90 seconds and a few hundred MB of memory for the
default depth-8 search.

## Performance

Rough numbers from a single run (your machine will vary):

| Scramble depth | Avg. time | Avg. solution length |
|---|---|---|
| 1–7 | ~20 ms | matches scramble depth |
| 8 | ~300 ms | matches scramble depth |
| 9 | ~200–2500 ms (varies a lot) | ≤ scramble depth |

The jump around depth 8–9 isn't a fluke — it's exactly where the
pattern database's exact knowledge runs out (see
[Pattern database](#pattern-database)). Below that, the heuristic gives
IDA* a near-perfect lower bound and it prunes almost everything.
Beyond it, some states fall back to a much weaker heuristic and the
search has to work harder to prove optimality, which is also why
depth-9+ solve times vary more between individual scrambles than
shallower ones do.

## The R-move bug: what happened and how it was found

The most serious issue in this codebase, found and fixed during a
correctness audit: **the `R` move silently corrupted the cube** whenever
combined with certain other moves.

`RubiksCubeBitboard::r()` cycles 12 stickers across the UP, FRONT,
DOWN, and BACK faces: three helper calls handle UP→FRONT, FRONT→DOWN,
and DOWN→BACK, and a final manual write-back closes the loop from
BACK into UP. That final write used destination byte-indices `{0, 7,
6}` on the BACK face; they needed to be `{6, 7, 0}` to match the read
order used a few lines earlier in the same function, when DOWN was
populated from BACK.

The effect of that one swapped pair: instead of three **independent**
4-cycles (so that turning `R` four times returns to the original
state, exactly like a real cube), the 12 stickers formed **one single
12-cycle**. Applying `R` once still looked completely correct — the
bug is only visible after composing `R` with something else.

This is why it went unnoticed: on a solved cube, most of the stickers
involved are duplicates of each other (e.g. every UP-face sticker is
white), so a wrong cyclic *order* still produces the same *colors* —
`R` four times in a row still looked like it correctly returned to
solved. It only broke once the cube was scrambled and those stickers
stopped being interchangeable, e.g.:

```
Scramble : L F R2
"Solution": R2 F' L'   (the textbook-correct inverse — and yet, cube not solved)
```

### How it was isolated

1. Reproduced the failure with a minimal scramble/unscramble pair.
2. Verified all 18 individual moves were self-consistent in isolation
   (`move` then `invert` returns to solved; `move` four times returns
   to solved) — they all passed, which ruled out a broken single-move
   implementation and pointed at an *interaction* bug instead.
3. Tested all 324 ordered pairs of moves the same way — every pairing
   of `R`/`R'`/`R2` with `U`/`D`/`F`/`B` (and their variants) failed;
   `L` and all-non-`R` pairs passed.
4. Cross-validated `RubiksCubeBitboard` against `RubiksCube3dArray`
   (the simple, easy-to-verify reference model) sticker-by-sticker
   after each move, narrowing the first point of divergence down to
   the exact function.
5. Traced the exact bit-level read/write order in `r()` by hand and
   with instrumented debug builds, confirming the code executes
   exactly as written (i.e. not a memory-aliasing bug) — the bug was a
   genuine logic/index error, not an execution-order accident.
6. Built a labeled "marker" cube (every sticker holds a unique ID
   rather than a color) and ran the trusted `RubiksCube3dArray`
   rotation logic on it to derive the *exact* correct index mapping,
   then applied that same mapping to the bitboard implementation.

### How the fix was verified

- All 324 ordered move pairs: `move → move → invert → invert` returns
  to solved. **0 failures** (previously 36).
- All 324 ordered move pairs, compared directly against
  `RubiksCube3dArray` sticker-by-sticker (a strictly stronger check
  than self-consistency alone, since a *consistently wrong* mapping
  can still pass a self-consistency check). **0 mismatches**.
- 20,000 randomly generated scrambles, 1–100 moves each, compared
  against `RubiksCube3dArray` after every single move. **0
  mismatches.**
- The pattern database was regenerated from scratch afterward, since
  the original file had been built using the buggy move logic and was
  therefore unreliable.

## Other fixes

- **Silent failure on a missing pattern database.** The `IDAstarSolver`
  constructor previously called `cornerDB.fromFile(fileName)` and
  ignored the return value. If the file couldn't be found (e.g. the
  wrong working directory), the database silently stayed at its
  "unknown" sentinel for every state, and the solver would just get
  very slow instead of failing loudly. It now throws
  `std::runtime_error` naming the missing path.
- **Oversized, unexplained database allocation.**
  `CornerPatternDatabase` allocated space for 100,179,840 entries with
  no comment explaining the number. The actual corner state space is
  exactly `8! × 3⁷ = 88,179,840`. Fixed to the exact value (documented
  inline), shrinking the file from ~50 MB to ~44 MB.
- **Missing copy constructors.** Both cube models defined `operator=`
  but not a copy constructor — a Rule-of-Three violation that silently
  fell back to the compiler's implicit (and compiler-flagged
  deprecated) version. Both now explicitly `= default` a copy
  constructor.
- **~100 lines of dead, commented-out code** in `main.cpp` (an old,
  disabled validation harness) removed; the validation it used to do
  is documented and reproducible instead (see
  [Testing / validating changes](#testing--validating-changes)).
- **No way to (re)build the pattern database.** `CornerDBMaker` existed
  as a class but nothing in the project invoked it. Added
  `tools/generate_corner_db.cpp` and wired it into the CMake build.
- **Empty README**, and a `.gitignore` fix so the required
  `data/cornerPatternDB.bin` runtime asset isn't accidentally excluded
  by the blanket `*.bin` rule that used to be in place.

## Testing / validating changes

There's no formal test framework dependency (no GoogleTest/Catch2), but
if you change anything in `RubiksCubeBitboard`, rerun the same checks
used to find and verify the fix above. The pattern to follow:

```cpp
#include "Model/RubiksCube3dArray.h"
#include "Model/RubiksCubeBitboard.h"

bool matches(RubiksCube3dArray &a, RubiksCubeBitboard &b) {
    for (int f = 0; f < 6; f++)
        for (int r = 0; r < 3; r++)
            for (int c = 0; c < 3; c++)
                if (a.getColor((RubiksCube::FACE)f, r, c) !=
                    b.getColor((RubiksCube::FACE)f, r, c))
                    return false;
    return true;
}

// apply the same random sequence of moves to both models, then call
// matches(a, b) after every move — any regression will show up
// immediately as a mismatch.
```

Worth running:

1. **All 18×18 ordered move pairs**, both as a self-consistency check
   (`move → move → invert → invert` == solved) and as a direct
   cross-model comparison.
2. **A large batch of random scrambles** (a few thousand, up to 50–100
   moves each) comparing the two models after every move — this is
   what actually caught the R-move bug, since the 2-move pairwise
   tests alone weren't quite strong enough on their own to distinguish
   "internally self-consistent but wrong" from "actually correct."
3. **End-to-end solves** at each scramble depth, verified by replaying
   the returned solution and checking `isSolved()` — this is what
   `RubiksCubeSolver`'s main loop already does every time it runs.

## Extending this project

**Push the pattern database deeper.** Raise `kMaxDepth` in
`CornerDBMaker::bfsAndStore()`
(`src/PatternDatabases/CornerDBMaker.cpp`), then run
`./build/generate_corner_db`. Memory and time both grow quickly with
depth — depth 8 uses a few hundred MB and ~90 seconds; going further
can require several GB, since a full BFS to the true corner-only
maximum (~depth 11) needs to hold tens of millions of cube states in
memory simultaneously. If you have the RAM to spare, this is the
single biggest lever for making deep scrambles solve faster.

**Add an edge pattern database.** The standard, much stronger approach
(as in Korf's original algorithm) combines a corner pattern database
with one or more edge pattern databases and takes the *maximum* of all
of them as the heuristic at each node — edges alone carry a lot of
information a corners-only heuristic can't see. This is the natural
next step if you want genuinely fast optimal solves at 15+ move
scrambles. It would mean adding an `EdgePatternDatabase` alongside
`CornerPatternDatabase` (the existing `PatternDatabase` base class and
`PermutationIndexer` should both be directly reusable) and updating
`IDAstarSolver` to take the max of both estimates.

**Reduce IDA*'s memory use.** `IDAstarSolver` currently keeps full
`unordered_map`s of visited states and parent moves across an entire
bounded search, keyed by full cube objects. That's part of why very
deep scrambles (12+ moves) with a weak heuristic can use a lot of
memory. A more memory-frugal implementation would use a true recursive
IDA* (constant memory along the current path, no global visited set)
at the cost of potentially revisiting some states.

## Known limitations

- The corner-only heuristic (no edge pattern database) means scrambles
  deeper than ~9–10 moves get noticeably slower and more variable to
  solve optimally, and very deep scrambles (12+ moves) can use enough
  memory to be impractical on modest machines. See
  [Extending this project](#extending-this-project) for the two most
  impactful ways to address this.
- `BFS` / `DFS` / `IDDFS` operate on `RubiksCube3dArray` and don't use
  the pattern database, so they're only practical for shallow
  scrambles (a handful of moves) before the search space makes them
  impractically slow.
- The demo (`RubiksCubeSolver`) defaults to scramble depths 1–9 for a
  smooth out-of-the-box run on modest hardware; this is a `constexpr`
  at the top of `src/main.cpp` if you want to push it further.
