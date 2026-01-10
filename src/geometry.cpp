#include "geometry.h"
#include "camera.h"
#include "constants.h"
#include <cmath>
#include <sys/ioctl.h>
#include <unistd.h>
#include <vector>
using namespace std;

point3d::point3d(double a, double b, double c) : x(a), y(b), z(c) {
}

point3d point3d::operator+(const point3d &p) const {
    return point3d(x + p.x, y + p.y, z + p.z);
}

point3d point3d::operator-(const point3d &p) const {
    return point3d(x - p.x, y - p.y, z - p.z);
}

point2d::point2d(double a, double b) {
    x = a;
    y = b;
}

color::color(int red, int green, int blue) {
    r = red;
    g = green;
    b = blue;
}

point2d point3d::convert_2d(camera &cam) const {

    point3d C = cam.conv_cam_3d();
    point3d forward = cam.get_basis()[0];
    point3d right = cam.get_basis()[1];
    point3d up = cam.get_basis()[2];

    point3d rel = *this - C;

    double x1 = rel.dot(right);
    double y1 = rel.dot(up);
    double z1 = rel.dot(forward);

    double aspectRatio = (double)SCREEN_WIDTH / (double)SCREEN_HEIGHT;

    double x2 = x1 / z1;
    double y2 = y1 / z1;

    x2 = x2 / aspectRatio;

    double x_screen = ((x2 + 1.0) / 2.0) * SCREEN_WIDTH;
    double y_screen = (1.0 - (y2 + 1.0) / 2.0) * SCREEN_HEIGHT;

    return point2d(x_screen, y_screen);
}

point3d point3d::rotate(char axis, double angle) {
    point3d temp;

    double c = cos(angle);
    double s = sin(angle);

    if (axis == 'x') {
        temp.x = x;
        temp.y = y * c - z * s;
        temp.z = y * s + z * c;
    }
    if (axis == 'y') {
        temp.x = x * c + z * s;
        temp.y = y;
        temp.z = -x * s + z * c;
    }
    if (axis == 'z') {
        temp.x = x * c - y * s;
        temp.y = x * s + y * c;
        temp.z = z;
    }
    return temp;
}
