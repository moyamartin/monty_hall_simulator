/// Copyright 2022 Martin Moya <moyamartin1@gmail.com>
///
/// @file       Person.cpp
/// @brief      Contains the definition of function members from the class
///             Person
/// @version    0.0.1
/// @date       26. Dec. 2022
/// @author     Martin Moya
///
#include <Person.hpp>

Person::Person(const char *name, int min_range, int max_range)
    : _name(name), _min_range(min_range), _max_range(max_range),
      _engine(std::mt19937(_seed())) {
    _random_number_generator =
        std::uniform_int_distribution<int>(_min_range, _max_range);
}

int Person::generate_random_number() {
    return _random_number_generator(_engine);
}

void Person::update_range(int min_range, int max_range) {
    _min_range = min_range;
    _max_range = max_range;
    _random_number_generator =
        std::uniform_int_distribution<int>(_min_range, _max_range);
}

std::string Person::get_name() { return _name; }
