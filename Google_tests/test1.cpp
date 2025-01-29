#include <gtest/gtest.h>

#include "../Labyrinth.h"

class TestLabyrinth : public testing::Test {
    protected:
    Labyrinth labyrinth;
};
TEST_F(TestLabyrinth, pointAccesability1) {
    ASSERT_EQ(false, Labyrinth::isBelongsToLabyrinth(-1,-1));
}
TEST_F(TestLabyrinth, pointAccesability2) {
    ASSERT_EQ(false, Labyrinth::isBelongsToLabyrinth(-1,0));
}
TEST_F(TestLabyrinth, pointAccesability3) {
    ASSERT_EQ(false, Labyrinth::isBelongsToLabyrinth(3,-1));
}
TEST_F(TestLabyrinth, pointAccesability4) {
    ASSERT_EQ(false, Labyrinth::isBelongsToLabyrinth(3,-1));
}
TEST_F(TestLabyrinth, pointAccesability5) {
    ASSERT_EQ(true, Labyrinth::isBelongsToLabyrinth(3,3));
}
TEST_F(TestLabyrinth, pointAccesability6) {
    ASSERT_EQ(false, Labyrinth::isBelongsToLabyrinth(31,21));
}
TEST_F(TestLabyrinth, pointAccesability7) {
    ASSERT_EQ(true, Labyrinth::isBelongsToLabyrinth(30,20));
}
TEST_F(TestLabyrinth, pointAccesability8) {
    ASSERT_EQ(true, Labyrinth::isBelongsToLabyrinth(0,0));
}
