#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include<algorithm>
using namespace std;

//平凡算法（链式累加）
long long naive_sum(const int* arr, int n) {
    long long sum = 0;
    for (int i = 0; i < n; ++i)
        sum += arr[i];
    return sum;
}

//两路链式累加
long long two_way_sum(const int* arr, int n) {
    long long sum1 = 0, sum2 = 0;
    for (int i = 0; i < n; i += 2) {
        sum1 += arr[i];
        sum2 += arr[i + 1];
    }
    return sum1 + sum2;
}

//递归归并
long long recursive_sum(int* arr, int n) {
    for (int m = n; m > 1; m /= 2)
        for (int i = 0; i < m / 2; ++i)
            arr[i] = arr[2 * i] + arr[2 * i + 1];
    return arr[0];
}

int main() {
    const int n = 1 << 20;   //2^20
    int* data = new int[n];
    srand(time(nullptr));
    for (int i = 0; i < n; ++i)
        data[i] = rand() % 100;

    // 计时辅助 lambda（直接输出毫秒）
    auto measure = [&](auto func, const char* name) {
        auto start = chrono::high_resolution_clock::now();
        volatile long long result = func();   // volatile 防止被优化
        auto end = chrono::high_resolution_clock::now();
        double ms = chrono::duration<double, milli>(end - start).count();
        cout << name << " : " << ms << " ms, 结果 = " << result << endl;
    };

    // 测试平凡算法
    measure([&]() { return naive_sum(data, n); }, "平凡算法");

    // 测试两路链式
    measure([&]() { return two_way_sum(data, n); }, "两路链式");

    // 测试递归归并（需要拷贝原数组，因为会修改）
    int* copy = new int[n];
    std::copy(data, data + n, copy);
    measure([&]() { return recursive_sum(copy, n); }, "递归归并");
    delete[] copy;

    delete[] data;
    return 0;
}