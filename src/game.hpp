#pragma once

#include <random>
#include <string>
#include <tuple>
#include <vector>

struct Roll {
    int die1;
    int die2;

    int total() const { return die1 + die2; }
};

struct RoundResult {
    Roll player_roll;
    Roll cpu_roll;
};

struct GameResult {
    int player_score{};
    int cpu_score{};
    bool player_starts{};
    std::vector<RoundResult> rounds{};

    std::string winner() const {
        if (player_score > cpu_score) return "player";
        if (cpu_score > player_score) return "cpu";
        return "draw";
    }
};

Roll roll_dice(std::mt19937 &rng);
GameResult play_game(std::mt19937 &rng, int rounds);
