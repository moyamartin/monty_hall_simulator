/// Copyright 2022 Martin Moya <moyamartin1@gmail.com>
///
/// @file       Player.hpp
/// @brief      Contains the definition of class Player which inherits from
///             Person.hpp
/// @version    0.0.1
/// @date       26. Dec. 2022
/// @author     Martin Moya
///

#pragma once

// stdlib/external dependencies

// created dependencies
#include <Person.hpp>

class Player : public Person {
  public:
    Player(const char *name, int max_door_number, bool repeat_door);
    ~Player() = default;

    ///
    /// pick_door
    /// @brief
    ///     pick a door number randomly, the number can be between 0 and
    ///     _max_range_val
    /// @param
    ///     door_param (int): is 0 by default, but when passed this should be
    ///     the door picked by montyhall
    /// @return
    ///     the number that the player picked
    ///
    int pick_door(int door_param) override;

  private:
    ///
    /// choosen_door
    /// @brief
    ///     here the result of pick_door is stored, later used when pick_door is
    ///     ran for the second time
    ///
    int _choosen_door;

    ///
    /// repeat_door
    /// @brief
    ///     repeat_door is a boolean value set in the constructor of the
    ///     variable
    bool _repeat_door;

    ///
    /// _second_pick
    /// @brief
    ///     this variable when true states that it is the second pick of the
    ///     player
    ///
    bool _second_pick;

    ///
    /// _monty_hall_door
    /// @brief
    ///     this variable contains the number chosen by MontyHall class
    ///
    int _monty_hall_door;
};
