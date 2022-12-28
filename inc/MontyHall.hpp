/// Copyright 2022 Martin Moya <moyamartin1@gmail.com>
///
/// @file       MontyHall.hpp
/// @brief      Contains the definition of class MontyHall which inherits from
///             Person.hpp
/// @version    0.0.1
/// @date       26. Dec. 2022
/// @author     Martin Moya
///

#pragma once

#include <Person.hpp>

class MontyHall : public Person {
  public:
    explicit MontyHall(int max_door_number);
    ~MontyHall() = default;

    ///
    /// pick_door
    /// @brief
    ///     Picks a door that it is a goat and different than door_param
    /// @param
    ///     door_param (int): MontyHall always has to pick a door different
    ///     than the car and the one that the player picked
    /// @return
    ///     the number of the door picked that it is not a goat
    ///
    int pick_door(int door_param) override;

    ///
    /// has_won
    /// @brief
    ///     This function checks if the chosen number from a Player is the
    ///     same as the door that has a car
    ///
    /// @return
    ///     true if won, false if the user lost
    ///
    bool has_won(int chosen_door_number);

    ///
    /// get_car_door_number
    /// @brief
    ///     Returns the value of _car_door_number
    ///
    int get_car_door_number();

  private:
    ///
    /// _car_door_number
    /// @brief
    ///     This variable contains the number of the winning door, it is
    ///     it is generated during the constructor
    ///
    int _car_door_number;

    ///
    /// _choosen_door
    /// @brief
    ///     This variable contains the number of the choosen door, it is
    ///     always a door number different than _car_door_number
    ///
    int _choosen_door;
};
