#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>
#include "Statistics.h"

int main() {
    Statistics statistics;
    std::vector<float> data = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0};
    for (auto value: data) statistics.update(value);
    assert(statistics.count() == 7);
    assert(statistics.sum() == 28.0);
    assert(statistics.mean() == 4.0);
    assert(statistics.variance() == 4.0);
    assert(statistics.min() == 1.0);
    assert(statistics.max() == 7.0);
    std::cout << "OK: Tests passed." << std::endl;
}