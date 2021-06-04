// Copyright 2021 Panova Olga
#ifndef MODULES_TASK_3_PANOVA_O_SHELL_B_SORT_SHELL_B_SORT_H_
#define MODULES_TASK_3_PANOVA_O_SHELL_B_SORT_SHELL_B_SORT_H_
#include <tbb/tbb.h>
#include <tbb/tick_count.h>
#include <vector>
#include <random>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <cmath>
std::vector<int> CreateVector(int size);
std::vector<int> EvenMerge(const std::vector<int>& left, const std::vector<int>& right);
std::vector<int> OddMerge(const std::vector<int>& left, const std::vector<int>& right);
std::vector<int> BatcherMerge(const std::vector<int>& left, const std::vector<int>& right);
std::vector<int> ShellSort(const std::vector<int>& a);
std::vector<std::vector<int>> Division(const std::vector<int>& a, int piece);
std::vector<int> ParallelOddEvenShellSort(const std::vector<int> a, int piece);
std::vector<int> SequentialOddEvenShellSort(const std::vector<int> a, int piece);
#endif  // MODULES_TASK_3_PANOVA_O_SHELL_B_SORT_SHELL_B_SORT_H_
