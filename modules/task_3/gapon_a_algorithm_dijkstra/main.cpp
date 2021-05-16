// Copyright 2021 Gapon Andrey
#include <tbb/tbb.h>
#include <gtest/gtest.h>
#include <vector>
#include "../../../modules/task_3/gapon_a_algorithm_dijkstra/dijkstra.h"


TEST(Dijkstra, test_matrix_generation_NUMBER_3) {
    std::vector<int> graf(16);
    graf = generateGraph(4);
    std::vector<int> res = { 4, 1 };
    EXPECT_EQ(Dijkstra(graf, 1, 4), res);
}

TEST(Dijkstra, test_three_points) {
    std::vector<int> graf = { 0, 2, 3,
                          2, 0, 1,
                          3, 1, 0 };

    std::vector<int> res = { 3, 1 };
    EXPECT_EQ(Dijkstra(graf, 1, 3), res);
}

TEST(Dijkstra, throws_with_negative_weight) {
    std::vector<int> graf = { 0, -5, 9, 0, 0, 14,
                          7, 0, 10, 15, 0, 0,
                          9, 10, 0, 11, 0, 2,
                          0, 15, 11, 0, 6, 0,
                          0, 0, 0, 6, 0, 9,
                          14, 0, 2, 0, 9, 0 };

    std::vector<int> res = { 5, 5, 5, 5 };
    ASSERT_ANY_THROW(Dijkstra(graf, 5, 1));
}

TEST(Dijkstra, throws_with_wrong_arguments) {
    std::vector<int> graf = { 0, -5, 9, 0, 0, 14,
                          7, 0, 10, 15, 0, 0,
                          9, 10, 0, 11, 0, 2,
                          0, 15, 11, 0, 6, 0,
                          0, 0, 0, 6, 0, 9,
                          14, 0, 2, 0, 9, 0, 99, 9 };

    std::vector<int> res = { 5, 5, 5, 5 };
    ASSERT_ANY_THROW(Dijkstra(graf, 5, 1));
}

TEST(Dijkstra, passes_if_start_equal_end) {
    std::vector<int> graf = { 0, 2, 3,
                          2, 0, 1,
                          3, 1, 0 };

    ASSERT_NO_THROW(Dijkstra(graf, 3, 3));
}

TEST(dijkstra, throws_with_no_graph) {
    std::vector<int> graf = {};
    ASSERT_ANY_THROW(Dijkstra(graf, 1, 1));
}

TEST(Dijkstra, test_six_point) {
    std::vector<int> graf = { 0, 7, 9, 0, 0, 14,
                          7, 0, 10, 15, 0, 0,
                          9, 10, 0, 11, 0, 2,
                          0, 15, 11, 0, 6, 0,
                          0, 0, 0, 6, 0, 9,
                          14, 0, 2, 0, 9, 0 };

    std::vector<int> res = { 5, 6, 3, 1 };
    EXPECT_EQ(Dijkstra(graf, 1, 5), res);
}

TEST(Dijkstra, test_parallel_six_point) {
    std::vector<int> graf = { 0, 7, 9, 0, 0, 14,
                          7, 0, 10, 15, 0, 0,
                          9, 10, 0, 11, 0, 2,
                          0, 15, 11, 0, 6, 0,
                          0, 0, 0, 6, 0, 9,
                          14, 0, 2, 0, 9, 0 };

    std::vector<int> res = { 5, 6, 3, 1 };
    EXPECT_EQ(Parallel_Dijkstra(graf, 1, 5), res);
}
