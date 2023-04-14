#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

const float time_delta = 1e-3;
const float eps = 1e-5;
float alpha = 50;

float f(float pos, float t, float x) 
{
    return exp(-x*x) * exp(-pow(pos - x, 2)/2/alpha/t);
}

float Integrate(float left, float right, float t, float iterations, float pos) {
    float result = 0;
    float step = (right - left) / iterations;
    for (int i = 0; i < iterations; i++) {
        float x = left + step * i;
        float prev_x = left + step * (i - 1);
 
        result += step / 2 * (f(pos, t, x) + f(pos, t, prev_x));
    }
 
    return result / 2 / sqrt(M_PI * alpha * t);
}
 
float CalculateTemps(float t, float l, int iterations, std::vector<float> &temps) {
    float result = 0;
    for (int i = 0; i < iterations; ++i) {
        temps[i] = Integrate(0, l, t, iterations, i * l / iterations);
        result += temps[i];
    }
    return result / iterations;
}

int main()
{
    int iterations;
    float t, l; 
    cin >> iterations >> l;

    t = 0;
    vector<float> temps(iterations);
    bool is_changed = true;

    while (is_changed) {
        is_changed = false;
        t += time_delta;
        float avg = CalculateTemps(t, l, iterations, temps);
        for (int i = 0; i < iterations; i++) {
            if (abs(avg - temps[i]) > eps) {
                is_changed = true;
            }
        } 
    }  

    cout << t << endl;
    cout << CalculateTemps(t, l, iterations, temps) << endl;
} 
