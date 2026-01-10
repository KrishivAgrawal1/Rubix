#include "cube.h"
#include "constants.h"
#include "geometry.h"
#include <cstdlib>
#include <vector>
using namespace std;

cube::cube() {
    data.resize(54, color(0, 0, 0));
    mesh.clear();
    mappings.clear();
    mesh.resize(54);

    for (int i = 0; i < 54; i++) {
        data[i] = colors.at(i / 9);
    }

    int k = 0;
    for (int i = 0; i < 6; i++) {
        int axis = i / 2;
        int val = (i % 2 == 0) ? +1 : -1;

        for (auto x : coordinates) {
            facelet cell;

            switch (axis) {
                case 0:
                    cell.normal.x = val;
                    break;
                case 1:
                    cell.normal.y = val;
                    break;
                case 2:
                    cell.normal.z = val;
                    break;
            }

            vector<double> y = {scale * x[0], scale * x[1]};

            x.insert(x.begin() + axis, val);
            point3d temp(x[0], x[1], x[2]);
            cell.posn = temp;

            mappings.push_back(cell);

            double d = 0.20;

            vector<double> p1 = {y[0] - d, y[1] + d};
            vector<double> p2 = {y[0] + d, y[1] + d};
            vector<double> p3 = {y[0] + d, y[1] - d};
            vector<double> p4 = {y[0] - d, y[1] - d};

            p1.insert(p1.begin() + axis, val);
            p2.insert(p2.begin() + axis, val);
            p3.insert(p3.begin() + axis, val);
            p4.insert(p4.begin() + axis, val);

            point3d temp1(p1[0], p1[1], p1[2]);
            point3d temp2(p2[0], p2[1], p2[2]);
            point3d temp3(p3[0], p3[1], p3[2]);
            point3d temp4(p4[0], p4[1], p4[2]);

            mesh[k] = {temp1, temp2, temp3, temp4};
            k++;
        }
    }
}

void cube::rotate(char axis, int layer, double angle) {
    vector<int> indices;
    for (int i = 0; i < 54; i++) {
        bool match = false;
        if (mappings[i].posn.x == layer && axis == 'x')
            match = true;
        if (mappings[i].posn.y == layer && axis == 'y')
            match = true;
        if (mappings[i].posn.z == layer && axis == 'z')
            match = true;
        if (match)
            indices.push_back(i);
    }

    vector<color> new_data = data;

    for (auto &i : indices) {
        point3d new_posn = mappings[i].posn.rotate(axis, angle);
        point3d new_normal = mappings[i].normal.rotate(axis, angle);

        for (int j = 0; j < 54; j++) {
            if (mappings[j].normal == new_normal &&
                mappings[j].posn == new_posn) {
                new_data[j] = data[i];
                break;
            }
        }
    }

    data = new_data;
}

void cube::scramble() {
    std::vector<void(cube::*)()> funcs = {
        &cube::cube_f,  &cube::cube_b,  &cube::cube_r,  &cube::cube_u,
        &cube::cube_d,  &cube::cube_l,  &cube::cube_f1, &cube::cube_b1,
        &cube::cube_r1, &cube::cube_u1, &cube::cube_d1, &cube::cube_l1
    };

    for (int i = 0; i < 25; i++) {
        int j = rand() % 12;
        (this->*funcs[j])();
    }
}

void cube::reset() {
    for (int i = 0; i < 54; i++) {
        data[i] = colors.at(i / 9);
    }
}
