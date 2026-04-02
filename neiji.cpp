#include <iostream>
//计时库
#include <chrono>
using namespace std;
using namespace chrono;

//矩阵大小n
const int n = 2048;

int main() {
    
   
    double** B = new double*[n];
    double* a = new double[n];
    
    double* sum = new double[n];

    
    for (int j = 0; j < n; j++) {
        B[j] = new double[n];
        for (int i = 0; i < n; i++) {
            B[j][i] = i + j;  //固定值
        }
        a[j] = j;  //赋值
    }

   
    auto start1 = high_resolution_clock::now(); //计时开始
    for (int i = 0; i < n; i++) {
        sum[i] = 0.0;
        for (int j = 0; j < n; j++) {
            sum[i] += B[j][i] * a[j]; 
        }
    }
    auto end1 = high_resolution_clock::now();   //计时结束
    auto time1 = duration_cast<microseconds>(end1 - start1).count();

    //验证正确
    cout << "=== 平凡算法运行时间：" << time1 << " 微秒 ===" << endl;
    cout << "前5个计算结果：";
    for (int i = 0; i < 5; i++) cout << sum[i] << " ";
    cout << endl << endl;

    //优化算法：逐行计算内积
    auto start2 = high_resolution_clock::now(); //计时开始
    //初始化sum为0
    for (int i = 0; i < n; i++) sum[i] = 0.0;
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            sum[i] += B[j][i] * a[j]; 
        }
    }
    auto end2 = high_resolution_clock::now();   //计时结束
    auto time2 = duration_cast<microseconds>(end2 - start2).count();

   
    cout << "=== 优化算法运行时间：" << time2 << " 微秒 ===" << endl;
    cout << "前5个计算结果：";
    for (int i = 0; i < 5; i++) cout << sum[i] << " ";
    cout << endl << endl;

    for (int j = 0; j < n; j++) delete[] B[j];
    delete[] B;
    delete[] a;
    delete[] sum;

    return 0;
}