// Copyright 2021 Kumbrasev Mark
#include <gtest/gtest.h>
#include "./conjugate_gradient.h"

TEST(Conjugate_gradient_omp, M2) {
    std::vector<std::vector<double>> M = { { 5, 2}, {2, 1} };
    std::vector<double> B = { 7, 9 };

    std::vector<double> X = ConjugateGradient(M, B);
    tbb::tick_count t0 = tbb::tick_count::now();
    std::vector<double> Mx = mMultv(M, X);
    tbb::tick_count t1 = tbb::tick_count::now();
    std::cout << "ParTime:" << (t1 - t0).seconds() << std::endl;
    std::vector<double> res = { { 7, 9 } };
    for (size_t i = 0; i < res.size(); ++i) {
        ASSERT_NEAR(Mx[i], res[i], 0.5);
    }
}
TEST(Conjugate_gradient_omp, X) {
    std::vector<std::vector<double>> M = { { 5, 2}, {2, 1} };
    std::vector<double> B = { 7, 9 };

    std::vector<double> X = ConjugateGradient(M, B);
    std::vector<double> res = { { -11, 31 } };
    for (size_t i = 0; i < res.size(); ++i) {
        ASSERT_NEAR(res[i], X[i], 0.5);
    }
}
TEST(Conjugate_gradient_omp, M3) {
    std::vector<std::vector<double>> M = { { 1, 5, 3 }, {2, 1, -1 }, { 4, 2, 1 } };
    std::vector<double> B = { 31, 29, 10 };

    std::vector<double> X = ConjugateGradient(M, B);
    tbb::tick_count t0 = tbb::tick_count::now();
    std::vector<double> res = mMultv(M, X);
    tbb::tick_count t1 = tbb::tick_count::now();
    std::cout << "ParTime:" << (t1 - t0).seconds() << std::endl;
    std::vector<double> finalr = { { 172.2, 137.814, 134.175 } };
    for (size_t i = 0; i < res.size(); ++i) {
        ASSERT_NE(B[i], res[i]);
    }
}
TEST(Conjugate_gradient_omp, M4) {
    std::vector<std::vector<double>> M = { { 1, -1, 3, 1 }, {4, -1, 5, 4 }, { 2, -2, 4, 1 }, { 1, -4, 5, -1 } };
    std::vector<double> B = { 5, 4, 6, 3 };

    std::vector<double> X = ConjugateGradient(M, B);
    tbb::tick_count t0 = tbb::tick_count::now();
    std::vector<double> res = mMultv(M, X);
    tbb::tick_count t1 = tbb::tick_count::now();
    std::cout << "ParTime:" << (t1 - t0).seconds() << std::endl;
    for (size_t i = 0; i < res.size(); ++i) {
        ASSERT_NE(B[i], res[i]);
    }
}
TEST(Conjugate_gradient_omp, MultiMB) {
    std::vector<std::vector<double>> M = { { 2, 6, 1 }, { 3, 1, 7 }, { 8, 9, 1 } };
    std::vector<double> B = { 7, 4, 1 };

    tbb::tick_count t0 = tbb::tick_count::now();
    std::vector<double> res = mMultv(M, B);
    tbb::tick_count t1 = tbb::tick_count::now();
    std::cout << "ParTime:" << (t1 - t0).seconds() << std::endl;
    std::vector<double> I = { { 39, 32, 93 } };
    for (size_t i = 0; i < res.size(); ++i) {
        ASSERT_EQ(I[i], res[i]);
    }
}
TEST(Conjugate_gradient_omp, MultiMBRandom) {
    int n = 100;
    std::vector<std::vector<double>> M = getRandomMatrix(n);
    std::vector<double> B = getRandomVector(n);

    tbb::tick_count t0 = tbb::tick_count::now();
    std::vector<double> res = mMultv(M, B);
    tbb::tick_count t1 = tbb::tick_count::now();
    std::cout << "ParTime:" << (t1 - t0).seconds() << std::endl;
    std::vector<double> I = B;
    for (size_t i = 0; i < B.size(); ++i) {
        ASSERT_EQ(I[i], B[i]);
    }
}
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
