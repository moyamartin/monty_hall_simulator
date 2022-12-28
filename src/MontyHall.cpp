/// Copyright 2022 Martin Moya <moyamartin1@gmail.com>
#include <MontyHall.hpp>

MontyHall::MontyHall(int max_door_number)
    : Person("Monty Hall", 0, max_door_number), _car_door_number(-1),
      _choosen_door(-1) {
    _car_door_number = generate_random_number();
}

int MontyHall::pick_door(int door_param) {
    _choosen_door = generate_random_number();
    while (_choosen_door == _car_door_number || _choosen_door == door_param) {
        _choosen_door = generate_random_number();
    }
    return _choosen_door;
}

bool MontyHall::has_won(int choosen_door_number) {
    return choosen_door_number == _car_door_number;
}

int MontyHall::get_car_door_number() { return _car_door_number; }
