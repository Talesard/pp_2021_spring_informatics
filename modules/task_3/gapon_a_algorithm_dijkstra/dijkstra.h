// Copyright 2021 Gapon Andrey

#ifndef MODULES_TASK_3_GAPON_A_ALGORITHM_DIJKSTRA_DIJKSTRA_H_
#define MODULES_TASK_3_GAPON_A_ALGORITHM_DIJKSTRA_DIJKSTRA_H_
#include <vector>

std::vector<int> dijkstra_parallel(const std::vector<int>& graph,
int first, int end);
std::vector<int> dijkstra_algorithm(const std::vector<int>& graph,
int first, int end);
std::vector<int> Create_Graph(int size);

#endif  //  MODULES_TASK_3_GAPON_A_ALGORITHM_DIJKSTRA_DIJKSTRA_H_
