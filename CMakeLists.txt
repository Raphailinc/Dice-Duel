cmake_minimum_required(VERSION 3.16)
project(dice-duel LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(dice_duel STATIC src/game.cpp)
target_include_directories(dice_duel PUBLIC src)

add_executable(dice_duel_cli src/main.cpp)
target_link_libraries(dice_duel_cli PRIVATE dice_duel)

enable_testing()
add_executable(dice_duel_tests tests/main.cpp tests/test_game.cpp)
target_include_directories(dice_duel_tests PRIVATE tests)
target_link_libraries(dice_duel_tests PRIVATE dice_duel)
add_test(NAME dice_duel_tests COMMAND dice_duel_tests)
