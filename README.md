<h1 align="center">Structural Column Solver</h1>

<p align="center">
  <img alt="C++17" src="https://img.shields.io/badge/C%2B%2B-17-blue?logo=c%2B%2B" />
  <img alt="status" src="https://img.shields.io/badge/status-WIP-yellow" />
  <img alt="platforms" src="https://img.shields.io/badge/platform-macOS%20%7C%20Linux-lightgrey" />
</p>

A concise, single-file C++17 command-line utility for estimating column behaviour (Straight, Crooked, Eccentric) using classical Euler and Johnson formulas. The project is intentionally small and focused so numerical corrections and tests can be added quickly. Originally developed as a university coursework project.

**Highlights**
- Single-file canonical implementation: `columnsolver.cpp`.
- Clear numeric helpers: `euler_load_from_sr()`, `johnson_load()`, `solve_quadratic_small_root()`.
- Portable C++17 (no platform-specific headers), input validation, and guarded numerics.

## Quick start
Requirements: a C++17 toolchain (g++ or clang++) on macOS or Linux.

Build with the provided Makefile:

```sh
make build
```

Or compile directly:

```sh
g++ -std=c++17 columnsolver.cpp -O2 -o columnsolver
```

Run:

```sh
./columnsolver
```

Interactive example: choose a menu option (1 = Straight, 2 = Crooked, 3 = Eccentric), then follow prompts for geometry and material inputs. The program prints radius of gyration, slenderness ratio, column constant, and recommended Euler/Johnson loads.

## Project layout
- `columnsolver.cpp` — canonical source; numerical helpers and CLI handlers (`handle_straight()`, `handle_crooked()`, `handle_eccentric()`).
- `Makefile` — build/run/clean/test targets (`test` is a placeholder until tests are added).

## Developer guidance
- Start with `columnsolver.cpp` helpers if you need to adjust formulas or tolerances.
- Use `double` precision and small tolerances (e.g., 1e-6) for unit tests that compare floating-point results.

## Tests & CI (recommended next steps)
- Add unit tests (recommended: `doctest` for single-file convenience or `Google Test` for larger suites). Create tests that reproduce the original pa/paa numeric issues and assert corrected behavior.
- Add GitHub Actions CI that builds on Ubuntu and macOS and runs tests. Include sanitizer builds (ASan/UBSan) for numeric/runtime checks.

## Contribution ideas
1. Add unit tests validating Euler vs Johnson branches and edge-case slenderness ratios.
2. Add a CI workflow that runs `make build` and `make test` on `ubuntu-latest` and `macos-latest`.
3. Split numeric helpers into a small header/module for easier testing.

## License
This project is licensed under the MIT License — see `LICENSE` for details.

---

If you'd like, I can now add unit tests (recommended first step) or create a GitHub Actions CI workflow—which should I do next? (reply `tests`, `ci`, or `pr`)