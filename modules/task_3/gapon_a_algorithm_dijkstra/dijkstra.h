// Copyright 2021 Gapon Andrey

#ifndef MODULES_TASK_3_GAPON_A_ALGORITHM_DIJKSTRA_DIJKSTRA_H_
#define MODULES_TASK_3_GAPON_A_ALGORITHM_DIJKSTRA_DIJKSTRA_H_
#include <vector>

std::vector<int> generateGraph(int size);
std::vector<int> Dijkstra(const std::vector<int>& graph,
int s_vertex, int e_vertex);
std::vector<int> Parallel_Dijkstra(const std::vector<int>& graph,
int s_vertex, int e_vertex);

#endif  //  MODULES_TASK_3_GAPON_A_ALGORITHM_DIJKSTRA_DIJKSTRA_H_
