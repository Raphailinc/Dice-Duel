# Dice Duel

[English](README.md) · [Русский](README.ru.md)

A console game and C++ learning project that separates game rules from command-line interaction.

## What it does

- Play a configurable number of rounds against the computer.
- Set a seed for reproducible runs.
- Use automatic mode for a non-interactive game.
- Test the game model through CTest.

## Run locally

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/dice_duel_cli --rounds 4 --seed 42 --auto
```

## Checks

```bash
ctest --test-dir build --output-on-failure
```

## Scope and implementation notes

Requires a C++17 compiler and CMake. This is a local simulation/game exercise.
