#ifndef HW_STATISTICS
#define HW_STATISTICS

class Statistics {
public:
    void update(float x);            // добавить новый элемент
    int count() const;
    float min() const;
    float max() const;
    float sum() const;
    float mean() const;     // среднее
    float variance() const; // дисперсия
private:
    float _min = 0;
    float _max = 0;
    float _sum = 0;
    float _mean = 0;
    int _count = 0;
    float _m = 0;
};

#endif
