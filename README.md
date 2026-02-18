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

## Project structure
Below is the repository layout and purpose of each top-level item.

```
columnsolver.cpp          # Canonical single-file source: numeric helpers + CLI handlers
Makefile                  # Build/run/clean/test helper targets
README.md                 # Project overview, quick start, and developer notes
LICENSE                   # MIT license (this project)
legacy_columnsolver.exe   # Original school submission (outdated) — kept for reference
.gitignore                # (ignored build artifacts and editor files)
```

Build artifacts and platform binaries (for example `columnsolver` or `columnsolver.exe`) are intentionally omitted from the repository and are listed in `.gitignore`. Build locally with `make build` or `g++` to produce the executable. Exception: `legacy_columnsolver.exe` is a checked-in historical binary — the original file submitted for coursework and now kept only for reference (outdated).

## Developer guidance
- Start with `columnsolver.cpp` helpers if you need to adjust formulas or tolerances.
- Use `double` precision and small tolerances (e.g., 1e-6) for unit tests that compare floating-point results.

