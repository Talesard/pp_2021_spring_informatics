// Copyright 2021 Tashirev Ivan
#ifndef MODULES_TASK_4_TASHIREV_I_MONTE_CARLO_TASHIREV_I_MONTE_CARLO_H_
#define MODULES_TASK_4_TASHIREV_I_MONTE_CARLO_TASHIREV_I_MONTE_CARLO_H_

#include <vector>
#include <string>

struct my_range{
    int start;
    int end;
};

double seqMonteCarlo(double(*f)(const std::vector<double>&),
                     const std::vector<double>& a,
                     const std::vector<double>& b, int s);

double stdMonteCarlo(double(*f)(const std::vector<double>&),
                     const std::vector<double>& a,
                     const std::vector<double>& b, int s);

#endif  // MODULES_TASK_4_TASHIREV_I_MONTE_CARLO_TASHIREV_I_MONTE_CARLO_H_