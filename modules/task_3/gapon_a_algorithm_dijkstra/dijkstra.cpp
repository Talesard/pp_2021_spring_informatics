// Copyright 2021 Gapon Andrey
#include "../../../modules/task_3/gapon_a_algorithm_dijkstra/dijkstra.h"
#include <tbb/tbb.h>
#include <vector>
#include <limits>
#include <cmath>
#define THREADS 4



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

    int points_count = sqrt(graph.size());
    int max_weight = INT32_MAX;
    int min, min_point, temp;
    std::vector<int> gr;
    std::vector<int> points_len(points_count, max_weight);
    std::vector<bool> proces(points_count, false);
    tbb::mutex mutex;
    tbb::task_scheduler_init(THREADS);
    std::vector<int> min_valume(2, INT32_MAX);

    if (graph.size() == 0) {
        throw "Error graph";
    }

    if (first == last)
        return std::vector<int>(1, 0);

    if (first > last) {
        std::swap(first, last);
    }

    if (sqrt(graph.size()) != points_count) {
        throw "Error size";
    }

    --first;
    --last;

    points_len[first] = 0;

    do {
        min_valume = tbb::parallel_reduce(
            tbb::blocked_range<int>(0, points_count),
            std::vector<int>(2) = { INT32_MAX, INT32_MAX },
            [&](const tbb::blocked_range<int>& v,
                std::vector<int> min_vals) {
            for (int m = v.begin(); m < v.end(); m++) {
                if (!proces[m] && points_len[m] < min_vals[0]) {
                    min_vals[0] = points_len[m];
                    min_vals[1] = m;
                }
            }
            return min_vals;
        },
            [&](std::vector<int> x, std::vector<int> y) {
            if (x[0] < y[0]) {
                return x;
            }
            return y;
        });

        min_point = min_valume[1];
        min = min_valume[0];

        if (min_point != max_weight) {
            tbb::parallel_for(
                tbb::blocked_range<int>(0, points_count),
                [&](const tbb::blocked_range<int>& v) {
                for (int i = v.begin(); i < v.end(); i++) {
                    if (graph[min_point * points_count + i] > 0) {
                        mutex.lock();
                        temp = min + graph[min_point * points_count + i];
                        if (points_len[i] > temp) {
                            points_len[i] = temp;
                        }
                        mutex.unlock();
                    }
                }
            });
            proces[min_point] = true;
        }
    } while (min_point < max_weight);
    int weight = points_len[last];
    gr.push_back(last + 1);
    while (last != first) {
        tbb::parallel_for(
            tbb::blocked_range<int>(0, points_count),
            [&](const tbb::blocked_range<int>& vertex) {
            for (int n = vertex.begin(); n < vertex.end(); n++) {
                if (graph[last * points_count + n] > 0) {
                    temp = weight - graph[last * points_count + n];
                    if (points_len[n] == temp) {
                        weight = temp;
                        last = n;
                        mutex.lock();
                        gr.push_back(n + 1);
                        mutex.unlock();
                    }
                }
            }
        });
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
}
