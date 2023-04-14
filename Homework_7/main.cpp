#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <unordered_set>
#include <cmath>
#include <list>
#include <functional>

using namespace std;

double PodIntegralOwen(double x, double h) {
    return exp((-1.0/2.0)*h*h*(1.0 + x*x))/(1.0 + x*x);
}

double H = 0;

double PodIntegralOwen(double x) {
    return exp(-1.0/2.0*H*H*(1.0 + x*x))/(1.0 + x*x);
}

double simpsonIntegral(double a, double b, int n, const std::function<double (double)> &f) {
    const double width = (b-a)/n;

    double simpson_integral = 0;
    for(int step = 0; step < n; step++) {
        const double x1 = a + step*width;
        const double x2 = a + (step+1)*width;
        double dx = (x2-x1)/3.0;

        simpson_integral += ((f(x1) + 3.0*f(x1 + dx) + 3.0*f(x1 + 2*dx) + f(x2)))*3*dx/8;
    }

    return simpson_integral;
}

double Owen(double h, double a) {
    H = h;
    const std::function<double (double)> &f = [](double x){return PodIntegralOwen(x);};
    double integral = simpsonIntegral(0, a, 10, f);
    return integral/(2.0*M_PI);
}

double GaussLegandre(double h, double a){
    vector<double> w = {
            0,
            0.2955242247147529,
            0.2955242247147529,
            0.2692667193099963,
            0.2692667193099963,
            0.2190863625159820,
            0.2190863625159820,
            0.1494513491505806,
            0.1494513491505806,
            0.0666713443086881,
            0.0666713443086881
    };

    vector<double> x = {
            0,
            -0.148874338981631,
            0.1488743389816312,
            -0.433395394129247,
            0.4333953941292472,
            -0.679409568299024,
            0.6794095682990244,
            -0.865063366688984,
            0.8650633666889845,
            -0.973906528517171,
            0.9739065285171717
    };

    double sum = 0;
    for (int i = 1; i < 11; ++i) {
        sum += w[i] * PodIntegralOwen((a/2.0 + (x[i])*a/2.0), h);
    }

    return (a/2)*(sum)/(2.0*M_PI);
}

int main() {
    cout << "Newton Cotes" << endl;
    for (int i = 0; i < 10; ++i) {
        cout << i << ": " << Owen(2.5, i) << '\n';
    }

    cout << "\n";
    cout << "Gauss Legandre" << endl;
    for (int i = 0; i < 10; ++i) {
        cout << i << ": " << GaussLegandre(2.5, i) << '\n';
    }
}

