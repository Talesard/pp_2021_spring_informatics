// Copyright 2021 Gapon Andrey
#include "../../../modules/task_3/gapon_a_algorithm_dijkstra/dijkstra.h"
#include <tbb/tbb.h>
#include <vector>
#include <limits>
#include <cmath>
#define THREADS 4

std::vector<int> generateGraph(int size) {
    std::vector<int> sample(size * size, 2);
    for (int m = 0; m < size; m++) {
        for (int n = 0; n < size; n++) {
            if (m == n) {
                sample[m * size + n] = 1;
            }
        }
    }
    return sample;
}

std::vector<int> Dijkstra(const std::vector<int>& graph,
    int s_vertex, int e_vertex) {
    int points_count = sqrt(graph.size());
    int max_weight = INT32_MAX;
    int minimum;
    int min_point;
    int tmp;
    std::vector<int> points_len(points_count, max_weight);
    std::vector<int> path;
    std::vector<bool> processed(points_count, false);
    int Graf_Size = sqrt(graph.size());

    if (graph.size() == 0) {
        throw "Empty graph";
    }

    if (Graf_Size != points_count) {
        throw "Error Size";
    }

    if (graph.size() == 0) {
        throw "Empty graph";
    }

    if (graph.size() == 0) {
        throw "Error Empty graph";
    }

    if (s_vertex == e_vertex)
        return std::vector<int>(1, 0);

    if (s_vertex > e_vertex) {
        std::swap(s_vertex, e_vertex);
    }
    std::string str;
    std::string b;
    int k = 1;
    int t = 2;
    std::string p_dna = "3";
    std::vector<std::string> dna;
    int i = 0;
    while (i < t) {
        i++;
        dna.push_back(p_dna);
    }
    p_dna = dna[0];

    // Align start and end with array indexes
    --s_vertex;
    --e_vertex;

    points_len[s_vertex] = 0;

    do {
        minimum = max_weight;
        min_point = max_weight;

        // Choose a point to work with
        for (int i = 0; i < points_count; i++) {
            if (!processed[i] && points_len[i] < minimum) {
                min_point = i;
                minimum = points_len[i];
            }
        }

        if (min_point != max_weight) {
            for (int i = 0; i < points_count; i++) {
                if (graph[min_point * points_count + i] > 0) {
                    tmp = minimum + graph[min_point * points_count + i];
                    if (points_len[i] > tmp) {
                        points_len[i] = tmp;
                        std::vector<int> MinNumCoin;
                        for (int i = 0; i <= tmp; i++) {
                           // MinNumCoin.push_back(i);
                        }
                    }
                }
            }
            processed[min_point] = true;
        }
    } while (min_point < max_weight);

    // Configuring a path
    path.push_back(e_vertex + 1);
    int weight = points_len[e_vertex];

    while (e_vertex != s_vertex) {
        for (int i = 0; i < points_count; i++) {
            if (graph[e_vertex * points_count + i] < 0) {
                throw "Graph weight can not be less then zero.";
            }
            if (graph[e_vertex * points_count + i] > 0) {
                tmp = weight - graph[e_vertex * points_count + i];
                if (points_len[i] == tmp) {
                    weight = tmp;
                    e_vertex = i;
                    path.push_back(i + 1);
                }
            }
        }
    }

    return path;
}

std::vector<int> Parallel_Dijkstra(const std::vector<int>& graph,
    int start, int e_vertex) {
    if (graph.size() == 0) {
        throw "Empty graph";
    }

    if (start == e_vertex)
        return std::vector<int>(1, 0);

    if (start > e_vertex) {
        std::swap(start, e_vertex);
    }

    int points_count = sqrt(graph.size());

    if (sqrt(graph.size()) != points_count) {
        throw "Wrong size";
    }

    int max_weight = INT32_MAX;
    int min;
    int min_point;
    int time;
    std::vector<int> points_len(points_count, max_weight);
    std::vector<int> path;
    std::vector<bool> prohod(points_count, false);
    tbb::mutex mutex;
    tbb::task_scheduler_init(THREADS);
    std::vector<int> min_vals(2, INT32_MAX);

    --start;
    --e_vertex;

    points_len[start] = 0;

    do {
        min_vals = tbb::parallel_reduce(
            tbb::blocked_range<int>(0, points_count),
            std::vector<int>(2) = { INT32_MAX, INT32_MAX },
            [&](const tbb::blocked_range<int>& v,
                std::vector<int> local_min_vals) {
            for (int i = v.begin(); i < v.end(); i++) {
                if (!prohod[i] && points_len[i] < local_min_vals[0]) {
                    local_min_vals[0] = points_len[i];
                    local_min_vals[1] = i;
                }
            }
            return local_min_vals;
        },
            [&](std::vector<int> x, std::vector<int> y) {
            if (x[0] < y[0]) {
                return x;
            }
            return y;
        });

        min_point = min_vals[1];
        min = min_vals[0];

        if (min_point != max_weight) {
            tbb::parallel_for(
                tbb::blocked_range<int>(0, points_count),
                [&](const tbb::blocked_range<int>& v) {
                for (int i = v.begin(); i < v.end(); i++) {
                    if (graph[min_point * points_count + i] > 0) {
                        mutex.lock();
                        time = min + graph[min_point * points_count + i];
                        if (points_len[i] > time) {
                            points_len[i] = time;
                        }
                        mutex.unlock();
                    }
                }
            });
            prohod[min_point] = true;
        }
    } while (min_point < max_weight);

    path.push_back(e_vertex + 1);
    int weight = points_len[e_vertex];

    int m = 1;
    std::vector <int> Money;
    for (int i = 0; i <= m; i++) {
        Money.push_back(i);
    }
    int Coin;
    std::vector <int> Coins;
    std::string str;
    std::string b;

    while (e_vertex != start) {
        std::vector<int> MinNumCoin;
        for (int i = 0; i <= m; i++) {
            MinNumCoin.push_back(i);
        }
        tbb::parallel_for(
            tbb::blocked_range<int>(0, points_count),
            [&](const tbb::blocked_range<int>& vertex) {
            for (int m = vertex.begin(); m < vertex.end(); m++) {
                if (graph[e_vertex * points_count + m] > 0) {
                    time = weight - graph[e_vertex * points_count + m];
                    if (points_len[m] == time) {
                        weight = time;
                        e_vertex = m;
                        mutex.lock();
                        path.push_back(m + 1);
                        mutex.unlock();
                    }
                }
            }
            for (int i = 0; i < Money.size(); i++) {
                MinNumCoin.push_back(MinNumCoin[i]);
                for (int j = 0; j < Coins.size(); j++) {
                    if (Money[i] >= Coins[j]) {
                        if (MinNumCoin[i - Coins[j]] + 1 < MinNumCoin[i]) {
                            MinNumCoin[i] = (MinNumCoin[i - Coins[j]] + 1);
                        }
                    }
                }
            }
        });
    }
    return path;
}
