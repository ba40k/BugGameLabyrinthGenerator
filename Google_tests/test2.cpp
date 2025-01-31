//
// Created by radamir on 30.01.25.
//
#include <gtest/gtest.h>
#include "../Generator.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/rotating_file_sink.h>
class GeneratorTest : public ::testing::Test {
    public:
    Generator defaultGenerator;
    static Generator GetParametrizedGenerator(int seed,int min,int max) {
        try {
            Generator g(seed,min,max);
            return g;
        } catch (...) {
            throw;
        }

    }
};
TEST_F(GeneratorTest, HandlesInput1) {
    EXPECT_THROW(defaultGenerator.getRandomInt(-1,-2),std::invalid_argument);
}
TEST_F(GeneratorTest, HandlesInput2) {
    EXPECT_THROW(GetParametrizedGenerator(0,0,-1),std::invalid_argument);
}
TEST_F(GeneratorTest, HandlesInput3) {
    EXPECT_THROW(defaultGenerator.getRandomPoint(-1,0),std::invalid_argument);
}
TEST_F(GeneratorTest, HandlesInput4) {
    EXPECT_THROW(defaultGenerator.getRandomInt(-100,-1),std::invalid_argument);
}
