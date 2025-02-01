//
// Created by radamir on 01.02.25.
//
#include <gtest/gtest.h>

#include "../Population.h"
class TestingPopulation : public testing::Test {
    public:
    Population population;
};
TEST_F(TestingPopulation, HandlesPopulationSize1) {
    EXPECT_EQ(population.getPopulationSize(), 100);
}
TEST_F(TestingPopulation, HandlesShrinkPopualtion) {
    population.setMaxPopulationSize(10);
    EXPECT_EQ(population.getPopulationSize(), 10);
}