#include <cmath>
#pragma once

class camera;

class point2d {
public:
    double x;
    double y;
    point2d(double a, double b);
};

class point3d {
public:
    double x;
    double y;
    double z;
    point3d(double x = 0.0, double y = 0.0, double z = 0.0);

    point3d operator+(const point3d &p) const;
    point3d operator-(const point3d &p) const;

    bool operator==(const point3d &p) const {
        return (fabs(x - p.x) < 0.1 && fabs(y - p.y) < 0.1 &&
                fabs(z - p.z) < 0.1);
    }

    point2d convert_2d(camera &cam) const;

    point3d cross(const point3d &b) {
        return point3d(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
    }

    double dot(const point3d &b) {
        return x * b.x + y * b.y + z * b.z;
    }

    double length() const {
        return sqrt(x * x + y * y + z * z);
    }

    point3d normalize() const {
        double l = length();
        return point3d(x / l, y / l, z / l);
    }

    point3d rotate(char axis, double angle);
};

class color {
public:
    int r;
    int g;
    int b;
    color(int a, int b, int c);

    color operator*(double lightness) {
        int a1 = (int)(r * lightness);
        int b1 = (int)(g * lightness);
        int c1 = (int)(b * lightness);
        return color(a1, b1, c1);
    }
};
