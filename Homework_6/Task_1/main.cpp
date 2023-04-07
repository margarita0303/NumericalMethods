#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <sstream>
#include <cassert>

struct point {
    float x;
    float y;
    float z;
};

struct triangle {
    point x;
    point y;
    point z;

    float sign(point p1, point p2, point p3){  return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y); };

    bool inside(point p) {
        float d1, d2, d3;
        bool has_neg, has_pos;

        d1 = sign(p, x, y);
        d2 = sign(p, y, z);
        d3 = sign(p, z, x);

        has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
        has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

        return !(has_neg && has_pos);
    }
};

std::vector<std::string> split(const std::string &s, const std::string &delim) {
    std::vector<std::string> ans;
    auto start = 0U;
    auto end = s.find(delim);
    while (end != std::string::npos) {
        ans.push_back(s.substr(start, end - start));
        start = end + delim.length();
        end = s.find(delim, start);
    }
    ans.push_back(s.substr(start, end));
    return ans;
}

void read_surface(std::vector<std::vector<point>> &x) {
    std::ifstream in("surface.xyz");
    std::string point;
    int x_id = 0;
    int y_id = 0;
    while (std::getline(in, point)) {
        auto xyz = split(point, " ");
        float x_ = std::stof(xyz[0]);
        float y_ = std::stof(xyz[1]);
        float z_ = std::stof(xyz[2]);

        x[x_id][y_id] = {x_, y_, z_};
        y_id++;

        if (y_id == 128) {
            y_id = 0;
            x_id++;
        }
    }
}

void process_triagnles(const std::vector<std::vector<point>> &x, std::vector<triangle> &trgs) {
    for (int i = 0; i < 128 - 1; i++) {
        for (int j = 0; j < 128 - 1; j++) {
            triangle t1 = { x[i][j], x[i + 1][j], x[i + 1][j + 1] };
            triangle t2 = { x[i][j], x[i][j + 1], x[i + 1][j + 1] };
            trgs.push_back(t1);
            trgs.push_back(t2);
        }
    }
}

int main() {
    std::vector<std::vector<point>> x(128, std::vector<point>(128));
    std::vector<triangle> trgls;
    read_surface(x);
    process_triagnles(x, trgls);

    std::cout << "Input point_x, point_y:" << std::endl;
    float x_in, y_in;
    std::cin >> x_in >> y_in;
    point p = {x_in, y_in, 0};

    for (auto &t: trgls) {
        if (t.inside(p)) {
            float d = (t.y.y - t.z.y) * (t.x.x - t.z.x) + (t.z.x - t.y.x) * (t.x.y - t.z.y);
            float t1 = 1 / d * (t.y.y - t.z.y) * (p.x - t.z.x) + (t.z.x - t.y.x) * (p.y - t.z.y);
            float t2 = 1 / d * (t.z.y - t.x.y) * (p.x - t.z.x) + (t.x.x - t.z.x) * (p.y - t.z.y);
            float t3 = 1 - t1 - t2;
            std::cout << t1 * t.x.z + t2 * t.y.z + t3 * t.z.z << std::endl;
            break;
        }
    }
}
