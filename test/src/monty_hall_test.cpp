#include "MontyHall.hpp"
#include <gtest/gtest.h>

// Check that player picks the same door on the second try
TEST(MontyHall, CheckThatPicksAGoat) {
    MontyHall test_monty_hall(2);

    int goat_door = test_monty_hall.pick_door(1);
    EXPECT_FALSE(test_monty_hall.has_won(goat_door));
}

// Check that has_won is working properly
TEST(MontyHall, CheckGetCarDoorNumber) {
    MontyHall test_monty_hall(2);

    int car_door = test_monty_hall.get_car_door_number();
    EXPECT_TRUE(test_monty_hall.has_won(car_door));
}

// Check that the name of Monty Hall is actually 'Monty Hall'
TEST(MontyHall, CheckMontyHallName) {
    MontyHall test_monty_hall(2);

    EXPECT_EQ("Monty Hall", test_monty_hall.get_name());
}
