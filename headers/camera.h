#pragma once
#include "constants.h"
#include "geometry.h"
#include <tuple>
#include <vector>
using namespace std;

class camera {
public:
    double phi;
    double theta;
    double rho;

    camera(double phi = 3 * pi / 8, double theta = pi / 4, double rho = 3.3);

    point3d conv_cam_3d();

    vector<point3d> get_basis();
    void change_rho(double val);
    void change_phi(double val);
    void change_theta(double val);

    tuple<char, int> front_axis();
};


