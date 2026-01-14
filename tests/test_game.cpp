#include "game.hpp"
#include "doctest/doctest.h"
#include <random>

DOCTEST_TESTCASE(test_deterministic_game) {
    std::mt19937 rng(42);
    auto result = play_game(rng, 3);
    CHECK(result.rounds.size() == 3);
    CHECK(result.player_score > 0);
    CHECK(result.cpu_score > 0);
    CHECK(result.winner() == "player" || result.winner() == "cpu" || result.winner() == "draw");
}

DOCTEST_TESTCASE(test_winner_resolution) {
    GameResult res;
    res.player_score = 10;
    res.cpu_score = 8;
    CHECK(res.winner() == "player");
    res.cpu_score = 12;
    CHECK(res.winner() == "cpu");
    res.cpu_score = 10;
    CHECK(res.winner() == "draw");
}
