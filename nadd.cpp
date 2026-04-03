#include <iostream>
#include <cstdlib>
#include <ctime>


using namespace std;

const int REPEAT = 100; //测量次数

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

//原地递归归并, but会修改数组
long long guibing_sum(int* arr, int n) {
    for (int m = n; m > 1; m /= 2) {
        for (int i = 0; i < m / 2; ++i) {
            arr[i] = arr[2 * i] + arr[2 * i + 1];
        }
    }
    return arr[0];
}

int main() {
    const int n = 1 << 20;   //1左移20位,也就是2^20
    int* data = new int[n];

   
    for (int i = 0; i < n; ++i)
        data[i] = i % 100;

    //正确性验证
    cout << "=== 正确性验证 ===" << endl;
    cout << "平凡算法结果: " << flat_sum(data, n) << endl;
    cout << "两路链式结果: " << two_way_sum(data, n) << endl;

    int* copy_check = new int[n];
    for (int i = 0; i < n; ++i) copy_check[i] = data[i];
    cout << "递归归并结果: " << guibing_sum(copy_check, n) << endl;
    delete[] copy_check;
    cout << endl;

    //多次测量性能
    cout << "=== 性能测量 (重复" << REPEAT << "次取平均) ===" << endl;

    //平凡算法
    double total_flat = 0.0;
    for (int t = 0; t < REPEAT; ++t) {
        clock_t start = clock();
        long long res = flat_sum(data, n);
        clock_t end = clock();
        total_flat += (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
        
    }
    cout << "平凡算法平均耗时: " << total_flat / REPEAT << " ms" << endl;

    //两路链式
    double total_two = 0.0;
    for (int t = 0; t < REPEAT; ++t) {
        clock_t start = clock();
        long long res = two_way_sum(data, n);
        clock_t end = clock();
        total_two += (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
       
    }
    cout << "两路链式平均耗时: " << total_two / REPEAT << " ms" << endl;

    //递归归并,每次测量需拷贝原始数据
    double total_gui = 0.0;
    int* work = new int[n];
    for (int t = 0; t < REPEAT; ++t) {
        //拷贝原始数据
        for (int i = 0; i < n; ++i) work[i] = data[i];
        clock_t start = clock();
        long long res = guibing_sum(work, n);
        clock_t end = clock();
        total_gui += (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
        
    }
    cout << "递归归并平均耗时: " << total_gui / REPEAT << " ms" << endl;
    delete[] work;

    delete[] data;
    return 0;
}