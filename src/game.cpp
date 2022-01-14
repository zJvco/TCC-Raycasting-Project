#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_circle.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <time.h>

#include "game.hpp"
#include "ray.hpp"
#include "utils.hpp"
#include "map.hpp"
#include "player.hpp"

int main(int argc, char* argv[])
{
    SDL_Window *window;
    SDL_Renderer *renderer;

    bool run = true;

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        std::cout << "Failed to initialize SDL %s\n" << SDL_GetError();

    window = SDL_CreateWindow (
        "Raycasting",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WIDTH,
        HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (window == NULL)
    {
        std::cout << "Could not create window: %s\n" << SDL_GetError();
        return 1;
    }

    if (FULLSCREEN)
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

    renderer = SDL_CreateRenderer(window, -1, 0);

    if (renderer == NULL)
    {
        std::cout << "Could not create renderer: %s\n" << SDL_GetError();
        return 1;
    }

    Player p(WIDTH/2, HEIGHT/2, cos(get_radians(p.angle))*5, sin(get_radians(p.angle))*5);

    // Criando os raios (objetos)
    std::vector<Ray> rays;

    for (int a = 0; a < 10; a++)
    {
        Ray ray(p.x, p.y, 0, 0, get_radians(a), 1000);
        rays.push_back(ray);
    }

    // Objeto do chão
    SDL_Rect floor;
    floor.x = 0;
    floor.y = HEIGHT / 2;
    floor.w = WIDTH;
    floor.h = HEIGHT;

    // Player Rect
    SDL_Rect pr;
    pr.w = 15;
    pr.h = 15;

    SDL_Event event;

    // Loop principal
    while (run)
    {
        // Começando a contar o tempo que leva para realizar as ações abaixo
        frameStart = SDL_GetTicks();

        // Fundo do céu
        SDL_SetRenderDrawColor(renderer, 135, 206, 235, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        
        // Fundo do chão
        SDL_SetRenderDrawColor(renderer, 175, 175, 175, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &floor);

        // Loop de eventos
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                run = false;
                break;
            }

            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_w:
                        break;
                    case SDLK_s:
                        break;
                    case SDLK_a:
                        break;
                    case SDLK_d:
                        break;
                    default:
                        break;
                }
            }
        }

        drawMap2D(renderer, map);

        for (Ray& ray : rays)
        {
            ray.setX(pr.x+pr.w/2);
            ray.setY(pr.y+pr.h/2);
            ray.setDirX(p.dx);
            ray.setDirY(p.dy);
            
            ray.Draw(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        }

        pr.x = p.x;
        pr.y = p.y;

        p.draw(renderer, &pr);

        SDL_RenderPresent(renderer);

        // Tempo final do processo realizado acima
        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    SDL_Quit();
    return 0;
}