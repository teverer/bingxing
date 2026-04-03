#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int n = 2048;   //矩阵大小
const int REPEAT = 10; //测量次数

//平凡算法,列优先访问，内层循环行索引变化，步长大，缓存不友好
void pingxingAlgo(double* B, double* a, double* sum, int n) {
    for (int i = 0; i < n; ++i)
        sum[i] = 0.0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            sum[i] += B[j * n + i] * a[j];
        }
    }
}

//优化算法,行优先访问，内层循环列索引连续
void youhuaAlgo(double* B, double* a, double* sum, int n) {
    for (int i = 0; i < n; ++i)
        sum[i] = 0.0;
    for (int j = 0; j < n; ++j) {
        double aj = a[j];
        double* row = B + j * n;
        for (int i = 0; i < n; ++i) {
            sum[i] += row[i] * aj;
        }
    }
}

int main() {
    double* B = new double[n * n];
    double* a = new double[n];
    double* sum = new double[n];

    
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < n; ++i) {
            B[j * n + i] = i + j;
        }
        a[j] = j;
    }

    //正确性验证,输出前5个结果
    cout << "=== 正确性验证 ===" << endl;
    pingxingAlgo(B, a, sum, n);
    cout << "平凡算法前5个结果: ";
    for (int i = 0; i < 5; ++i) cout << sum[i] << " ";
    cout << endl;

    youhuaAlgo(B, a, sum, n);
    cout << "优化算法前5个结果: ";
    for (int i = 0; i < 5; ++i) cout << sum[i] << " ";
    cout << endl << endl;

    //多次测量性能
    cout << "=== 性能测量 (重复" << REPEAT << "次取平均) ===" << endl;

    //平凡算法多次测量
    double total1 = 0.0;
    for (int t = 0; t < REPEAT; ++t) {
        clock_t start = clock();
        pingxingAlgo(B, a, sum, n);
        clock_t end = clock();
        total1 += (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
    }
    double avg1 = total1 / REPEAT;
    cout << "平凡算法平均耗时: " << avg1 << " ms" << endl;

    //优化算法多次测量
    double total2 = 0.0;
    for (int t = 0; t < REPEAT; ++t) {
        clock_t start = clock();
        youhuaAlgo(B, a, sum, n);
        clock_t end = clock();
        total2 += (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
    }
    double avg2 = total2 / REPEAT;
    cout << "优化算法平均耗时: " << avg2 << " ms" << endl;

    delete[] B;
    delete[] a;
    delete[] sum;
    return 0;
}