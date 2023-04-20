#include <bits/stdc++.h>
#include <iostream>
#include <cstdint>
#include <cstring>

using namespace std;

void thomas(const float* a_, const float* b_, const float* c_, const float* d_, float* x, int n) {
    float* a = new float[n-1];
    float* b = new float[n];
    float* c = new float[n-1];
    float* d = new float[n];
    std::memcpy(b,b_,sizeof(int)*n);
    std::memcpy(d,d_,sizeof(int)*n);
    std::memcpy(c,c_,sizeof(int)*(n-1));
    std::memcpy(a,a_,sizeof(int)*(n-1));
    for (int i=1; i<n; ++i) {
        float w = a[i] / b[i-1];
        b[i] -= w*c[i-1];
        d[i] -= w*d[i-1];
    }
    x[n-1] = d[n-1] / b[n-1];
    for (int i=n-2; i>=0; --i) {
        x[i] = (d[i] + c[i]*x[i+1]) / b[i];
    }
}

float* diffusion(float XMin, float XMax, int ansIndexX, float t_size, float dt, float dx, float k) {
    int size = (int) ceil((XMax - XMin) / dx) + 1;
    cout << "x size: " << size << '\n';
    float C = k * (dt)/pow((dx), 2);
    float K = 1 + 2 * C;
    float* a = new float[size - 3];
    float* b = new float[size - 2];
    float* c = new float[size - 3];
    for (int i = 0; i < size - 2; ++i) {
        b[i] = K;
    }
    for (int i = 0; i < size - 3; ++i) {
        a[i] = -C;
        c[i] = -C;
    }
    float* cur = new float[size - 2];
    float* prev = new float[size - 2];
    float curX = XMin;
    for (int i = 0; i < size - 2; i++) {
        prev[i] = exp(-curX * curX);
        curX = i == size - 1 ? XMax : curX + dx;
    }
    thomas(a, b, c, prev, cur, size - 2);
    cur[0] = cur[size-3] = 0;
    for (int i = 1; i < t_size; ++i) {
        std::memcpy(prev,cur,sizeof(int)*(size-2));
        thomas(a, b, c, prev, cur,  size-2);
        cur[0] = cur[size-3] = 0;
    }
    return cur;
}

int main() {
    float* res = diffusion(1.0, 3, 10, 3, 0.1, 0.1, 0.2);
    for(int i = 0; i < 21; i++){
        cout << res[i] << '\n';
    }
    std::cout << res << '\n';
    return 0;
}
