#include "game.hpp"

#include <random>

Roll roll_dice(std::mt19937 &rng) {
    std::uniform_int_distribution<int> dist(1, 6);
    return Roll{dist(rng), dist(rng)};
}

GameResult play_game(std::mt19937 &rng, int rounds) {
    if (rounds <= 0) {
        return {};
    }

    GameResult result;
    std::bernoulli_distribution start_dist(0.5);
    result.player_starts = start_dist(rng);

    result.rounds.reserve(static_cast<std::size_t>(rounds));

    for (int i = 0; i < rounds; ++i) {
        RoundResult rr{};
        if (result.player_starts) {
            rr.player_roll = roll_dice(rng);
            rr.cpu_roll = roll_dice(rng);
        } else {
            rr.cpu_roll = roll_dice(rng);
            rr.player_roll = roll_dice(rng);
        }

        result.player_score += rr.player_roll.total();
        result.cpu_score += rr.cpu_roll.total();

        result.rounds.push_back(rr);
    }

    return result;
}
