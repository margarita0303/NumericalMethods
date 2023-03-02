#include <algorithm>
#include "Statistics.h"

void Statistics::update(float x) {
    if (_count == 0) {
        _min = _max = x;
    } else {
        _min = std::min(_min, x);
        _max = std::max(_max, x);
    }
    _count++;
    _sum += x;

    float mean = _mean + (x - _mean) / (float) _count;
    _m = _m + (x - _mean) * (x - mean);
    _mean = mean;
}

int Statistics::count() const {
    return _count;
}

float Statistics::min() const {
    return _min;
}

float Statistics::max() const {
    return _max;
}

float Statistics::sum() const {
    return _sum;
}

float Statistics::mean() const {
    return _mean;
}

float Statistics::variance() const {
    return _m / (float) count();
}