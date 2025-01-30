#include <gtest/gtest.h>

#include "../Labyrinth.h"

class TestLabyrinth : public testing::Test {
    protected:
    Labyrinth labyrinth;
};
TEST_F(TestLabyrinth, HandlesPointAccesability1) {
    ASSERT_EQ(false, Labyrinth::isBelongsToLabyrinth(-1,-1));
}
TEST_F(TestLabyrinth, HandlesPointAccesability2) {
    ASSERT_EQ(false, Labyrinth::isBelongsToLabyrinth(-1,0));
}
TEST_F(TestLabyrinth, HandlesPointAccesability3) {
    ASSERT_EQ(false, Labyrinth::isBelongsToLabyrinth(3,-1));
}
TEST_F(TestLabyrinth, HandlesPointAccesability4) {
    ASSERT_EQ(false, Labyrinth::isBelongsToLabyrinth(3,-1));
}
TEST_F(TestLabyrinth, HandlesPointAccesability5) {
    ASSERT_EQ(true, Labyrinth::isBelongsToLabyrinth(3,3));
}
TEST_F(TestLabyrinth, HandlesPointAccesability6) {
    ASSERT_EQ(false, Labyrinth::isBelongsToLabyrinth(31,21));
}
TEST_F(TestLabyrinth, HandlesPointAccesability7) {
    ASSERT_EQ(true, Labyrinth::isBelongsToLabyrinth(30,20));
}
TEST_F(TestLabyrinth, HandlesPointAccesability8) {
    ASSERT_EQ(true, Labyrinth::isBelongsToLabyrinth(0,0));
}
