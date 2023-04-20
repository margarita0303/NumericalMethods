#include <bits/stdc++.h>

double SolveEquation(double xMin, double xMax, double dt, double dx, double v) {
    int size = (int) ceil((xMax - xMin) / dx) + 1;
    std::vector<double> cur(size), prev(size);
    double curX = xMin;

    for (int i = 0; i < size; i++) {
        prev[i] = exp(-curX * curX);
        if (i == size - 1) {
            curX = xMax;
        }
        else {
            curX = curX + dx;
        }
    }
    
    double t = 0;

    if (std::all_of(prev.begin(), prev.end(), [&prev](double p) { return std::abs(prev.front() - p) < 1e-5; })) {
        return t;
    }

    while (true) {
        if (v > 0) {
            cur[0] = prev[0] - v * (dt / dx) * (prev[0] - prev[size - 1]);
            for (int j = 1; j < size; j++) {
                cur[j] = prev[j] - v * (dt / dx) * (prev[j] - prev[j - 1]);
            }
        } 
        else {
            cur[size - 1] = prev[size - 1] - v * (dt / dx) * (prev[size - 1] - prev[0]);
            for (int j = size - 2; j >= 0; j--) {
                cur[j] = prev[j] - v * (dt / dx) * (prev[j] - prev[j + 1]);
            }
        }
        prev = cur;

        if (std::all_of(cur.begin(), cur.end(), [&cur](double p) { return std::abs(cur.front() - p) < 1e-5; })) {
            break;
        }

        t += dt;
    }

    return t;
}

int main() {
    double result = SolveEquation(1.0, 3, 0.1, 0.1, 0.5);
    std::cout << result << std::endl;
    return 0;
}
