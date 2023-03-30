#define TICK_INTERVAL 1000/60
const float AU = (149.6e+6 * 1000);
int WHITE[] = {255, 255, 255};
int BLACK[] = {0, 0, 0};
int YELLOW[] = {255, 255, 0};
int BLUE[] = {100, 149, 237};
int RED[] = {188, 39, 50};
int DARK_GREY[] = {80, 78, 80};
int CHROME_YELLOW[] = {221, 211, 80};

#include <iostream>
#include <SDL2/SDL.h>
#include <cmath>
#include <vector>
#include <string>

#include "draw.hpp"
#include "planets.hpp"

int WIDTH = 750, HEIGHT = 750;

Uint32 time_left(Uint32 next_time)
{
    Uint32 now;

    now = SDL_GetTicks();
    if (next_time <= now)
    {
        return 0;
    }
    else
    {
        return next_time - now;
    }
}

int main(int argc, char* argv[])
{
    
    SDL_Init( SDL_INIT_EVERYTHING );


    SDL_Window *window = SDL_CreateWindow( "Solar System Simulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (NULL == window)
    {
        std::cout << "Could not create window: " << SDL_GetError( ) << std::endl;
        return 1;
    }

    // Planet(long double p_x, long double p_y, int p_r, int p_c[3], long double p_m, std::string p_name)

    Planet sun(0, 0, 30, YELLOW, 1.98892 * pow(10, 30), "sun");
    sun.set_Sun(true);

    Planet earth(-1 * AU, 0, 16, BLUE, 5.9742 * pow(10, 24), "earth");
    earth.set_y_vel(29.783 * 1000);

    Planet mars(-1.524 * AU, 0, 12, RED, 6.39 * pow(10, 23), "mars");
    mars.set_y_vel(24.077 * 1000);

    Planet mercury(0.387 * AU, 0, 8, DARK_GREY, 3.30 * pow(10, 23), "mercury");
    mercury.set_y_vel(-47.4 * 1000);

    Planet venus(0.723 * AU, 0, 14, CHROME_YELLOW, 4.8685 * pow(10, 24), "venus");
    venus.set_y_vel(-35.02 * 1000);

    std::vector<Planet> planets = {sun, earth, mars, mercury, venus};

    // int center[2] = {(int)WIDTH/2, (int)HEIGHT/2};
    // double radius = 150;


    // int N = 100;

    // double theta[N];

    // double start = 0, end = 2 * M_PI;

    // double delta = (end - start) / (N - 1);

    // for (int i=0; i < (N - 1); ++i)
    // {
    //     theta[i] = (start + delta * i);
    // }

    // theta[N] = end;

    // int iterate = 0;

    static Uint32 next_time;
    next_time = SDL_GetTicks() + TICK_INTERVAL;

    bool gameRunning = true;

    while (gameRunning)
    {
        SDL_Event windowEvent;

        if (SDL_PollEvent( &windowEvent ))
        {
            if (SDL_QUIT == windowEvent.type)
            { gameRunning = false; }
        }

        SDL_RenderClear(renderer);

        for (Planet p : planets)
        {
            p.update(planets);
            p.draw(renderer, WIDTH, HEIGHT);
            reset_col(renderer);
        }


        display(renderer);
        SDL_Delay(time_left(next_time));
        next_time += TICK_INTERVAL;
    }

    SDL_DestroyWindow( window );
    SDL_Quit( );

    return EXIT_SUCCESS;
}