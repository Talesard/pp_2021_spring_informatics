// Copyright 2021 Gapon Andrey

#include <vector>
#include <limits>
#include <cmath>
#include "../../../modules/task_1/gapon_a_algorithm_dijkstra/dijkstra.h"

std::vector<int> Create_Graph(int s) {
    std::vector<int> example(s * s, 2);
    for (int m = 0; m < s; m++) {
        for (int n = 0; n < s; n++) {
            if (m == n) {
                example[m * s + n] = 1;
            }
        }
    }
    return example;
}

std::vector<int> dijkstra_algorithm(const std::vector<int>& graph,
    int first, int last) {

    int vertex_count = sqrt(graph.size());
    int max_weight = INT32_MAX;
    int minimum;
    int min_vertex;
    int temp;
    std::vector<int> points_weight(vertex_count, max_weight);
    std::vector<int> gr;
    std::vector<bool> proces(vertex_count, false);

    if (graph.size() == 0) {
        throw "Error empty graph";
    }

    if (first == last)
        return std::vector<int>(1, 0);

    if (first > last) {
        std::swap(first, last);
    }

    if (sqrt(graph.size()) != vertex_count) {
        throw "Error size";
    }

    --first;
    --last;

    points_weight[first] = 0;

    do {
        min_vertex = max_weight;
        minimum = max_weight;

        for (int m = 0; m < vertex_count; m++) {
            if (!proces[m] && points_weight[m] < minimum) {
                min_vertex = m;
                minimum = points_weight[m];
            }
        }

        if (min_vertex != max_weight) {
            for (int n = 0; n < vertex_count; n++) {
                if (graph[min_vertex * vertex_count + n] > 0) {
                    temp = minimum + graph[min_vertex * vertex_count + n];
                    if (points_weight[n] > temp) {
                        points_weight[n] = temp;
                    }
                }
            }
            proces[min_vertex] = true;
        }
    } while (min_vertex < max_weight);

    gr.push_back(last + 1);
    int weight = points_weight[last];

    while (last != first) {
        for (int m = 0; m < vertex_count; m++) {
            if (graph[last * vertex_count + m] < 0) {
                throw "Error";
            }
            if (graph[last * vertex_count + m] > 0) {
                temp = weight - graph[last * vertex_count + m];
                if (points_weight[m] == temp) {
                    weight = temp;
                    last = m;
                    gr.push_back(m + 1);
                }
            }
        }
    }
    return gr;
}
