# GitHub Copilot instructions — structural-column-solver

## Project snapshot 🧭
- Single-file C++ CLI application: `columnsolver.cpp` is the entire program and the canonical source of truth.  
- No build files, tests, or CI present; `README.md` contains only a short project description.

## What this agent must know first (quick summary) ✅
- The code uses outdated/non‑portable constructs: `#include <iostream.h>`, `#include <conio.h>`, `getch()`, `clrscr()` and heavy use of `goto`/labels for menu flow. These must be modernized before the program can be compiled on macOS/Linux.
- Core domain logic: calculations for Straight / Crooked / Eccentric columns using Euler and Johnson formulas (look for "Euler", "Johnson", `slenderness`, `Column constants`).
- Important file: `columnsolver.cpp` — read top-to-bottom; all behavior is implemented inline.

## High‑priority tasks for the agent (ranked) 🔧
1. Port to modern C++ so it builds on macOS/Linux:
   - Replace `<iostream.h>` with `<iostream>` and use `std::` (or `using namespace std;`).
   - Remove `<conio.h>` and replace `getch()` / `clrscr()` with portable alternatives (e.g. `std::cin.get()` / `std::system("clear")` or remove screen-clear behavior).
   - Replace `M_PI`/magic constants with a single `constexpr double PI = 3.141592653589793;` for consistency.
2. Fix obvious logic/initialization bugs observed in formulas (examples in code):
   - `pa=(((pa*pa)+c2)/c1);` and `paa=((paa*paa)+c2)/c1;` use `pa`/`paa` on RHS before assignment — reproduce and correct.
3. Replace menu `goto`/labels with structured control flow (functions + loop) to improve testability.
4. Add a small build setup (Makefile or CMake) and a minimal unit test harness (Google Test or small doctest) covering: menu branches and both Euler/Johnson branches.
5. Add CI workflow that builds and runs the tests on Linux/macOS.

## Observable code patterns & examples (do not invent) 📌
- Single-entrypoint CLI: `int main()` contains the whole UI and calculations (search for `menu:`, `back:`, `straight:` labels).
- Interactive input via `cin`/`cout` — no file I/O or args parsing.
- Mixed numeric constants: both `M_PI` and raw constants (`3.14`, `9.869`, `39.478`) are present — unify constants.
- Repeated variable blocks per case: e.g. `float r, rr, b, h, d, sr, k, l, cc, s, e, a, p, ...` are redeclared in multiple switch branches.

## Known pitfalls to test for (explicit examples) ⚠️
- Branches that compute `pa`/`paa` appear to read uninitialized values — create unit tests that exercise Crooked/Eccentric flows to reproduce.
- Platform-specific headers (`<conio.h>`) will cause build failures on macOS.
- Numerical edge-cases: when slenderness ratio (`sr`) is close to the column constant (`cc`) — add tests around that threshold.

## How to compile & run (after porting) — example commands ▶️
- Build: `g++ -std=c++17 columnsolver.cpp -O2 -o columnsolver`
- Run: `./columnsolver` and exercise the interactive menu (1–3 options).

## PR guidance for contributors (what reviewers should check) 🔁
- Porting PRs must include a green build + at least one unit test reproducing the old behavior (or a corrected behavior with a clear migration note).
- Fixes to formulas must include the math reference (source or derivation) in the PR description.
- Avoid changing numeric results without adding tests or a short explanation.

## Search hints (where to look in this repo) 🔎
- `columnsolver.cpp` — menu labels (`menu:`, `straight:`, `crooked:`, `eccentric:`), Euler/Johnson formula code paths, and places with `M_PI` or `3.14`.
- `README.md` — high-level description only.

## Short-term actionable checklist for this repo (copy into issues) 📝
- [ ] Port code to modern C++ (replace headers, remove conio).  
- [ ] Fix uninitialized-variable/formula bugs and add unit tests that cover them.  
- [ ] Add a Makefile/CMake and a CI workflow (build + tests).  
- [ ] Refactor interactive menu into functions to enable unit testing.

---
If any part of the code's intended numeric formula or behavior is unclear, tell me which calculation or label (example: `crooked` → circular branch) and I will add clarification or open a PR that reproduces the failing case. Please confirm which of the high‑priority tasks you want me to implement first.