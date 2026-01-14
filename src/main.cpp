#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>

#include "game.hpp"

namespace {

std::string die_face(int value) {
    switch (value) {
    case 1: return "[⚀]";
    case 2: return "[⚁]";
    case 3: return "[⚂]";
    case 4: return "[⚃]";
    case 5: return "[⚄]";
    case 6: return "[⚅]";
    default: return "[?]";
    }
}

void print_round(int index, const RoundResult &rr) {
    std::cout << "Раунд " << (index + 1) << ":\n";
    std::cout << "  Игрок: " << die_face(rr.player_roll.die1) << die_face(rr.player_roll.die2)
              << "  (+" << rr.player_roll.total() << ")\n";
    std::cout << "  Компьютер: " << die_face(rr.cpu_roll.die1) << die_face(rr.cpu_roll.die2)
              << "  (+" << rr.cpu_roll.total() << ")\n\n";
}

void print_banner() {
    std::cout << "===== Dice Duel =====\n"
              << "Бросьте кубы и обгоните соперника. По умолчанию 4 раунда.\n"
              << "Параметры: --rounds N, --seed X, --auto (без вопросов)\n\n";
}

} // namespace

int main(int argc, char *argv[]) {
    int rounds = 4;
    bool auto_mode = false;
    std::uint64_t seed = static_cast<std::uint64_t>(
        std::chrono::high_resolution_clock::now().time_since_epoch().count());

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--rounds" && i + 1 < argc) {
            rounds = std::max(1, std::stoi(argv[++i]));
        } else if (arg == "--seed" && i + 1 < argc) {
            seed = static_cast<std::uint64_t>(std::stoull(argv[++i]));
        } else if (arg == "--auto") {
            auto_mode = true;
        }
    }

    print_banner();
    if (!auto_mode) {
        std::cout << "Нажмите Enter, чтобы бросить жребий на первый ход...";
        std::cin.get();
    }

    std::mt19937 rng(seed);
    GameResult result = play_game(rng, rounds);

    std::cout << (result.player_starts ? "Первым ходит игрок" : "Первым ходит компьютер") << "\n\n";

    for (std::size_t i = 0; i < result.rounds.size(); ++i) {
        if (!auto_mode) {
            std::cout << "Раунд " << (i + 1) << ": нажмите Enter, чтобы бросить...";
            std::cin.get();
        }
        print_round(static_cast<int>(i), result.rounds[i]);
        std::cout << "Текущий счёт: Игрок " << result.player_score << " — Компьютер " << result.cpu_score
                  << "\n\n";
    }

    std::cout << "Итоговый счёт: Игрок " << result.player_score << " — Компьютер " << result.cpu_score << "\n";
    if (result.winner() == "player") {
        std::cout << "Вы победили!\n";
    } else if (result.winner() == "cpu") {
        std::cout << "Победил компьютер.\n";
    } else {
        std::cout << "Ничья.\n";
    }
    return 0;
}
