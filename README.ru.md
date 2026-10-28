# Dice Duel

[![CI](https://github.com/Raphailinc/Dice-Duel/actions/workflows/ci.yml/badge.svg)](https://github.com/Raphailinc/Dice-Duel/actions/workflows/ci.yml)

[English](README.md) · [Русский](README.ru.md)

Консольная игра на C++17 с отдельной моделью правил и командным интерфейсом.

## Возможности

- Настройка количества раундов против компьютера.
- Seed для воспроизводимого запуска.
- Автоматический режим без интерактивного ввода.
- Проверки игровой модели через CTest.

## Локальный запуск

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/dice_duel_cli --rounds 4 --seed 42 --auto
```

## Проверки

```bash
ctest --test-dir build --output-on-failure
```

## Условия запуска и границы проекта

Нужны компилятор C++17 и CMake. Это локальная игровая симуляция.
