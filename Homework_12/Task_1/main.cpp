#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>
#include <cassert>
#include <iomanip>

using namespace std;

void LU(const vector<vector<float>>& A, vector<vector<float>>& L, vector<vector<float>>& U) {
    int n = A.size();
    U = A;
    for (int i = 0; i < n; i++) {
        L[i][i] = 1;
        assert (A[i][i] != 0);
    }

    for (int ni = 0; ni < n - 1; ni++) {
        for (int j = ni; j < n; j++) {
            for (int i = j; i < n; i++) {
                L[i][j] = U[i][j] / U[j][j];
            }
        }
            
        for (int i = ni + 1; i < n; i++) {
            for (int j = ni; j < n; j++) {
                U[i][j] -= L[i][ni] * U[ni][j];
            }
        }
    }
}

float det(const vector<vector<float>>& A) {
    int n = A.size();
    vector<vector<float>> L = vector<vector<float>>(n, vector<float>(n, 0));
    vector<vector<float>> U = vector<vector<float>>(n, vector<float>(n, 0));
    LU(A, L, U);
    float prod = 1.f;
    for (int i = 0; i < n; i++) {
        prod *= U[i][i];
    }
    return prod;
}

void CheckCorrectnessUsingMultiplication(const vector<vector<float>>& A, float epsilon = 1e-5) {
    int n = A.size();
    vector<vector<float>> L = vector<vector<float>>(n, vector<float>(n, 0));
    vector<vector<float>> U = vector<vector<float>>(n, vector<float>(n, 0));
    vector<vector<float>> C = vector<vector<float>>(n, vector<float>(n, 0));
    LU(A, L, U);
    for (int i = 0; i < L.size(); i++) {
        for (int j = 0; j < L.size(); j++) {
            for (int l = 0; l < L.size(); l++) {
                C[i][j] += L[i][l] * U[l][j];
            }
        }
    }
    float sum = 0.f;
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < A.size(); j++) {
            sum += A[i][j] - C[i][j];
        }
    }
    assert (abs(sum / A.size() / A.size()) < epsilon);
}

int main() {
    vector<vector<float>> A = {
            {86.81, 47.95, 65.57, 69.26, 33.35},
            {44.82, 90.32, 63.29, 26.98, 64.56},
            {28.37, 80.81, 45.98, 50.85, 55.50},
            {54.08, 94.75, 71.01, 66.71, 48.10},
            {79.63, 27.16, 95.16, 56.54, 19.81},
    };
    CheckCorrectnessUsingMultiplication(A);
    cout << det(A) << '\n';
}