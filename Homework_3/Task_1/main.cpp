#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <math.h>

class TaskRastring {
public:
    virtual float obj(float x) {
        return 10 + pow(x, 2) - 10 * cos(2*M_PI*x);
    }
    virtual float derivative(float x) {
        return 2 * x + 20 * M_PI * sin(2*M_PI*x);
    }
    virtual float derivative2(float x) {
        return 2 + 40 * M_PI * M_PI * cos(2*M_PI*x);
    }
};

class Bisection {
public:
    TaskRastring *task;
    int operations = 0;

    float minimize(float left, float right, float eps, float eps2) {
        float global_min = 0;

        if (task->derivative(left) <= 0 && task->derivative(right) >= 0) {
            float tmp = left;
            left = right;
            right = tmp;
        }

        while (abs(right - left) > eps) {
            float middle = (right + left) / 2;
            operations += 1;

            if (task->derivative(middle) > 0) {
                left = middle;
            } 
            else {
                right = middle;
            }

            if (abs(task->derivative(left)) < eps2) {
                return left;
            }
            
            if (abs(task->derivative(right)) < eps2) {
                return right;
            }

            if (operations > 1000) {
                operations = -1;
                return left;
            }
        }

        if (abs(task->derivative(left)) < eps2) {
            return left;
        } 
        else {
            std::cout << "Try to increase eps2 or decrease eps.";
            operations = -1;
            return left;
        }
    }
};

class Neuton {
public:
    TaskRastring *task;
    int operations = 0;

    float minimize(float x, float eps) {
        float current = x;
        float next = x + 2 * eps;

        while (abs(current - next) > eps) {
            operations++;
            current = next;

            if (task->derivative2(current) == 0) {
                next = current - (task->derivative(current)) * eps;
            }
            else {
                next = current - (task->derivative(current)/task->derivative2(current));
            }

            if (operations > 3000) {
                operations = -1;
                return next;
            }

            if (abs(task->derivative(current)) < eps) {
                return current;
            }
        }
        
        if (abs(task->derivative(next)) < eps) {
            return next;
        } 
        else {
            operations = -1;
            return next;
        }
    }
};

int main() {
    std::cout << "Derivative(5): " << (new TaskRastring())->derivative(5) << '\n';
    std::cout << "Derivative(-4): " << (new TaskRastring())->derivative(-4) << '\n';
    // где-то между ними есть ноль

    Bisection bisection_solver = *new Bisection();
    bisection_solver.task = new TaskRastring();
    std::cout << "\nBisection solver\n";
    float result = bisection_solver.minimize(5, -4, 0.000001, 0.0001);
    std::cout.precision(20);
    std::cout << "Result: " << result << '\n';
    std::cout << "Bisection solver operations: " << bisection_solver.operations << '\n';
    std::cout.precision(20);
    std::cout << "Derivative(result): " << (new TaskRastring())->derivative(result) << '\n';

    std::cout << "\nNeuton solver\n";
    Neuton neuton_solver = *new Neuton();
    neuton_solver.task = new TaskRastring();
    float result2 = neuton_solver.minimize(2, 0.001);
    std::cout.precision(20);
    std::cout << "Result: " << result2 << '\n';
    std::cout << "Neuton solver operations: " << neuton_solver.operations << '\n';
    std::cout.precision(20);
    std::cout << "Derivative(result): " << (new TaskRastring())->derivative(result) << '\n';

    // Вывод на консоли:
    // Derivative(5): 10
    // Derivative(-4): -8

    // Bisection solver
    // Result: -2.98485565185546875
    // Bisection solver operations: 23
    // Derivative(result): 1.9427599909249693155e-05

    // Neuton solver
    // Result: 1.9899122714996337891
    // Neuton solver operations: 2
    // Derivative(result): 1.9427599909249693155e-05

    // Видно, что Ньютон сходится за 2 шага. Это связано с тем, что вторая проивзодная не сложная и 
    // минимум нашелся быстро, а также в связи с ранним выскакиванием.
    // А точность здесь сильно увеличить не получится, потому что метод быстро начнёт зацикливаться.

}


