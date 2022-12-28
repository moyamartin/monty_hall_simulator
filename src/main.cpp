/// Copyright 2022 Martin Moya <moyamartin1@gmail.com>
//
#include <iostream>

#include "MontyHall.hpp"
#include "Player.hpp"
#include "spdlog/spdlog.h"
#include <argparse/argparse.hpp>

static constexpr int number_of_doors = 2;

void print_intro() { std::cout << "Welcome to the MontyHall show!"; }

bool run_simulation(bool player_keep_same_door) {
    Player player("Martin", number_of_doors, player_keep_same_door);
    MontyHall monty_hall(number_of_doors);

    spdlog::debug("{} is picking a door", player.get_name());
    int first_door = player.pick_door(-1);
    spdlog::debug("{} picked door #{}", player.get_name(), first_door);
    int monty_hall_door = monty_hall.pick_door(first_door);
    spdlog::debug("{} picked door #{}", monty_hall.get_name(), monty_hall_door);
    int second_door = player.pick_door(monty_hall_door);
    spdlog::debug("{} second pick is door #{}", player.get_name(), second_door);
    bool has_won = monty_hall.has_won(second_door);
    spdlog::debug("{} has won? {}", player.get_name(),
                  (has_won ? "yes" : "no"));
    return has_won;
}

int main(int argc, char *argv[]) {

    argparse::ArgumentParser program("monty_hall_simulation", "0.0.1");
    program.add_argument("-s")
        .help("The number of simulations to run")
        .default_value(1000);
    program.add_description(
        "This software implements a simulation of the "
        "Monty Hall problem, it will run the amount of simulations "
        "specified by the -s flag");
    try {
        program.parse_args(argc, argv);
    } catch (const std::runtime_error &err) {
        spdlog::warn("{}", err.what());
        std::cout << program << std::endl;
        std::exit(1);
    }
    // parse the number of iterations
    int number_of_iterations = program.get<int>("-s");
    int won_keep_same_door = 0;
    int won_choose_new_door = 0;
    spdlog::info("Monty Hall Problem Simulatior (C++11)");
    spdlog::debug("Running simulation for {} iterations", number_of_iterations);
    for (int i = 0; i < number_of_iterations; ++i) {
        won_keep_same_door += run_simulation(true);
        won_choose_new_door += run_simulation(false);
    }
    float probability_choose_new_door =
        (static_cast<float>(won_choose_new_door) /
         static_cast<float>(number_of_iterations)) *
        100.0;
    float probability_keep_same_door =
        (static_cast<float>(won_keep_same_door) /
         static_cast<float>(number_of_iterations)) *
        100.0;
    spdlog::info("Probability of winning keeping the same door {}%",
                 probability_keep_same_door);
    spdlog::info("Probability of winning changing the door {}%",
                 probability_choose_new_door);
}
