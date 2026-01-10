#include "camera.h"
#include "geometry.h"
#include <cmath>
#include <vector>
using namespace std;

camera::camera(double p, double t, double r) {
    phi = p;
    theta = t;
    rho = r;
}

point3d camera::conv_cam_3d() {
    double y = rho * cos(phi);
    double x = rho * sin(phi) * sin(theta);
    double z = rho * sin(phi) * cos(theta);

    return point3d(x, y, z);
}

void camera::change_rho(double val) {
    rho += val;
}

void camera::change_phi(double val) {
    phi += val;
    if (phi < 0.01)
        phi = 0.01;
    if (phi > 3.14)
        phi = 3.14;
}

void camera::change_theta(double val) {
    theta += val;
}

vector<point3d> camera::get_basis() {
    vector<point3d> out;

    point3d eye = this->conv_cam_3d();
    point3d target(0, 0, 0);
    point3d world_up(0, 1, 0);

    point3d forward = (target - eye).normalize();
    point3d right = forward.cross(world_up).normalize();
    point3d up = right.cross(forward).normalize();

    out.push_back(forward);
    out.push_back(right);
    out.push_back(up);

    return out;
}

// tuple<char, int> camera::front_axis() {
//
//     if (phi > 3 * pi / 4) {
//         return {'y', -1};
//     }
//
//     if (phi < pi / 4) {
//         return {'y', 1};
//     }
//
//     if (theta < 3 * pi / 4 && theta > pi / 4) {
//         return {'x', 1};
//     }
//
//     if (theta < 7 * pi / 4 && theta > 5 * pi / 4) {
//         return {'x', -1};
//     }
//
//     if (theta < 5 * pi / 4 && theta > 3 * pi / 4) {
//         return {'z', -1};
//     }
//
//     else  {
//         return {'z', 1};
//     }
// }
