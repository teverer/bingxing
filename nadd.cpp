#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

long long flat_sum(int* a, int n) {
    long long sum = 0;
    for (int i = 0; i < n; ++i)
        sum += a[i];
    return sum;
}

long long two_way_sum(int* a, int n) {
    long long sum1 = 0, sum2 = 0;
    for (int i = 0; i < n; i += 2) {
        sum1 += a[i];
        sum2 += a[i + 1];
    }
    return sum1 + sum2;
}

//原地递归归并
long long guibing_sum(int* arr, int n) {
    //原地归并，两两相加，结果存在数组前面
    for (int m = n; m > 1; m /= 2) {
        for (int i = 0; i < m / 2; ++i) {
            arr[i] = arr[2 * i] + arr[2 * i + 1];
        }
    }
    return arr[0];  
}

double measure(long long (*func)(int*, int), int* arr, int n, const char* name) {
    clock_t start = clock();
    long long result = func(arr, n);
    clock_t end = clock();
    double ms = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
    cout << name << " : " << ms << " ms, 结果 = " << result << endl;
    return ms;
}

int main() {
    const int n = 1 << 20;   //1左移20位,也就是2^20
    int* data = new int[n];

    
    for (int i = 0; i < n; ++i)
        data[i] = i % 100;//取模100而不是i本身,i本身会导致了归并算法溢出

    measure(flat_sum, data, n, "平凡算法");
    measure(two_way_sum, data, n, "两路链式");

    //递归归并需要拷贝，因为会原地修改数组
    int* copy = new int[n];
    for (int i = 0; i < n; ++i)
        copy[i] = data[i];
    measure(guibing_sum, copy, n, "递归归并");
    delete[] copy;

    delete[] data;
    return 0;
}