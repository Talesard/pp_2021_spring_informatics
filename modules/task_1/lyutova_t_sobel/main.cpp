// Copyright 2021 Lyutova Tanya
#include "../../modules/task_1/lyutova_t_sobel/lyutova_t_sobel.h"
#include "gtest/gtest.h"

TEST(sequential, RandomImage) {
    Image image = createRandomImage(1000, 1000);
    ASSERT_EQ(image.cols, 1000);
    ASSERT_EQ(image.rows, 1000);
}

TEST(sequential, DifferentImages) {
    Image image = createRandomImage(100, 100);
    Image sobel(100,100);
    ASSERT_NE(image.pixels, sobel.pixels);
}

TEST(sequential, EmptyMatrix) {
    Image tmp(0, 0);
    ASSERT_EQ(tmp.cols, 0);
    ASSERT_EQ(tmp.rows, 0);
}

TEST(sequential, BigImage) {
    Image tmp(1000, 1000);
    ASSERT_EQ(tmp.cols, tmp.rows);
}

TEST(sequential, CompareSameImage) {
    Image tmp(1, 1);
    Image tmp2(1, 1);
    ASSERT_EQ(tmp, tmp2);
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
