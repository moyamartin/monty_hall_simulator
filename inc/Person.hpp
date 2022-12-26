///
/// @file       Person.hpp
/// @brief      Contains the definition of class Person
/// @version    0.0.1
/// @date       26. Dec. 2022
/// @author     Martin Moya
///

#pragma once

#include <string>

class Person
{
public:
    Person(const char* name);
    virtual ~Person() = default;

    ///
    /// Pick a door
    /// @return
    ///     the number that the player picked
    ///
    virtual int pick_door() = 0;

private:
    std::string _name; 
};
