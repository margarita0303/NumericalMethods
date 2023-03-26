#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <math.h>

using namespace std;

class Task {
public:
    virtual float obj(float x) { 
        return 0; 
    };

    virtual float derivative(float x) { 
        return 0; 
    };

    virtual float derivative2(float x) { 
        return 0; 
    };
};

class Rastring : public Task {
public:
    virtual float obj(float x) override {
        return 10 + pow(x, 2) - 10 * cos(2 * M_PI * x);
    }

    virtual float derivative(float x) override {
        return 2 * x + 20 * M_PI * sin(2 * M_PI * x);
    }

    virtual float derivative2(float x) override {
        return 2 + 40 * M_PI * M_PI * cos(2 * M_PI * x);
    }
};


class RandomSearch {
public:
    Task *task;
    int operations = 0;
    vector<float> points;
    vector<float> objects;
    float globalmax = -100000;
    float globalresult;
    float maximize(float x1, float x2, float count) {
        const float L = 1;
        std::srand(std::time(nullptr));
        float current = (x1 + x2)/2;
        float next;
        for (int i = 0; i < count; ++i) {
            operations++;
            int r = std::rand();
            next = (float)r/(float)RAND_MAX * (x2 - x1) + x1;
            if(task->obj(next) > globalmax){
                globalmax = task->obj(next);
                globalresult = next;
            }
        }
        return globalresult;
    }
};
class LiPo {
public:
    Task *task;
    int operations = 0;
    vector<float> points;
    vector<float> objects;
    float globalmax = -100000;
    float globalresult;
    float maximize(float x1, float x2, float count) {
        const float L = 1;
        std::srand(std::time(nullptr));
        float current = (x1 + x2)/2;
        float next;
        while(operations < count) {
            int r = std::rand();
            float next_delta;
            if(r%2==0){
                next_delta = ((float)r/(float)RAND_MAX);
            }else{
                next_delta = (-1)*((float)r/(float)RAND_MAX);
            }
            while(next + next_delta > x2 || next + next_delta < x1 ){
                int r = std::rand();
                if (r%2==0) {
                    next_delta = ((float)r/(float)RAND_MAX);
                } else {
                    next_delta = (-1)*((float)r/(float)RAND_MAX);
                }
            }
            float min = 10000;
            for (float a: objects) {
                if(a + L*(abs(next - a)) < min){
                    min = a + L*(abs(next - a));
                }
            }
            float max = -10000;
            for (float a: objects) {
                if(a > max){
                    max = a;
                }
            }
            if (min >= max) {
                operations++;
                next = next + next_delta;
                if(task->obj(next) > globalmax){
                    globalmax = task->obj(next);
                    globalresult = next;
                }
            }
            else
            {
                continue;
            }
        }
        return globalresult;
    }
};


void TestLiPo(int count){
    cout << "LIPO TEST, count: " << count << "\n";
    LiPo solver2 = *new LiPo();
    solver2.task = new Rastring();
    float result2 = solver2.maximize(-9.0, 10.0, count);
    cout.precision(20);
    cout << "Result: " << result2 << '\n';
    cout << "Operations: " << solver2.operations << '\n';
    cout << "Obj(result): " << (new Rastring())->obj(result2) << "\n\n";
}

void TestRand(int count){
    cout << "RAND TEST, count: " << count << "\n";
    RandomSearch solver = *new RandomSearch();
    solver.task = new Rastring();
    float result = solver.maximize(-9.0, 10.0, count);
    cout.precision(20);
    cout << "Result: " << result << '\n';
    cout << "Operations: " << solver.operations << '\n';
    cout << "Obj(result): " << (new Rastring())->obj(result) << "\n\n";
}

int main() {
    for (int i = 2; i < 5; ++i) {
        TestRand(pow(10, i));
    }
    for (int i = 2; i < 5; ++i) {
        TestLiPo(pow(10, i));
    }
}


// Мой вывод на консоли:

// RAND TEST, count: 100
// Result: 9.5232181549072265625
// Operations: 100
// Obj(result): 110.5854644775390625

// RAND TEST, count: 1000
// Result: 9.5529575347900390625
// Operations: 1000
// Obj(result): 110.71050262451171875

// RAND TEST, count: 10000
// Result: 9.5507144927978515625
// Operations: 10000
// Obj(result): 110.71274566650390625

// LIPO TEST, count: 100
// Result: 9.5496015548706054688
// Operations: 100
// Obj(result): 110.71315765380859375

// LIPO TEST, count: 1000
// Result: 9.5496015548706054688
// Operations: 1000
// Obj(result): 110.71315765380859375

// LIPO TEST, count: 10000
// Result: 9.5496015548706054688
// Operations: 10000
// Obj(result): 110.71315765380859375

// На небольших точностях сложно заметить, кто из них быстрее сходится,
// но кажется, что Липо быстрее раз в 10.
 
