/// Copyright 2022 Martin Moya <moyamartin1@gmail.com>
#include <Player.hpp>

Player::Player(const char* name, int max_door_number, bool repeat_door)
    : Person(name, 0, max_door_number),
      _choosen_door(-1),
      _monty_hall_door(-1),
      _repeat_door(repeat_door),
      _second_pick(false) {}

int Player::pick_door() {
  // check if the player has done the second pick and it is configured to
  // repeat the same door as the first pick
  if (!_second_pick) {
    _choosen_door = generate_random_number();
    _second_pick = true;
  } else {
    int tmp_door_number = _choosen_door;
    while (!_repeat_door && _choosen_door != tmp_door_number &&
           _choosen_door != _monty_hall_door) {
      _choosen_door = generate_random_number();
    }
  }
  return _choosen_door;
}
