// Copyright 2021 Panova Olga
#include "../../../modules/task_3/panova_o_shell_b_sort/shell_b_sort.h"
std::vector<int> CreateVector(int size) {
    std::random_device d;
    std::mt19937 g(d());
    std::vector<int> a(size);
    for (int i = 0; i < size; i++) {
        a[i] = g() % 111;
    }
    return a;
}
std::vector<std::vector<int>> Division(const std::vector<int>& a, int piece) {
    std::vector<std::vector<int>> res;
    int begin = 0;
    int end = a.size() / piece;
    int R = a.size() % piece;
    res.reserve(piece);
    for (int i = 0; i < piece; i++) {
        if (R > 0) {
            end++;
            R--;
        }
        std::vector<int> tmp(a.begin() + begin, a.begin() + end);
        res.push_back(tmp);
        begin = end;
        end += a.size() / piece;
    }
    return res;
}
std::vector<int> EvenMerge(const std::vector<int>& left, const std::vector<int>& right) {
    std::vector<int> res_a;
    int left_size = static_cast<int>(left.size());
    int right_size = static_cast<int>(right.size());
    int left_iter = 0, right_iter = 0;
    res_a.reserve((left_size + 1) / 2 + (right_size + 1) / 2);
    while ((left_iter < left_size) && (right_iter < right_size)) {
        if (left[left_iter] <= right[right_iter]) {
            res_a.push_back(left[left_iter]);
            left_iter += 2;
        } else {
            res_a.push_back(right[right_iter]);
            right_iter += 2;
        }
    }
    if (right_iter >= right_size) {
        for (int i = left_iter; i < left_size; i += 2) {
            res_a.push_back(left[i]);
        }
    } else {
        for (int i = right_iter; i < right_size; i += 2) {
            res_a.push_back(right[i]);
        }
    }
    return res_a;
}
std::vector<int> OddMerge(const std::vector<int>& left, const std::vector<int>& right) {
    std::vector<int> res;
    int left_size = static_cast<int>(left.size());
    int right_size = static_cast<int>(right.size());
    int left_iter = 1, right_iter = 1;
    res.reserve(left_size / 2 + right_size / 2);
    while ((left_iter < left_size) && (right_iter < right_size)) {
        if (left[left_iter] <= right[right_iter]) {
            res.push_back(left[left_iter]);
            left_iter += 2;
        } else {
            res.push_back(right[right_iter]);
            right_iter += 2;
        }
    }
    if (right_iter >= right_size) {
        for (int i = left_iter; i < left_size; i += 2) {
            res.push_back(left[i]);
        }
    } else {
        for (int i = right_iter; i < right_size; i += 2) {
            res.push_back(right[i]);
        }
    }
    return res;
}
std::vector<int> BatcherMerge(const std::vector<int>& left, const std::vector<int>& right) {
    std::vector<int> res;
    int left_size = static_cast<int>(left.size());
    int right_size = static_cast<int>(right.size());
    int res_size = left_size + right_size;
    int i, j, count;
    res.reserve(res_size);
    for (i = 0, j = 0, count = 0; i < left_size && j < right_size; i++, j++, count += 2) {
        res.push_back(left[i]);
        res.push_back(right[j]);
    }
    if (i < left_size && j >= right_size) {
        for (int k = count; k < res_size; k++, i++) {
            res.push_back(left[i]);
        }
    }

    for (int i = 1; i < res_size; i++) {
        if (res[i] < res[i - 1]) {
            std::swap(res[i], res[i - 1]);
        }
    }
    /*if (left_size == right_size) {
        for (int i = 0; i < left_size; i++) {
            res.push_back(left[i]);
            res.push_back(right[i]);
        }
    } else if (left_size == right_size + 2 || right_size == left_size + 2) {
        int i;
        for (i = 0; i < std::min(left_size, right_size); i++) {
            res.push_back(left[i]);
            res.push_back(right[i]);
        }
        if (left_size == right_size + 2) {
            res.push_back(left[i]);
            res.push_back(left[i + 1]);
        } else {
            res.push_back(right[i]);
            res.push_back(right[i + 1]);
        }
    } else if (left_size == right_size + 1 || right_size == left_size + 1) {
        int i;
        for (i = 0; i < std::min(left_size, right_size); i++) {
            res.push_back(left[i]);
            res.push_back(right[i]);
        }
        if (left_size == right_size + 1) {
            res.push_back(left[i]);
        } else {
            res.push_back(right[i]);
        }
    }
    for (int i = 1; i < res_size; i++) {
        if (res[i] < res[i - 1]) {
            std::swap(res[i], res[i - 1]);
        }
    }*/
    return res;
}
std::vector<int> ShellSort(const std::vector<int>& a) {
    std::vector<int> res(a);
    int size = static_cast<int>(res.size());
    int k, incr, tmp;
    int swp = 0, comp = 0;
    incr = size / 2;
    while (incr > 0) {
        for (int i = 0; i < incr; i++) {
            for (int j = 0; j < size; j += incr) {
                tmp = res[j];
                for (k = j - incr; k >= 0 && tmp < res[k]; k -= incr) {
                    comp++;
                    swp++;
                    res[k + incr] = res[k];
                }
                res[k + incr] = tmp;
                swp++;
            }
        }
        comp++;
        if (incr / 2 != 0) {
            incr = incr / 2;
        } else if (incr == 1) {
            incr = 0;
        } else {
            incr = 1;
        }
    }
    return res;
}
std::vector<int> ParallelOddEvenShellSort(const std::vector<int> a, int piece) {
    std::vector<std::vector<int>> temp = Division(a, piece);
    tbb::task_scheduler_init init(piece);
    tbb::parallel_for(tbb::blocked_range<size_t>(0, temp.size(), 1),
        [&temp](const tbb::blocked_range<size_t>& p) {
            for (int i = p.begin(); i != p.end(); ++i)
                temp[i] = ShellSort(temp[i]);
        }, tbb::simple_partitioner());
    init.terminate();
    std::vector<int> even;
    std::vector<int> odd;
    std::vector<int> reslt;
    reslt = temp[0];
    for (int i = 1; i < piece; i++) {
        even = EvenMerge(reslt, temp[i]);
        odd = OddMerge(reslt, temp[i]);
        reslt = BatcherMerge(even, odd);
    }
    return reslt;
}
std::vector<int> SequentialOddEvenShellSort(const std::vector<int> a, int piece) {
    std::vector<std::vector<int>> temp = Division(a, piece);

    for (int i = 0; i < piece; i++) {
        temp[i] = ShellSort(temp[i]);
    }
    std::vector<std::vector<int>> res(temp);
    std::vector<int> even;
    std::vector<int> odd;
    int k = piece;
    while (k != 1) {
        std::vector<std::vector<int>> tmp(k / 2 + k % 2);
        std::vector<std::vector<int>> left(k / 2);
        std::vector<std::vector<int>> right(k / 2);
        int j = 0;
        for (int i = 0; i < k - 1; i += 2, j++) {
            left[j] = res[i];
            right[j] = res[i + 1];
        }
        int size = static_cast<int>(left.size());
        for (j = 0; j != size; j++) {
            even = EvenMerge(left[j], right[j]);
            odd = OddMerge(left[j], right[j]);
            tmp[j] = BatcherMerge(even, odd);
        }
        if (k % 2 == 1) {
            tmp[size] = res[k - 1];
        }
        res = tmp;
        k = (k + 1) / 2;
    }
    return res[0];
}
