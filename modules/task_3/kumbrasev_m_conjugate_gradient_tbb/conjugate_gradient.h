// Copyright 2021 Kumbrasev Mark
#ifndef MODULES_TASK_2_KUMBRASEV_M_CONJUGATE_GRADIENT_TBB_CONJUGATE_GRADIENT_H_
#define MODULES_TASK_2_KUMBRASEV_M_CONJUGATE_GRADIENT_TBB_CONJUGATE_GRADIENT_H_

#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>
#include "tbb/tbb.h"
#include "tbb/parallel_for.h"
#include "tbb/blocked_range.h"
#include "tbb/tick_count.h"

std::vector<std::vector<double> > getRandomMatrix(int n);
std::vector<double> getRandomVector(int n);
std::vector<double> linVec(double a, const std::vector<double> &v1, double b, const std::vector<double> &v2);
double innerVec(const std::vector<double> &v1, const std::vector<double> &v2);
std::vector<double> mMultv(const std::vector<std::vector<double>> &M, const std::vector<double> &V);
double vecNorm(const std::vector<double> &V);
std::vector<double> ConjugateGradient(const std::vector<std::vector<double>> &M, const std::vector<double> &B);

#endif  // MODULES_TASK_2_KUMBRASEV_M_CONJUGATE_GRADIENT_TBB_CONJUGATE_GRADIENT_H_
