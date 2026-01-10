#include "camera.h"
#include "cube.h"
#include "geometry.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

void draw_point(SDL_Renderer *renderer, point2d &p, const color &c) {
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, 255);
    SDL_Rect pointRect;

    int size = 4;
    pointRect.w = size;
    pointRect.h = size;

    pointRect.x = static_cast<int>(p.x) - (size / 2);
    pointRect.y = static_cast<int>(p.y) - (size / 2);
    SDL_RenderFillRect(renderer, &pointRect);
}

void draw_line(SDL_Renderer *renderer, point2d &p1, point2d &p2,
               const color &c) {
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, 255);
    SDL_RenderDrawLine(renderer, static_cast<int>(p1.x), static_cast<int>(p1.y),
                       static_cast<int>(p2.x), static_cast<int>(p2.y));
}

void draw_poly(SDL_Renderer *renderer, point3d &p1, point3d &p2, point3d &p3,
               point3d &p4, camera &cam, const color &c) {

    point2d rp1 = p1.convert_2d(cam);
    point2d rp2 = p2.convert_2d(cam);
    point2d rp3 = p3.convert_2d(cam);
    point2d rp4 = p4.convert_2d(cam);

    draw_point(renderer, rp1, c);
    draw_point(renderer, rp2, c);
    draw_point(renderer, rp3, c);
    draw_point(renderer, rp4, c);

    draw_line(renderer, rp1, rp2, c);
    draw_line(renderer, rp2, rp3, c);
    draw_line(renderer, rp3, rp4, c);
    draw_line(renderer, rp4, rp1, c);
}

void draw_cube(SDL_Renderer *renderer, cube &c, camera &cam) {
    point3d C = cam.conv_cam_3d();
    for (int i = 0; i < 54; i++) {
        point3d cube_n = c.mappings[i].normal;
        point3d cube_p = c.mappings[i].posn;
        double dot = (C - cube_p).dot(cube_n);
        if (dot >= -0.2) {
            point3d p1 = c.mesh[i][0];
            point3d p2 = c.mesh[i][1];
            point3d p3 = c.mesh[i][2];
            point3d p4 = c.mesh[i][3];

            color colr = c.data[i];
            draw_poly(renderer, p1, p2, p3, p4, cam, colr);
        }

        // turn on opacity of back sides if needed
        // current opacity level is 0.2
        // else {
        //     point3d p1 = c.mesh[i][0];
        //     point3d p2 = c.mesh[i][1];
        //     point3d p3 = c.mesh[i][2];
        //     point3d p4 = c.mesh[i][3];
        //
        //     color colr = c.data[i];
        //     draw_poly(renderer, p1, p2, p3, p4, cam, colr * opacity);
        // }
    }
}

int main() {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! Error: " << SDL_GetError()
                  << "\n";
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Rubix", SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                                          SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (!window) {
        std::cout << "Window could not be created! Error: " << SDL_GetError()
                  << "\n";
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    bool isRunning = true;
    SDL_Event event;

    cube c1;
    camera cam;

    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            bool shiftActive = (event.key.keysym.mod & KMOD_SHIFT);
            switch (event.type) {
                case SDL_QUIT:
                    isRunning = false;
                    break;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_q:
                            isRunning = false;
                            break;

                        case SDLK_DOWN:
                            cam.change_phi(0.1);
                            break;

                        case SDLK_UP:
                            cam.change_phi(-0.1);
                            break;

                        case SDLK_RIGHT:
                            cam.change_theta(0.1);
                            break;

                        case SDLK_LEFT:
                            cam.change_theta(-0.1);
                            break;

                        case SDLK_EQUALS:
                            cam.change_rho(-0.1);
                            break;

                        case SDLK_MINUS:
                            cam.change_rho(0.1);
                            break;

                        case SDLK_f:
                            if (shiftActive) {
                                c1.cube_f1();
                            } else {
                                c1.cube_f();
                            };
                            break;
                        case SDLK_b:
                            if (shiftActive) {
                                c1.cube_b1();
                            } else {
                                c1.cube_b();
                            }
                            break;
                        case SDLK_u:
                            if (shiftActive) {
                                c1.cube_u1();
                            } else {
                                c1.cube_u();
                            }
                            break;
                        case SDLK_d:
                            if (shiftActive) {
                                c1.cube_d1();
                            } else {
                                c1.cube_d();
                            }
                            break;
                        case SDLK_l:
                            if (shiftActive) {
                                c1.cube_l1();
                            } else {
                                c1.cube_l();
                            }
                            break;
                        case SDLK_r:
                            if (shiftActive) {
                                c1.cube_r1();
                            } else {
                                c1.cube_r();
                            }
                            break;
                        case SDLK_s:
                            c1.scramble();
                            break;
                        case SDLK_o:
                            c1.reset();
                            break;
                    }
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        draw_cube(renderer, c1, cam);

        SDL_RenderPresent(renderer);
    }
}
