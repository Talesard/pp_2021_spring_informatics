// Copyright 2021 Gapon Andrey

#include "../../../modules/task_2/gapon_a_algorithm_dijkstra/dijkstra.h"
#include <omp.h>
#include <vector>
#include <limits>
#include <cmath>

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

std::vector<int> dijkstra_parallel(const std::vector<int>& graph,
    int first, int last) {

    int vertex_count = sqrt(graph.size());
    int max_weight = std::numeric_limits<int>::max();
    int min_vertex;
    int minimum;
    int temp;
    std::vector<int> points_weight(vertex_count, max_weight);
    std::vector<int> gr;
    std::vector<bool> processed(vertex_count, false);

    if (sqrt(graph.size()) != vertex_count) {
        throw "Error size";
    }

    if (first == last)
        return std::vector<int>(1, 0);

    if (graph.size() == 0) {
        throw "Error graph";
    }

    if (first > last) {
        std::swap(first, last);
    }

    --first;
    --last;

    points_weight[first] = 0;
    int retry = 10;
    do {
        min_vertex = max_weight;
        minimum = max_weight;


#pragma omp parallel
        {
            int local_min_point = max_weight;
            int local_min = max_weight;

#pragma omp for
            for (int m = 0; m < vertex_count; m++) {
                if (!processed[m] && points_weight[m] < local_min) {
                    local_min = points_weight[m];
                    local_min_point = m;
                }
            }

#pragma omp critical
            {
                if (local_min < minimum) {
                    minimum = local_min;
                    min_vertex = local_min_point;
                }
            }
        }

        if (min_vertex != max_weight) {
#pragma omp parallel for private(temp)
            for (int i = 0; i < vertex_count; i++) {
                if (graph[min_vertex * vertex_count + i] > 0) {
                    temp = minimum + graph[min_vertex * vertex_count + i];
                    if (points_weight[i] > temp) {
                        points_weight[i] = temp;
                    }
                }
            }
            processed[min_vertex] = true;
        }
        retry--;
    } while (min_vertex < max_weight || retry == 0);

    gr.push_back(last + 1);
    int weight = points_weight[last];

    while (last != first) {
#pragma omp parallel for private(temp)
        for (int i = 0; i < vertex_count; i++) {
            if (graph[last * vertex_count + i] > 0) {
                temp = weight - graph[last * vertex_count + i];
                if (points_weight[i] == temp) {
#pragma omp critical
                    {
                        weight = temp;
                        last = i;
                        gr.push_back(i + 1);
                    }
                }
            }
        }
    }
    return gr;
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

    // Align start and end with array indexes
    --first;
    --last;

    points_weight[first] = 0;

    do {
        min_vertex = max_weight;
        minimum = max_weight;

        // Choose a point to work with
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

    // Configuring a path
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
