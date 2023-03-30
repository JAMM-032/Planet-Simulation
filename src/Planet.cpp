const float AU (149.6e+6 * 1000);
const double G = (6.67428e-11);
const float SCALE = 150 / AU;
const double TIMESTEP = (3600*24);

#include <iostream>
#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <cmath>

#include "planets.hpp"
#include "draw.hpp"


Planet::Planet(long double p_x, long double p_y, int p_r, int p_c[3], long double p_m, std::string p_name)
{
    this->x = p_x;
    this->y = p_y;
    this->r = p_r;
    for (int i = 0; i < 3; i++)
    {
        this->c[i] = p_c[i];
    }
    this->m = p_m;
    this->name = p_name;

}

void Planet::draw(SDL_Renderer *renderer, const int WIDTH, const int HEIGHT)
{
    int x0 = (int)((this->x * SCALE) + (WIDTH / 2));
    int y0 = (int)((this->y * SCALE) + (HEIGHT / 2));
    SDL_SetRenderDrawColor(renderer, this->c[0], this->c[1], this->c[2], SDL_ALPHA_OPAQUE);
    if (true)
    {
        std::vector<std::vector<int>> updated_points = {};
        for (std::vector<int> point : this->orbit)
        {
            int x1 = point[0], y1 = point[1];
            int x2 = x1 * SCALE + WIDTH / 2;
            int y2 = y1 * SCALE + HEIGHT / 2;
            updated_points.push_back({x2, y2});
        }
        for (unsigned int i = 0; i < updated_points.size()-1; i++)
        {
            line(renderer, updated_points[i][0], updated_points[i][1], updated_points[i+1][0], updated_points[i+1][1]);
        }
    }
    SDL_RenderFillCircle(renderer, x0, y0, this->r);
    reset_col(renderer);
}

void Planet::attraction(Planet &other, float &force_x, float &force_y)
{
    int other_x = other.get_x(), other_y = other.get_y();
    float distance_x = other_x - this->x;
    float distance_y = other_y - this->y;
    int distance = std::sqrt(std::pow(distance_x, 2) + std::pow(distance_y, 2));

    if (other.Sun) { this->distance_to_sun = distance; }

    float force = G * this->m * other.m / pow(distance, 2);
    double theta = std::atan2(distance_x, distance_y);
    force_x = std::cos(theta) * force;
    force_y = std::sin(theta) * force;
}

void Planet::update(std::vector<Planet> planets)
{
    float totalfx = 0.0, totalfy = 0.0;
    for (Planet planet : planets)
    {
        if (!(this->name == planet.name))
        {
            float fx = 0, fy = 0;
            this->attraction(planet, fx, fy);
            totalfx += fx;
            totalfy += fy;
        }
    }
    // std::cout << totalfx << ' ' << totalfy << std::endl;

    this->x_vel += totalfx / this->m * TIMESTEP;
    this->y_vel += totalfy / this->m * TIMESTEP;

    // std::cout << this->x_vel * TIMESTEP << ' ' << this->y_vel * TIMESTEP << std::endl;
    
    this->x += (long double)100000;
    this->y = this->y + (long double)100000;
    std::cout << this->x << ' ' << this->y << std::endl;
    this->orbit.push_back({(int)this->x, (int)this->y});
}

void Planet::set_x_vel(double val)
{
    this->x_vel = val;
}

void Planet::set_y_vel(double val)
{
    this->y_vel = val;
}

void Planet::set_Sun(bool val)
{
    this->Sun = val;
}

long double Planet::get_x()
{
    return this->x;
}

long double Planet::get_y()
{
    return this->y;
}

bool Planet::get_Sun()
{
    return this->Sun;
}

long double Planet::get_m()
{
    return this->m;
}

long int Planet::get_distance_to_sun()
{
    return this->distance_to_sun;
}