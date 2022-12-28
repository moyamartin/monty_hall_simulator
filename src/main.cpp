/// Copyright 2022 Martin Moya <moyamartin1@gmail.com>
//
#include <iostream>

#include "MontyHall.hpp"
#include "Player.hpp"

static constexpr int number_of_doors = 3;

void print_intro();

void print_intro() { std::cout << "Welcome to the MontyHall show!"; }

int main() {
    int throws = 1;
    int won = 0;
    float probability;
    print_intro();
    Player player("Martin", number_of_doors, true);
    MontyHall monty_hall(number_of_doors);

    std::cout << player.get_name() << " is picking a door" << std::endl;
    int first_door = player.pick_door(-1);
    std::cout << player.get_name() << " picked door #" << first_door
              << std::endl;
    int monty_hall_door = monty_hall.pick_door(first_door);
    std::cout << monty_hall.get_name() << " picked door #" << monty_hall_door
              << std::endl;
    int second_door = player.pick_door(monty_hall_door);
    std::cout << player.get_name() << " second pick is door #" << first_door
              << std::endl;
    bool has_won = monty_hall.has_won(second_door);
    std::cout << "Has the player won? " << has_won << std::endl;
    won += has_won;
    probability = won / throws;
    std::cout << "Probability to win is " << probability << std::endl;
}
