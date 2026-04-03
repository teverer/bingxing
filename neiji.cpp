#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int n = 2048;   //矩阵大小

//平凡算法：列优先访问,内层循环行索引变化，步长大，缓存不友好
void pingxingAlgo(double* B, double* a, double* sum, int n) {
    
    for (int i = 0; i < n; ++i)
        sum[i] = 0.0;
    //列优先计算
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            sum[i] += B[j * n + i] * a[j];
        }
    }
}

//优化算法：行优先访问,内层循环列索引连续
void youhuaAlgo(double* B, double* a, double* sum, int n) {
    
    for (int i = 0; i < n; ++i)
        sum[i] = 0.0;
    //行优先计算
    for (int j = 0; j < n; ++j) {
        double aj = a[j];
        double* row = B + j * n;   //第 j 行的起始地址
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

    //平凡算法
    clock_t start1 = clock();
    pingxingAlgo(B, a, sum, n);
    clock_t end1 = clock();
    double ms1 = (double)(end1 - start1) / CLOCKS_PER_SEC * 1000.0;
    cout << "平凡算法（列优先） : " << ms1 << " ms, 前5个结果 = ";
    for (int i = 0; i < 5; ++i)
        cout << sum[i] << " ";
    cout << endl;

    //优化算法
    clock_t start2 = clock();
    youhuaAlgo(B, a, sum, n);
    clock_t end2 = clock();
    double ms2 = (double)(end2 - start2) / CLOCKS_PER_SEC * 1000.0;
    cout << "优化算法（行优先） : " << ms2 << " ms, 前5个结果 = ";
    for (int i = 0; i < 5; ++i)
        cout << sum[i] << " ";
    cout << endl;

    
    delete[] B;
    delete[] a;
    delete[] sum;

    return 0;
}