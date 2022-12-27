///
/// @file       Person.hpp
/// @brief      Contains the definition of class Person
/// @version    0.0.1
/// @date       26. Dec. 2022
/// @author     Martin Moya
///

#pragma once

#include <random>
#include <string>

class Person
{
public:
    Person(const char* name, int min_range, int max_range);
    virtual ~Person() = default;

    ///
    /// pick_door
    /// @brief
    ///     picks a random door
    /// @return
    ///     the number that the player picked
    ///
    virtual int pick_door() = 0;

    ///
    /// generate_random_number
    /// @brief
    ///     Generate a random number using a Mersenne Twister pseudo-random
    ///     generator
    /// @return
    ///     random int
    ///
    int generate_random_number();

    ///
    /// update_range 
    /// @brief
    ///     Update the range of the random number generator
    ///
    /// @param
    ///     min_range (int): the minimum value of the range
    ///     max_range (int): the maximum value of the range
    void update_range(int min_range, int max_range);

private:
    ///
    /// string_name
    /// @brief
    ///     name of the player
    ///
    std::string _name; 

    /// 
    /// seed
    /// @brief
    ///     This assure us that every time that the app is ran the random 
    ///     numbers are not repeated. i.e. if the app is ran and a sequence of
    ///     rolls is not repetead, the next time the app is ran this sequence
    ///     is NOT repeated again
    ///     
    /// @see <a href="http://www.cplusplus.com/reference/random/random_device/">
    ///     random_device</a>
    ///
    std::random_device _seed;

    ///
    /// engine
    /// @brief
    ///     A Mersenne Twister pseudo-random generator used by 
    ///      uniform_int_distribution
    ///
    /// @see
    ///     <a href="http://www.cplusplus.com/reference/random/mt19937/">
    ///     mt19937</a>
    ///
    std::mt19937 _engine;

    ///
    /// door_number_generator
    /// @brief
    ///     Generates the random output of the Roulette's
    ///
    /// @see 
    ///     <a href="https://en.cppreference.com/w/cpp/numeric/random/
    ///     uniform_int_distribution">
    ///     uniform_int_distribution</a>
    ///
    std::uniform_int_distribution<int> _random_number_generator;

    ///
    /// _max_range_val
    /// @brief
    ///     this variable is to define the maximum value for the range used by
    ///     the random generator
    ///
    int _max_range;

    ///
    /// _min_range_val
    /// @brief
    ///     this variable is to define the minimum value for the range used by
    ///     the random generator
    ///
    int _min_range;
};
