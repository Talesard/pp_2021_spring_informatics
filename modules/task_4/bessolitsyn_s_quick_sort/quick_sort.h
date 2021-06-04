// Copyright 2021 Bessolitsyn Sergay
#ifndef MODULES_TASK_4_BESSOLITSYN_S_QUICK_SORT_QUICK_SORT_H_
#define MODULES_TASK_4_BESSOLITSYN_S_QUICK_SORT_QUICK_SORT_H_


#include <vector>
#include <random>
#include <utility>

#include "../../../3rdparty/unapproved/unapproved.h"

template<typename T>
void quick_sort(T arr[], int right) {
    if (right > 1) {
        int rand_id = std::rand() % right;
        int k = 0;
        std::swap(arr[0], arr[rand_id]);
        for (int i = 1; i < right; ++i) {
            if (arr[i] < arr[0]) {
                std::swap(arr[i], arr[++k]);
            }
        }
        std::swap(arr[0], arr[k]);
        quick_sort(arr, k);
        quick_sort(arr + k + 1, right - k - 1);
    }
}

template<typename T>
void merge(T arr1[], int size1, T arr2[], int size2) {
    T* tmp_arr = new T[size1 + size2];
    int i = 0, j = 0, k = 0;
    for (; i < size1 && j < size2; ++k) {
        if (arr1[i] < arr2[j])
            tmp_arr[k] = arr1[i++];
        else
            tmp_arr[k] = arr2[j++];
    }
    while (i < size1) {
        tmp_arr[k++] = arr1[i++];
    }
    while (j < size2) {
        tmp_arr[k++] = arr2[j++];
    }
    for (i = 0; i < k; ++i) {
        arr1[i] = tmp_arr[i];
    }
    delete[] tmp_arr;
}

template<typename T>
void quick_sort_STD(std::vector<T>* vec) {
    int size = vec->size();
    int parts = std::thread::hardware_concurrency();  // 6;  // how many parts
    int delta = size / parts;  // a.k.a grainsize
    std::vector<std::thread> th_vec;
    for (int i = 0; i < parts - 1; ++i) {
        std::thread thread([&](int i) {
            quick_sort(vec->data() + i * delta, delta);
            }, i);
        th_vec.emplace_back(std::move(thread));
    }
    std::thread thread([&]() {
        quick_sort(vec->data() + (parts-1) * delta, size - (parts - 1) * delta);
        });
    th_vec.emplace_back(std::move(thread));
    for (int i = 0; i < parts; ++i) {
        th_vec[i].join();
    }
    for (int i = 1; i < parts - 1; ++i) {
        merge(vec->data(), i * delta, vec->data() + i * delta, delta);
    }
    merge(vec->data(), delta * (parts - 1), vec->data() + delta * (parts - 1), size - delta * (parts - 1));
}

std::vector<int> getRandomVector(int size, uint64_t seed = 50);
std::vector<double> getRandomDoubleVector(int size, uint64_t seed = 50);

#endif  // MODULES_TASK_4_BESSOLITSYN_S_QUICK_SORT_QUICK_SORT_H_
