#include "Player.hpp"
#include <gtest/gtest.h>

// Check that player picks the same door on the second try
TEST(PlayerTest, CheckPlayerRepeatsFirstDoor) {
    Player test_player("TestPlayer", 2, true);

    int first_door = test_player.pick_door(-1);
    int second_door = test_player.pick_door(1);
    EXPECT_EQ(first_door, second_door);
}

// Check that player picks a different door on second try
TEST(PlayerTest, CheckPlayerDoesntRepeatFirstDoor) {
    Player test_player("TestPlayer", 2, false);

    int first_door = test_player.pick_door(-1);
    int second_door = test_player.pick_door(1);
    EXPECT_NE(first_door, second_door);
}

/// Check that player returns the name that it is set during the constructor
/// this is part of Person functionality
TEST(PlayerTest, CheckPlayerName) {
    Player test_player("TestPlayer", 2, false);

    EXPECT_EQ("TestPlayer", test_player.get_name());
}
