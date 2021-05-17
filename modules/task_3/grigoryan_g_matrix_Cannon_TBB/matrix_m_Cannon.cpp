// Copyright 2021 Grigoryan Garry

#include "../../../modules/task_3/grigoryan_g_matrix_Cannon_TBB/matrix_m_Cannon.h"
#include <tbb/tbb.h>
#include <random>
#include <iostream>
#include <algorithm>
#include <exception>
#include <vector>

matrix RandomMatrix(const int n) {
    if (n <= 0)
        throw std::invalid_argument("Negative size");

    std::mt19937 generator;
    std::random_device device;
    generator.seed(device());
    std::uniform_real_distribution<double> distribution(0, 100);;

    matrix result(n, std::vector<double>(n, 0));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result[i][j] = distribution(generator);

    return result;
}

matrix NaiveMulti(const matrix &A, const matrix &B) {
    if (A[0].size() != B.size())
        throw std::invalid_argument("Different values for col and row");

    int aWidth = A[0].size();
    int aHeight = A.size();
    int bWidth = B[0].size();
    matrix result(m, std::vector<double>(l, 0));

    for (int y = 0; y < aHeight; y++)
        for (int x = 0; x < bWidth; x++)
            for (int k = 0; k < aWidth; k++)
                result[y][x] += A[y][k]*B[k][x];

    return result;
}

bool CompareMatrix(const matrix &A, const matrix &B) {
    if (A.size() != B.size() || A[0].size() != B[0].size())
        return false;

    for (int y = 0; y < A.size(); y++) {
        for (int x = 0; x < A[0].size(); x++)
            if (std::fabs(A[y][x] - B[y][x]) > 0.00001) {
                return false;
            }
    }

    return true;
}

matrix BlockMulti(const matrix &A, const matrix &B, const int &blockSize) {
    if (A[0].size() != B.size())
        throw std::invalid_argument("Different values for col and row");
    if (blockSize > A.size())
        throw std::invalid_argument("Wrong blockSize");

    int aWidth = A[0].size();
    int jjMin, kkMin;
    matrix result(n, std::vector<double>(n, 0));

    for (int jj = 0; jj < aWidth; jj += blockSize) {
        jjMin = std::min<int>(jj + blockSize, aWidth);
       for (int kk = 0; kk < aWidth; kk += blockSize) {
           kkMin = std::min<int>(kk+ blockSize, aWidth);
           for (int i = 0; i < aWidth; i++) {
               for (int k = kk; k < kkMin; k++) {
                   for (int j = jj; j < jjMin; j++) {
                      result[i][j]  +=  A[i][k] * B[k][j];
                   }
                }
            }
        }
    }

    return result;
}

matrix AlgorithmCannonTBB(const matrix &A, const matrix &B) {
    if (A[0].size() != B.size())
        throw std::invalid_argument("Different values for col and row");

    tbb::task_scheduler_init init;
    auto numThreads = init.default_num_threads();
    int aWidth = A[0].size();
    int lastWidth = aWidth;
    int q = std::sqrt(numThreads);
    matrix tempA = A;
    matrix tempB = B;

    if (aWidth % q != 0) {
       while (aWidth % q != 0) {
           tempA.push_back(std::vector<double>(lastWidth, 0));
           tempB.push_back(std::vector<double>(lastWidth, 0));
           aWidth++;
       }
        for (int i = 0; i < aWidth; i++) {
            for (int j = 0; j < aWidth - lastWidth; j++) {
                tempA[i].push_back(0);
                tempB[i].push_back(0);
            }
        }
    }
    int blockSize = aWidth / q;
    matrix result(n, std::vector<double>(n));

    tbb::parallel_for(tbb::blocked_range2d<size_t>(0, aWidth, blockSize, 0, aWidth, blockSize),
                        [&](const tbb::blocked_range2d<size_t>& r) {
        int xThread = r.rows().begin() / blockSize;
        int yThread = r.cols().begin() / blockSize;
        int xBlockA = 0, yBlockA = 0, xBlockB = 0, yBlockB = 0;

        matrix num1(block_size), num2(block_size),
            numres(block_size, std::vector<double>(block_size, 0));

        for (int k = 0; k < blockSize; k++) {
            xBlockA = xThread * blockSize + k;
            yBlockA = ((yThread + xThread) % q) * blockSize;

            yBlockB = yThread * blockSize;
            xBlockB = yBlockA + k;

            num1[k] = std::vector<double>(tempA[xBlockA].begin() + yBlockA,
			          tempA[xBlockA].begin() + yBlockA + blockSize);
            num2[k] = std::vector<double>(tempB[xBlockB].begin() + yBlockB,
			          tempB[xBlockB].begin() + yBlockB + blockSize);
        }
        for (int kk = 0; kk < q; kk++) {
            for (int x = 0; x < blockSize; x++) {
                for (int y = 0; y < blockSize; y++) {
                    for (int s = 0; s < blockSize; s++) {
                        numres[x][y] += num1[x][s] * num2[s][y];
                    }
                }
            }
            if (kk == q - 1)
                break;
            for (int k = 0; k < blockSize; k++) {
                int xA = xThread * blockSize + k;
                int yA = ((yBlockA / blockSize + kk + 1) % q) * blockSize;
                int xB = ((xBlockB / blockSize + kk + 1) % q) * blockSize + k;
                int yB = yThread * blockSize;
                num1[k] = std::vector<double>(tempA[xA].begin() + yA,
				          tempA[xA].begin() + yA + blockSize);
                num2[k] = std::vector<double>(tempB[xB].begin() + yB,
				          tempB[xB].begin() + yB + blockSize);
            }
        }
            for (int x = 0; x < blockSize; x++) {
                for (int y = 0; y < blockSize; y++) {
                    int xx = x + xThread * blockSize;
                    int yy = y + yThread * blockSize;
                    result[xx][yy] = numres[x][y];
                }
            }
    });
    if (lastWidth != aWidth) {
        tbb::parallel_for(tbb::blocked_range<size_t>(0, aWidth, blockSize), [&](const tbb::blocked_range<size_t>& r) {
            for (auto i = r.begin(); i < r.end(); i++) {
                result[i].resize(lastWidth);
            }
        });
    }
    result.resize(lastWidth);
    return result;
}
