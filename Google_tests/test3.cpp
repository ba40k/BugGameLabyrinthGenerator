//
// Created by radamir on 01.02.25.
//
#include <gtest/gtest.h>

#include "../Population.h"
#include "../Labyrinth.h"
class TestingPopulation : public testing::Test {
    public:
    Population<Labyrinth> population;
};
TEST_F(TestingPopulation, HandlesPopulationSize1) {
    EXPECT_EQ(population.getPopulationSize(), 100);
}
TEST_F(TestingPopulation, HandlesPopulationSize2) {
    Population<Labyrinth> pop(20);
    EXPECT_EQ(pop.getPopulationSize(), 20);
}
TEST_F(TestingPopulation, HandlesPopulationSize3) {
    Population<Labyrinth> pop(0);
    EXPECT_EQ(pop.getPopulationSize(), 0);
}
TEST_F(TestingPopulation, HandlesShrinkPopualtionAndSetMaxPopulationSize1) {
    population.setMaxPopulationSize(10);
    EXPECT_EQ(population.getPopulationSize(), 10);
}
TEST_F(TestingPopulation, HandlesShrinkPopualtionAndSetMaxPopulationSize2) {
    population.setMaxPopulationSize(100);
    EXPECT_EQ(population.getPopulationSize(), 100);
}
TEST_F(TestingPopulation, HandlesShrinkPopualtionAndSetMaxPopulationSize3) {
    population.setMaxPopulationSize(0);
    EXPECT_EQ(population.getPopulationSize(), 0);
}