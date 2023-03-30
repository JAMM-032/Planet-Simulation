#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <vector>

class Planet
{
    public:
        Planet(long double p_x, long double p_y, int p_r, int p_c[3], long double p_m, std::string p_name);
        void draw(SDL_Renderer *renderer, int WIDTH, int HEIGHT);
        void attraction(Planet &other, float &force_x, float &force_y);
        void update(std::vector<Planet> planets);
        void set_x_vel(double val);
        void set_y_vel(double val);
        void set_Sun(bool val);
        long double get_x();
        long double get_y();
        bool get_Sun();
        long double get_m();
        long int get_distance_to_sun();

    private:        
        int c[3];
        bool Sun;
        long double x, y;
        int r;
        double x_vel;
        double y_vel;
        double m;
        long int distance_to_sun;
        std::vector<std::vector<int>> orbit;
        std::string name;
};