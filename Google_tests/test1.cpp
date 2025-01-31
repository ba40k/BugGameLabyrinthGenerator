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
    ASSERT_EQ(false, Labyrinth::isBelongsToLabyrinth(30,20));
}
TEST_F(TestLabyrinth, HandlesPointAccesability8) {
    ASSERT_EQ(true, Labyrinth::isBelongsToLabyrinth(0,0));
}
TEST_F(TestLabyrinth, HandlesPointPassability1) {
    ASSERT_EQ(true, labyrinth.isPassable(0,0));
}
TEST_F(TestLabyrinth, HandlesPointPassability2) {
    labyrinth.setCell(1,1,'#');
    ASSERT_EQ(false, labyrinth.isPassable(1,1));
}
TEST_F(TestLabyrinth, HandlesPointPassability3) {
    EXPECT_THROW(labyrinth.isPassable(-1,0),std::out_of_range);
}
TEST_F(TestLabyrinth, HandlesPointPassability4) {
    EXPECT_THROW(labyrinth.isPassable(30,0),std::out_of_range);
}
TEST_F(TestLabyrinth, HandlesLabyrinthPassability1) {
    labyrinth.setCell(0,0,'#');
    EXPECT_EQ(false, labyrinth.isPassable());
}
TEST_F(TestLabyrinth, HandlesLabyrinthPassability2) {
    labyrinth.setCell(1,1,'#');
    labyrinth.setCell(0,1,'#');
    labyrinth.setCell(1,0,'#');
    EXPECT_EQ(false, labyrinth.isPassable());
}
TEST_F(TestLabyrinth, HandlesLabyrinthPassability3) {
    labyrinth.setCell(29,19,'#');
    EXPECT_EQ(false, labyrinth.isPassable());
}