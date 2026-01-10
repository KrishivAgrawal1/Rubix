#pragma once
#include "constants.h"
#include "geometry.h"
#include <string>
#include <vector>
using namespace std;

class facelet {
public:
    point3d posn;
    point3d normal;
};

class cube {
public:
    vector<color> data;
    vector<facelet> mappings;
    vector<vector<point3d>> mesh;

    // functions:
    cube();
    void rotate(char axis, int layer, double angle);

    void cube_f() {
        this->rotate('x', 1, -pi / 2);
    }
    void cube_b() {
        this->rotate('x', -1, pi / 2);
    }
    void cube_u() {
        this->rotate('y', 1, -pi / 2);
    }
    void cube_d() {
        this->rotate('y', -1, pi / 2);
    }
    void cube_l() {
        this->rotate('z', 1, -pi / 2);
    }
    void cube_r() {
        this->rotate('z', -1, pi / 2);
    }
    void cube_f1() {
        this->rotate('x', 1, -pi / 2);
    }
    void cube_b1() {
        this->rotate('x', -1, pi / 2);
    }
    void cube_u1() {
        this->rotate('y', 1, -pi / 2);
    }
    void cube_d1() {
        this->rotate('y', -1, pi / 2);
    }
    void cube_l1() {
        this->rotate('z', 1, -pi / 2);
    }
    void cube_r1() {
        this->rotate('z', -1, pi / 2);
    }

    void scramble();
    void reset();
};
