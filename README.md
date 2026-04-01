
# rdfile

Lightweight utilities and tools for reading/writing and processing RD-style files.

## Overview

This repository contains a small C++ project (CMake-based) with utilities located under `src/` and compiled binaries in `bin/`.

## Requirements

- CMake 3.20
- A C++23-capable compiler (MSVC / clang / gcc)
- Ninja (recommended) or another generator

## Build

From the repository root:

```bash
mkdir -p build
cmake -S . -B build -G Ninja
cmake --build build --config Release
```

Binaries will be placed under `bin/` (or `build/` output depending on generator).

## Run

Run the produced executable from `bin/` or the build output directory, for example:

```bash
./bin/rdfile.exe
```

Replace `rdfile.exe` with the actual binary name produced by the build.

## Project layout

- `src/` — main sources
- `lib/` — libraries
- `docs/` — documentation
- `build/`, `bin/` — build and output artifacts

## Contributing

Contributions are welcome. Please open issues or PRs with a clear description and tests where appropriate.