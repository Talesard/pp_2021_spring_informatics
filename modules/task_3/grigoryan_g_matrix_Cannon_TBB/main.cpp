// Copyright 2021 Grigoryan Garry
#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <numeric>
#include <random>
#include <stack>
#include "matrix_m_Cannon.h"

TEST(Matrix_Cannon_tbb,throw_when_different_size_mat){
matrixA=RandomMatrix(3);
matrixB=RandomMatrix(4);
ASSERT_ANY_THROW(AlgorithmCannonTBB(A,B));
}

TEST(Matrix_Cannon_tbb,time_for_parallel){
matrixA=RandomMatrix(100);
matrixB=RandomMatrix(100);
matrixrez1=BlockMulti(A,B,10);
matrixrez2=AlgorithmCannonTBB(A,B);
ASSERT_TRUE(CompareMatrix(rez1,rez2));
}
TEST(Matrix_Cannon_tbb,correct_result_mat_size_3){
matrixA={{4.1,5.5,6.6},
{5.2,7.2,1.3},
{4.1,7.8,9.7}};
matrixB={{4.1,7.8,9.7},
{3.6,4.5,5.8},
{5.1,5.9,5.1}};
matrixrez={{74.37,81.73,88.93},
{59.07,62.95,78.03},
{98.46,110.37,118.08}};
ASSERT_TRUE(CompareMatrix(rez,AlgorithmCannonTBB(A,B)));
}
TEST(Matrix_Cannon_tbb,correct_result_mat_size_4){
matrixA={{2.2,2.2,2.2,2.2},
{2.2,2.2,2.2,2.2},
{2.2,2.2,2.2,2.2},
{2.2,2.2,2.2,2.2}};
matrixB={{2.2,2.2,2.2,2.2},
{2.2,2.2,2.2,2.2},
{2.2,2.2,2.2,2.2},
{2.2,2.2,2.2,2.2}};
matrixrez={{19.36,19.36,19.36,19.36},
{19.36,19.36,19.36,19.36},
{19.36,19.36,19.36,19.36},
{19.36,19.36,19.36,19.36}};
ASSERT_TRUE(CompareMatrix(rez,AlgorithmCannonTBB(A,B)));
}
TEST(Matrix_Cannon_tbb,correct_result_different_algorithms){
matrixA=RandomMatrix(5);
matrixB=RandomMatrix(5);
ASSERT_TRUE(CompareMatrix(NaiveMulti(A,B),AlgorithmCannonTBB(A,B)));
}
intmain(intargc,char**argv){
::testing::InitGoogleTest(&argc,argv);
returnRUN_ALL_TESTS();
}
